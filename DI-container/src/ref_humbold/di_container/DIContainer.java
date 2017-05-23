package ref_humbold.di_container;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Modifier;
import java.util.HashMap;
import java.util.Map;

public class DIContainer
{
    private Map<Class<?>, Object> instances = new HashMap<>();
    private Map<Class<?>, Class<?>> classes = new HashMap<>();

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
        classes.put(supercls, cls);

        if(isSingleton)
            instances.put(supercls, null);
        else if(instances.containsKey(supercls))
            instances.remove(supercls);
    }

    public <T> void registerInstance(Class<T> cls, T instance)
    {
        if(instance == null)
            throw new IllegalArgumentException("Instance is null.");

        instances.put(cls, instance);
    }

    public <T> T resolve(Class<T> cls)
        throws AbstractTypeException, NoSuitableConstructorException, NewInstantanceException
    {
        if(instances.containsKey(cls) && instances.get(cls) != null)
            return (T)instances.get(cls);

        Class<? extends T> mappedcls = cls;

        do
        {
            if(!classes.containsKey(mappedcls))
                if(isAbstract(mappedcls))
                    throw new AbstractTypeException();
                else
                    classes.put(mappedcls, mappedcls);

            mappedcls = (Class<? extends T>)classes.get(mappedcls);
        }
        while(isAbstract(mappedcls));

        T object = construct(mappedcls);

        if(instances.containsKey(cls))
            instances.put(cls, object);

        return object;
    }

    private boolean isAbstract(Class<?> cls)
    {
        return cls.isInterface() || Modifier.isAbstract(cls.getModifiers());
    }

    private <T> T construct(Class<? extends T> cls)
        throws NoSuitableConstructorException, NewInstantanceException
    {
        Constructor<? extends T> ctor = null;
        T object = null;

        try
        {
            ctor = cls.getConstructor();
        }
        catch(NoSuchMethodException | SecurityException e)
        {
            throw new NoSuitableConstructorException(e);
        }

        try
        {
            object = ctor.newInstance();
        }
        catch(InstantiationException | IllegalAccessException | IllegalArgumentException
              | InvocationTargetException e)
        {
            throw new NewInstantanceException(e);
        }

        return object;
    }
}
