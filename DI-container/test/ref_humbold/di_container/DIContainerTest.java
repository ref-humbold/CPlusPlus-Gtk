package ref_humbold.di_container;

import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import ref_humbold.di_container.AbstractTypeException;
import ref_humbold.di_container.DIContainer;
import ref_humbold.di_container.NewInstantanceException;
import ref_humbold.di_container.NoSuitableConstructorException;

public class DIContainerTest
{
    private DIContainer testObject;

    @Before
    public void setUp()
    {
        testObject = new DIContainer();
    }

    @After
    public void tearDown()
    {
        testObject = null;
    }

    @Test
    public void testRegisterWhenSingleClass()
    {
        try
        {
            testObject.registerType(TestClass1.class);
        }
        catch(AbstractTypeException e)
        {
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        TestClass1 cls1 = null;
        TestClass1 cls2 = null;

        try
        {
            cls1 = testObject.resolve(TestClass1.class);
            cls2 = testObject.resolve(TestClass1.class);
        }
        catch(AbstractTypeException | NoSuitableConstructorException | NewInstantanceException e)
        {
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls1);
        Assert.assertNotNull(cls2);
        Assert.assertNotSame(cls1, cls2);
    }

    @Test
    public void testRegisterWhenSingleClassAsSingleton()
    {
        try
        {
            testObject.registerType(TestClass1.class, true);
        }
        catch(AbstractTypeException e)
        {
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        TestClass1 cls1 = null;
        TestClass1 cls2 = null;

        try
        {
            cls1 = testObject.resolve(TestClass1.class);
            cls2 = testObject.resolve(TestClass1.class);
        }
        catch(AbstractTypeException | NoSuitableConstructorException | NewInstantanceException e)
        {
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls1);
        Assert.assertNotNull(cls2);
        Assert.assertSame(cls1, cls2);
    }

    @Test
    public void testRegisterWhenSingleClassChangesSingleton()
    {
        try
        {
            testObject.registerType(TestClass1.class, true);
        }
        catch(AbstractTypeException e)
        {
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        TestClass1 cls11 = null;
        TestClass1 cls12 = null;

        try
        {
            cls11 = testObject.resolve(TestClass1.class);
            cls12 = testObject.resolve(TestClass1.class);
        }
        catch(AbstractTypeException | NoSuitableConstructorException | NewInstantanceException e)
        {
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls11);
        Assert.assertNotNull(cls12);
        Assert.assertSame(cls11, cls12);

        try
        {
            testObject.registerType(TestClass1.class, false);
        }
        catch(AbstractTypeException e)
        {
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        TestClass1 cls21 = null;
        TestClass1 cls22 = null;

        try
        {
            cls21 = testObject.resolve(TestClass1.class);
            cls22 = testObject.resolve(TestClass1.class);
        }
        catch(AbstractTypeException | NoSuitableConstructorException | NewInstantanceException e)
        {
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls21);
        Assert.assertNotNull(cls22);
        Assert.assertNotSame(cls21, cls22);
    }

    @Test(expected = AbstractTypeException.class)
    public void testRegisterWhenSingleClassIsInterface()
        throws AbstractTypeException
    {
        testObject.registerType(TestInterface1.class);
    }

    @Test(expected = AbstractTypeException.class)
    public void testRegisterWhenSingleClassIsAbstract()
        throws AbstractTypeException
    {
        testObject.registerType(TestAbstractClass4.class);
    }

    @Test
    public void testRegisterWhenInheritanceFromInterface()
    {
        testObject.registerType(TestInterface1.class, TestClass1.class);

        TestInterface1 cls1 = null;
        TestInterface1 cls2 = null;

        try
        {
            cls1 = testObject.resolve(TestInterface1.class);
            cls2 = testObject.resolve(TestInterface1.class);
        }
        catch(AbstractTypeException | NoSuitableConstructorException | NewInstantanceException e)
        {
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls1);
        Assert.assertNotNull(cls2);
        Assert.assertNotSame(cls1, cls2);
        Assert.assertTrue(cls1 instanceof TestClass1);
        Assert.assertTrue(cls2 instanceof TestClass1);
    }

    @Test
    public void testRegisterWhenInheritanceFromInterfaceAsSingleton()
    {
        testObject.registerType(TestInterface1.class, TestClass1.class, true);

        TestInterface1 cls1 = null;
        TestInterface1 cls2 = null;

        try
        {
            cls1 = testObject.resolve(TestInterface1.class);
            cls2 = testObject.resolve(TestInterface1.class);
        }
        catch(AbstractTypeException | NoSuitableConstructorException | NewInstantanceException e)
        {
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls1);
        Assert.assertNotNull(cls2);
        Assert.assertSame(cls1, cls2);
        Assert.assertTrue(cls1 instanceof TestClass1);
        Assert.assertTrue(cls2 instanceof TestClass1);
    }

    @Test
    public void testRegisterWhenInheritanceFromInterfaceChangesSingleton()
    {
        testObject.registerType(TestInterface1.class, TestClass1.class, true);

        TestInterface1 cls11 = null;
        TestInterface1 cls12 = null;

        try
        {
            cls11 = testObject.resolve(TestInterface1.class);
            cls12 = testObject.resolve(TestInterface1.class);
        }
        catch(AbstractTypeException | NoSuitableConstructorException | NewInstantanceException e)
        {
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls11);
        Assert.assertNotNull(cls12);
        Assert.assertSame(cls11, cls12);
        Assert.assertTrue(cls11 instanceof TestClass1);
        Assert.assertTrue(cls12 instanceof TestClass1);

        testObject.registerType(TestInterface1.class, TestClass1.class, false);

        TestInterface1 cls21 = null;
        TestInterface1 cls22 = null;

        try
        {
            cls21 = testObject.resolve(TestInterface1.class);
            cls22 = testObject.resolve(TestInterface1.class);
        }
        catch(AbstractTypeException | NoSuitableConstructorException | NewInstantanceException e)
        {
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls21);
        Assert.assertNotNull(cls22);
        Assert.assertNotSame(cls21, cls22);
        Assert.assertTrue(cls21 instanceof TestClass1);
        Assert.assertTrue(cls22 instanceof TestClass1);
    }

    @Test
    public void testRegisterWhenInheritanceFromInterfaceChangesClass()
    {
        testObject.registerType(TestInterface1.class, TestClass1.class);

        TestInterface1 cls1 = null;

        try
        {
            cls1 = testObject.resolve(TestInterface1.class);
        }
        catch(AbstractTypeException | NoSuitableConstructorException | NewInstantanceException e)
        {
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls1);
        Assert.assertTrue(cls1 instanceof TestClass1);

        testObject.registerType(TestInterface1.class, TestClass10.class);

        TestInterface1 cls10 = null;

        try
        {
            cls10 = testObject.resolve(TestInterface1.class);
        }
        catch(AbstractTypeException | NoSuitableConstructorException | NewInstantanceException e)
        {
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls10);
        Assert.assertTrue(cls10 instanceof TestClass10);
    }

    @Test
    public void testRegisterWhenInheritanceFromAbstractClass()
    {
        testObject.registerType(TestAbstractClass4.class, TestClass4.class);

        TestAbstractClass4 cls = null;

        try
        {
            cls = testObject.resolve(TestAbstractClass4.class);
        }
        catch(AbstractTypeException | NoSuitableConstructorException | NewInstantanceException e)
        {
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls);
        Assert.assertTrue(cls instanceof TestClass4);
    }

    @Test
    public void testRegisterWhenTwoStepsOfHierarchy()
    {
        testObject.registerType(TestInterface4.class, TestAbstractClass4.class);
        testObject.registerType(TestAbstractClass4.class, TestClass4.class);

        TestInterface4 cls = null;
        try
        {
            cls = testObject.resolve(TestInterface4.class);
        }
        catch(AbstractTypeException | NoSuitableConstructorException | NewInstantanceException e)
        {
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls);
        Assert.assertTrue(cls instanceof TestClass4);
    }

    @Test
    public void testResolveWhenClassHasDefaultConstructorOnly()
    {
        TestClass1 cls = null;

        try
        {
            cls = testObject.resolve(TestClass1.class);
        }
        catch(AbstractTypeException | NoSuitableConstructorException | NewInstantanceException e)
        {
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls);
        Assert.assertTrue(cls instanceof TestClass1);
    }

    @Test
    public void testResolveWhenClassInheritsFromOtherClass()
    {
        TestClass20 cls = null;

        try
        {
            cls = testObject.resolve(TestClass20.class);
        }
        catch(AbstractTypeException | NoSuitableConstructorException | NewInstantanceException e)
        {
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls);
        Assert.assertTrue(cls instanceof TestClass20);
    }

    @Test
    public void testResolveWhenClassInheritsFromAbstractClass()
    {
        TestClass4 cls = null;

        try
        {
            cls = testObject.resolve(TestClass4.class);
        }
        catch(AbstractTypeException | NoSuitableConstructorException | NewInstantanceException e)
        {
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls);
        Assert.assertTrue(cls instanceof TestClass4);
    }

    @Test(expected = NoSuitableConstructorException.class)
    public void testResolveWhenClassHasNoDefaultConstructor()
        throws AbstractTypeException, NoSuitableConstructorException, NewInstantanceException
    {
        testObject.resolve(TestClass2.class);
    }

    @Test
    public void testResolveWhenClassHasDefaultConstructorAndParameterConstructor()
    {
        TestClass3 cls = null;
        try
        {
            cls = testObject.resolve(TestClass3.class);
        }
        catch(AbstractTypeException | NoSuitableConstructorException | NewInstantanceException e)
        {
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls);
        Assert.assertTrue(cls instanceof TestClass3);
    }

    @Test(expected = AbstractTypeException.class)
    public void testResolveWhenInterface()
        throws AbstractTypeException, NoSuitableConstructorException, NewInstantanceException
    {
        testObject.resolve(TestInterface1.class);
    }

    @Test(expected = AbstractTypeException.class)
    public void testResolveWhenAbstractClass()
        throws AbstractTypeException, NoSuitableConstructorException, NewInstantanceException
    {
        testObject.resolve(TestAbstractClass4.class);
    }
}
