package ref_humbold.di_container;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

public final class DIContainer
{
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
        if(isAbstractType(cls))
            throw new AbstractTypeException();

        registerType(cls, cls, isSingleton);
    }

    public <T> void registerType(Class<T> supercls, Class<? extends T> cls)
    {
        registerType(supercls, cls, false);
    }

    public <T> void registerType(Class<T> supercls, Class<? extends T> cls, boolean isSingleton)
    {
        classes.put(changeToReferenceType(supercls), changeToReferenceType(cls));

        if(isSingleton)
            instances.put(changeToReferenceType(supercls), null);
        else if(instances.containsKey(changeToReferenceType(supercls)))
            instances.remove(changeToReferenceType(supercls));
    }

    public <T> void registerInstance(Class<T> cls, T instance)
    {
        if(instance == null)
            throw new IllegalArgumentException("Instance is null.");

        instances.put(changeToReferenceType(cls), instance);
    }

    public <T> T resolve(Class<T> cls)
        throws DIException
    {
        lastException = null;

        return resolveType(cls, new ArrayDeque<Class<?>>());
    }

    public <T> void buildUp(T obj)
        throws DIException
    {
        buildUpObject(obj, new ArrayDeque<Class<?>>());
    }

    private boolean isAbstractType(Class<?> cls)
    {
        return cls.isInterface() || Modifier.isAbstract(cls.getModifiers());
    }

    private boolean isCorrectAnnotatedMethod(Method method)
    {
        if(!method.isAnnotationPresent(DependencyMethod.class))
            throw new IllegalArgumentException();

        return method.getReturnType() == void.class && method.getParameterCount() > 0;
    }

    private Class<?> changeToReferenceType(Class<?> cls)
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

    private <T> T resolveType(Class<T> cls, ArrayDeque<Class<?>> resolved)
        throws DIException
    {
        T object = null;

        if(instances.containsKey(changeToReferenceType(cls))
           && instances.get(changeToReferenceType(cls)) != null)
            object = (T)instances.get(changeToReferenceType(cls));
        else
            object = resolveConstructor(cls, resolved);

        buildUpObject(object, resolved);

        return object;
    }

    private <T> T resolveConstructor(Class<T> cls, ArrayDeque<Class<?>> resolved)
        throws DIException
    {
        resolved.addFirst(cls);

        Class<? extends T> mappedClass = findRegisteredConcreteClass(cls);
        Constructor<? extends T>[] constructors = getConstructors(mappedClass);

        Arrays.sort(constructors, new ConstructorComparator());

        if(constructors.length > 1)
            if(constructors[1].isAnnotationPresent(DependencyConstructor.class))
                throw new MultipleAnnotatedConstructorsException();

        T object = null;

        for(Constructor<? extends T> ctor : constructors)
        {
            object = createInstance(ctor, resolved);

            if(object != null || ctor.isAnnotationPresent(DependencyConstructor.class))
                break;
        }

        if(object == null)
        {
            resolved.removeFirst();

            throw lastException;
        }

        if(instances.containsKey(changeToReferenceType(cls)))
            instances.put(changeToReferenceType(cls), object);

        resolved.removeFirst();

        return object;
    }

    private <T> void resolveMethod(T object, Method method, ArrayDeque<Class<?>> resolved)
        throws DIException
    {
        ArrayList<Object> paramObjects = new ArrayList<>();

        for(Class<?> p : method.getParameterTypes())
            paramObjects.add(resolveType(p, resolved));

        try
        {
            method.invoke(object, paramObjects.toArray());
        }
        catch(IllegalAccessException | IllegalArgumentException | InvocationTargetException e)
        {
            throw new DIException(e);
        }
    }

    private <T> void buildUpObject(T obj, ArrayDeque<Class<?>> resolved)
        throws DIException
    {
        ArrayList<Method> methods = new ArrayList<>();

        for(Method m : obj.getClass().getMethods())
            if(m.isAnnotationPresent(DependencyMethod.class))
            {
                if(!isCorrectAnnotatedMethod(m))
                    throw new IncorrectDependencyMethodSignature();

                methods.add(m);
            }

        for(Method m : methods)
            resolveMethod(obj, m, resolved);
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

            if(!instances.containsKey(changeToReferenceType(cls))
               && !classes.containsKey(changeToReferenceType(cls)))
            {
                lastException = new MissingDependenciesException();

                return null;
            }

            try
            {
                params.add(resolveType(changeToReferenceType(cls), resolved));
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

    private <T> Class<? extends T> findRegisteredConcreteClass(Class<T> cls)
        throws AbstractTypeException
    {
        Class<? extends T> mappedClass = cls;

        do
        {
            if(!classes.containsKey(changeToReferenceType(mappedClass)))
                if(isAbstractType(mappedClass))
                    throw new AbstractTypeException();
                else
                    classes.put(changeToReferenceType(mappedClass),
                                changeToReferenceType(mappedClass));

            mappedClass = (Class<? extends T>)classes.get(changeToReferenceType(mappedClass));
        }
        while(isAbstractType(mappedClass));

        return mappedClass;
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
