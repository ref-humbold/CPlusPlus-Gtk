package ref_humbold.di_container;

import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

class Provider
    extends DIContainerProvider
{
    private DIContainer container;

    public Provider(DIContainer container)
    {
        super();
        this.container = container;
        configureContainer(this.container);
    }

    @Override
    public DIContainer getContainer()
    {
        return container;
    }

    @Override
    protected void configureContainer(DIContainer container)
    {
        container.registerType(TestInterfaceComplexDependency.class,
                               TestClassComplexDependency.class);
        container.registerType(TestInterfaceBasic.class, TestClassWithDefaultConstructorOnly.class);
        container.registerType(TestInterfaceDiamond1.class, TestClassDiamond1.class);
        container.registerType(TestInterfaceDiamondBase.class, TestClassDiamondBase.class);
        container.registerType(TestInterfaceWithString.class, TestClassWithString.class);

        container.registerInstance(String.class, "string");
    }
}

public class DIServiceLocatorTest
{
    private DIContainer container;
    private Provider provider;

    @Before
    public void setUp()
    {
        container = new DIContainer();
        provider = new Provider(container);
    }

    @After
    public void tearDown()
    {
        container = null;
        provider = null;
    }

    @Test
    public void testGetInstance()
    {
        DIServiceLocator instance1 = DIServiceLocator.getInstance();
        DIServiceLocator instance2 = DIServiceLocator.getInstance();

        Assert.assertNotNull(instance1);
        Assert.assertNotNull(instance2);
        Assert.assertSame(instance1, instance2);
    }

    @Test
    public void testResolveInstanceWhenAllDependenciesArePresent()
    {
        DIServiceLocator.setContainerProvider(provider);

        TestInterfaceComplexDependency cls = null;

        try
        {
            cls = DIServiceLocator.getInstance().resolveType(TestInterfaceComplexDependency.class);
        }
        catch(DIException e)
        {
            e.printStackTrace();
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls);
        Assert.assertNotNull(cls.getBasicObject());
        Assert.assertNotNull(cls.getFirstObject());
        Assert.assertNotNull(cls.getSecondObject());
        Assert.assertNotNull(cls.getFirstObject().getObject());
        Assert.assertNotNull(cls.getSecondObject().getString());
        Assert.assertEquals("string", cls.getSecondObject().getString());
        Assert.assertTrue(cls instanceof TestClassComplexDependency);
    }

    @Test(expected = MissingDependenciesException.class)
    public void testResolveInstanceWhenMissingDependencies()
        throws DIException
    {
        DIServiceLocator.setContainerProvider(provider);

        DIServiceLocator.getInstance().resolveType(TestInterfaceDiamondBase.class);
    }

    @Test(expected = EmptyContainerProviderException.class)
    public void testResolveInstanceWhenContainerProviderIsNull()
        throws DIException
    {
        DIServiceLocator.setContainerProvider(null);

        DIServiceLocator.getInstance().resolveType(TestInterfaceComplexDependency.class);
    }

    @Test
    public void testResolveInstanceWhenContainerType()
    {
        DIServiceLocator.setContainerProvider(provider);

        DIContainer cnt = null;

        try
        {
            cnt = DIServiceLocator.getInstance().resolveType(DIContainer.class);
        }
        catch(DIException e)
        {
            e.printStackTrace();
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cnt);
        Assert.assertSame(container, cnt);
    }
}
