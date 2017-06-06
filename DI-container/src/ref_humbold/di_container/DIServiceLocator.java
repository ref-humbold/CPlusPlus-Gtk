package ref_humbold.di_container;

public final class DIServiceLocator
{
    private static DIContainerProvider containerProvider = null;
    private static DIServiceLocator instance = null;

    private DIServiceLocator()
    {
    }

    public static void setContainerProvider(DIContainerProvider provider)
    {
        containerProvider = provider;
    }

    public static DIServiceLocator getInstance()
    {
        if(instance == null)
            instance = new DIServiceLocator();

        return instance;
    }

    public <T> T resolveType(Class<T> cls)
        throws DIException
    {
        if(containerProvider == null)
            throw new EmptyContainerProviderException();

        if(cls == DIContainer.class)
            return (T)containerProvider.getContainer();

        return containerProvider.getContainer().resolve(cls);
    }
}
