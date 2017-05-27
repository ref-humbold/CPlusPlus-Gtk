package ref_humbold.di_container;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Modifier;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Map;

public class DIContainer
{
    private class ConstructorComparator
        implements Comparator<Constructor<?>>
    {
        @Override
        public int compare(Constructor<?> ctor0, Constructor<?> ctor1)
        {
            boolean ctorAnnotated0 = ctor0.isAnnotationPresent(DependencyConstructor.class);
            boolean ctorAnnotated1 = ctor1.isAnnotationPresent(DependencyConstructor.class);

            if(ctorAnnotated0 && !ctorAnnotated1)
                return -1;

            if(ctorAnnotated1 && !ctorAnnotated0)
                return 1;

            int ctorParams0 = ctor0.getParameterCount();
            int ctorParams1 = ctor1.getParameterCount();

            if(ctorParams0 > ctorParams1)
                return -1;

            if(ctorParams0 < ctorParams1)
                return 1;

            return 0;
        }
    }

    private Map<Class<?>, Object> instances = new HashMap<>();
    private Map<Class<?>, Class<?>> classes = new HashMap<>();
    private DIException lastException = null;

    public DIContainer()
    {
    }

    public <T> void registerType(Class<T> cls)
        throws AbstractTypeException
    {
        registerType(cls, false);
    }

    public <T> void registerType(Class<T> cls, boolean isSingleton)
        throws AbstractTypeException
    {
        if(isAbstract(cls))
            throw new AbstractTypeException();

        registerType(cls, cls, isSingleton);
    }

    public <T> void registerType(Class<T> supercls, Class<? extends T> cls)
    {
        registerType(supercls, cls, false);
    }

    public <T> void registerType(Class<T> supercls, Class<? extends T> cls, boolean isSingleton)
    {
        classes.put(referenced(supercls), referenced(cls));

        if(isSingleton)
            instances.put(referenced(supercls), null);
        else if(instances.containsKey(referenced(supercls)))
            instances.remove(referenced(supercls));
    }

    public <T> void registerInstance(Class<T> cls, T instance)
    {
        if(instance == null)
            throw new IllegalArgumentException("Instance is null.");

        instances.put(referenced(cls), instance);
    }

    public <T> T resolve(Class<T> cls)
        throws DIException
    {
        ArrayDeque<Class<?>> resolved = new ArrayDeque<>();

        lastException = null;

        return resolve(cls, resolved);
    }

    private boolean isAbstract(Class<?> cls)
    {
        return cls.isInterface() || Modifier.isAbstract(cls.getModifiers());
    }

    private Class<?> referenced(Class<?> cls)
    {
        if(cls == byte.class)
            cls = Byte.class;
        else if(cls == short.class)
            cls = Short.class;
        else if(cls == int.class)
            cls = Integer.class;
        else if(cls == long.class)
            cls = Long.class;
        else if(cls == float.class)
            cls = Float.class;
        else if(cls == double.class)
            cls = Double.class;
        else if(cls == boolean.class)
            cls = Boolean.class;
        else if(cls == char.class)
            cls = Character.class;

        return cls;
    }

    private <T> T resolve(Class<T> cls, ArrayDeque<Class<?>> resolved)
        throws DIException
    {
        resolved.addFirst(cls);

        if(instances.containsKey(referenced(cls)) && instances.get(referenced(cls)) != null)
        {
            resolved.removeFirst();

            return (T)instances.get(referenced(cls));
        }

        Class<? extends T> mappedClass = getConcreteClass(cls);
        Constructor<? extends T>[] constructors = getConstructors(mappedClass);

        Arrays.sort(constructors, new ConstructorComparator());

        if(constructors.length > 1)
            if(constructors[0].isAnnotationPresent(DependencyConstructor.class)
               && constructors[1].isAnnotationPresent(DependencyConstructor.class))
                throw new MultipleAnnotatedConstructorsException();

        T object = null;

        for(Constructor<? extends T> ctor : constructors)
        {
            object = createInstance(ctor, resolved);

            if(object != null || ctor.isAnnotationPresent(DependencyConstructor.class))
                break;
        }

        if(object == null)
            throw lastException;

        if(instances.containsKey(referenced(cls)))
            instances.put(referenced(cls), object);

        resolved.removeFirst();

        return object;
    }

    private <T> Class<? extends T> getConcreteClass(Class<T> cls)
        throws AbstractTypeException
    {
        Class<? extends T> mappedClass = cls;

        do
        {
            if(!classes.containsKey(referenced(mappedClass)))
                if(isAbstract(mappedClass))
                    throw new AbstractTypeException();
                else
                    classes.put(referenced(mappedClass), referenced(mappedClass));

            mappedClass = (Class<? extends T>)classes.get(referenced(mappedClass));
        }
        while(isAbstract(mappedClass));

        return mappedClass;
    }

    private <T> T createInstance(Constructor<? extends T> ctor, ArrayDeque<Class<?>> resolved)
        throws DIException
    {
        T instance = null;
        ArrayList<Object> params = new ArrayList<>();

        for(Class<?> cls : ctor.getParameterTypes())
        {
            if(resolved.contains(cls))
            {
                lastException = new CircularDependenciesException();

                return null;
            }

            if(!instances.containsKey(referenced(cls)) && !classes.containsKey(referenced(cls)))
            {
                lastException = new MissingDependenciesException();

                return null;
            }

            try
            {
                params.add(resolve(referenced(cls), resolved));
            }
            catch(DIException e)
            {
                lastException = e;

                return null;
            }
        }

        try
        {
            instance = ctor.newInstance(params.toArray());
        }
        catch(InstantiationException | IllegalAccessException | IllegalArgumentException
              | InvocationTargetException e)
        {
            lastException = new DIException(e);
        }

        return instance;
    }

    private <T> Constructor<? extends T>[] getConstructors(Class<? extends T> cls)
        throws NoSuitableConstructorException
    {
        Constructor<?>[] constructors = null;

        try
        {
            constructors = cls.getConstructors();
        }
        catch(SecurityException e)
        {
            throw new NoSuitableConstructorException(e);
        }

        if(constructors == null || constructors.length == 0)
            throw new NoSuitableConstructorException();

        return (Constructor<? extends T>[])constructors;
    }
}
