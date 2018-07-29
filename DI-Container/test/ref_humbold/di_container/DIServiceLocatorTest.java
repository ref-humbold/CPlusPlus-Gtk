package ref_humbold.di_container;

import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import ref_humbold.di_container.auxiliary.basics.ClassBasicsComplexDependency;
import ref_humbold.di_container.auxiliary.basics.InterfaceBasicsComplexDependency;
import ref_humbold.di_container.auxiliary.basics.InterfaceBasicsStringGetter;
import ref_humbold.di_container.auxiliary.diamonds.InterfaceDiamonds1;
import ref_humbold.di_container.auxiliary.diamonds.InterfaceDiamondsBottom;
import ref_humbold.di_container.auxiliary.setters.ClassSettersDouble;
import ref_humbold.di_container.auxiliary.setters.InterfaceSettersDouble;
import ref_humbold.di_container.exception.DIException;
import ref_humbold.di_container.exception.EmptyContainerProviderException;
import ref_humbold.di_container.exception.IncorrectDependencySetterException;
import ref_humbold.di_container.exception.MissingDependenciesException;

public class DIServiceLocatorTest
{
    private DIContainer container;
    private CustomProvider provider;

    @Before
    public void setUp()
    {
        container = new DIContainer();
        provider = new CustomProvider(container);
    }

    @After
    public void tearDown()
    {
        container = null;
        provider = null;
    }

    @Test
    public void testIsProviderPresentWhenProviderSet()
    {
        DIServiceLocator.setContainerProvider(provider);

        boolean result = DIServiceLocator.isProviderPresent();

        Assert.assertTrue(result);
    }

    @Test
    public void testIsProviderPresentWhenProviderNotSet()
    {
        DIServiceLocator.setContainerProvider(null);

        boolean result = DIServiceLocator.isProviderPresent();

        Assert.assertFalse(result);
    }

    @Test
    public void testResolveWhenAllDependenciesArePresent()
    {
        DIServiceLocator.setContainerProvider(provider);

        InterfaceBasicsComplexDependency result = null;

        try
        {
            result = DIServiceLocator.resolve(InterfaceBasicsComplexDependency.class);
        }
        catch(DIException e)
        {
            e.printStackTrace();
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(result);
        Assert.assertNotNull(result.getBasicObject());
        Assert.assertNotNull(result.getFirstObject());
        Assert.assertNotNull(result.getSecondObject());
        Assert.assertNotNull(result.getFirstObject().getObject());
        Assert.assertNotNull(result.getSecondObject().getString());
        Assert.assertEquals("string", result.getSecondObject().getString());
        Assert.assertTrue(result instanceof ClassBasicsComplexDependency);
    }

    @Test(expected = MissingDependenciesException.class)
    public void testResolveWhenMissingDependencies()
        throws DIException
    {
        DIServiceLocator.setContainerProvider(provider);

        DIServiceLocator.resolve(InterfaceDiamondsBottom.class);
    }

    @Test(expected = EmptyContainerProviderException.class)
    public void testResolveWhenContainerProviderIsNull()
        throws DIException
    {
        DIServiceLocator.setContainerProvider(null);

        DIServiceLocator.resolve(InterfaceBasicsComplexDependency.class);
    }

    @Test
    public void testResolveWhenContainerType()
    {
        DIServiceLocator.setContainerProvider(provider);

        DIContainer result = null;

        try
        {
            result = DIServiceLocator.resolve(DIContainer.class);
        }
        catch(DIException e)
        {
            e.printStackTrace();
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(result);
        Assert.assertSame(container, result);
    }

    @Test
    public void testBuildUpWhenWhenAllDependenciesArePresent()
    {
        DIServiceLocator.setContainerProvider(provider);

        InterfaceBasicsComplexDependency instance = null;
        InterfaceBasicsComplexDependency result = null;

        try
        {
            InterfaceDiamonds1 diamond1 = DIServiceLocator.resolve(InterfaceDiamonds1.class);
            InterfaceBasicsStringGetter withString = DIServiceLocator.resolve(
                InterfaceBasicsStringGetter.class);

            instance = new ClassBasicsComplexDependency(diamond1, withString);
            result = DIServiceLocator.buildUp(instance);
        }
        catch(DIException e)
        {
            e.printStackTrace();
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(result);
        Assert.assertNotNull(instance);
        Assert.assertNotNull(result.getBasicObject());
        Assert.assertNotNull(instance.getBasicObject());
        Assert.assertNotNull(result.getFirstObject());
        Assert.assertNotNull(instance.getFirstObject());
        Assert.assertNotNull(result.getSecondObject());
        Assert.assertNotNull(instance.getSecondObject());
        Assert.assertNotNull(result.getFirstObject().getObject());
        Assert.assertNotNull(instance.getFirstObject().getObject());
        Assert.assertNotNull(result.getSecondObject().getString());
        Assert.assertNotNull(instance.getSecondObject().getString());
        Assert.assertEquals("string", result.getSecondObject().getString());
        Assert.assertEquals("string", instance.getSecondObject().getString());
        Assert.assertSame(instance, result);
    }

    @Test(expected = IncorrectDependencySetterException.class)
    public void testBuildUpWhenIncorrectSetters()
        throws DIException
    {
        DIServiceLocator.setContainerProvider(provider);

        InterfaceSettersDouble instance = new ClassSettersDouble();

        DIServiceLocator.buildUp(instance);
    }
}
