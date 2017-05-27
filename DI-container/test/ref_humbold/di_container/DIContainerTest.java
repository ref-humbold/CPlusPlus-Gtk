package ref_humbold.di_container;

import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

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
            testObject.registerType(TestClassWithDefaultConstructorOnly.class);
        }
        catch(Exception e)
        {
            e.printStackTrace();
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        TestClassWithDefaultConstructorOnly cls1 = null;
        TestClassWithDefaultConstructorOnly cls2 = null;

        try
        {
            cls1 = testObject.resolve(TestClassWithDefaultConstructorOnly.class);
            cls2 = testObject.resolve(TestClassWithDefaultConstructorOnly.class);
        }
        catch(Exception e)
        {
            e.printStackTrace();
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
            testObject.registerType(TestClassWithDefaultConstructorOnly.class, true);
        }
        catch(Exception e)
        {
            e.printStackTrace();
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        TestClassWithDefaultConstructorOnly cls1 = null;
        TestClassWithDefaultConstructorOnly cls2 = null;

        try
        {
            cls1 = testObject.resolve(TestClassWithDefaultConstructorOnly.class);
            cls2 = testObject.resolve(TestClassWithDefaultConstructorOnly.class);
        }
        catch(Exception e)
        {
            e.printStackTrace();
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
            testObject.registerType(TestClassWithDefaultConstructorOnly.class, true);
        }
        catch(Exception e)
        {
            e.printStackTrace();
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        TestClassWithDefaultConstructorOnly cls11 = null;
        TestClassWithDefaultConstructorOnly cls12 = null;

        try
        {
            cls11 = testObject.resolve(TestClassWithDefaultConstructorOnly.class);
            cls12 = testObject.resolve(TestClassWithDefaultConstructorOnly.class);
        }
        catch(Exception e)
        {
            e.printStackTrace();
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls11);
        Assert.assertNotNull(cls12);
        Assert.assertSame(cls11, cls12);

        try
        {
            testObject.registerType(TestClassWithDefaultConstructorOnly.class, false);
        }
        catch(Exception e)
        {
            e.printStackTrace();
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        TestClassWithDefaultConstructorOnly cls21 = null;
        TestClassWithDefaultConstructorOnly cls22 = null;

        try
        {
            cls21 = testObject.resolve(TestClassWithDefaultConstructorOnly.class);
            cls22 = testObject.resolve(TestClassWithDefaultConstructorOnly.class);
        }
        catch(Exception e)
        {
            e.printStackTrace();
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
        testObject.registerType(TestInterface.class);
    }

    @Test(expected = AbstractTypeException.class)
    public void testRegisterWhenSingleClassIsAbstractClass()
        throws AbstractTypeException
    {
        testObject.registerType(TestAbstractClass.class);
    }

    @Test
    public void testRegisterWhenInheritanceFromInterface()
    {
        testObject.registerType(TestInterface.class, TestClassWithDefaultConstructorOnly.class);

        TestInterface cls1 = null;
        TestInterface cls2 = null;

        try
        {
            cls1 = testObject.resolve(TestInterface.class);
            cls2 = testObject.resolve(TestInterface.class);
        }
        catch(Exception e)
        {
            e.printStackTrace();
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls1);
        Assert.assertNotNull(cls2);
        Assert.assertNotSame(cls1, cls2);
        Assert.assertTrue(cls1 instanceof TestClassWithDefaultConstructorOnly);
        Assert.assertTrue(cls2 instanceof TestClassWithDefaultConstructorOnly);
    }

    @Test
    public void testRegisterWhenInheritanceFromInterfaceAsSingleton()
    {
        testObject.registerType(TestInterface.class, TestClassWithDefaultConstructorOnly.class,
                                true);

        TestInterface cls1 = null;
        TestInterface cls2 = null;

        try
        {
            cls1 = testObject.resolve(TestInterface.class);
            cls2 = testObject.resolve(TestInterface.class);
        }
        catch(Exception e)
        {
            e.printStackTrace();
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls1);
        Assert.assertNotNull(cls2);
        Assert.assertSame(cls1, cls2);
        Assert.assertTrue(cls1 instanceof TestClassWithDefaultConstructorOnly);
        Assert.assertTrue(cls2 instanceof TestClassWithDefaultConstructorOnly);
    }

    @Test
    public void testRegisterWhenInheritanceFromInterfaceChangesSingleton()
    {
        testObject.registerType(TestInterface.class, TestClassWithDefaultConstructorOnly.class,
                                true);

        TestInterface cls11 = null;
        TestInterface cls12 = null;

        try
        {
            cls11 = testObject.resolve(TestInterface.class);
            cls12 = testObject.resolve(TestInterface.class);
        }
        catch(Exception e)
        {
            e.printStackTrace();
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls11);
        Assert.assertNotNull(cls12);
        Assert.assertSame(cls11, cls12);
        Assert.assertTrue(cls11 instanceof TestClassWithDefaultConstructorOnly);
        Assert.assertTrue(cls12 instanceof TestClassWithDefaultConstructorOnly);

        testObject.registerType(TestInterface.class, TestClassWithDefaultConstructorOnly.class,
                                false);

        TestInterface cls21 = null;
        TestInterface cls22 = null;

        try
        {
            cls21 = testObject.resolve(TestInterface.class);
            cls22 = testObject.resolve(TestInterface.class);
        }
        catch(Exception e)
        {
            e.printStackTrace();
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls21);
        Assert.assertNotNull(cls22);
        Assert.assertNotSame(cls21, cls22);
        Assert.assertTrue(cls21 instanceof TestClassWithDefaultConstructorOnly);
        Assert.assertTrue(cls22 instanceof TestClassWithDefaultConstructorOnly);
    }

    @Test
    public void testRegisterWhenInheritanceFromInterfaceChangesClass()
    {
        testObject.registerType(TestInterface.class, TestClassWithDefaultConstructorOnly.class);

        TestInterface cls1 = null;

        try
        {
            cls1 = testObject.resolve(TestInterface.class);
        }
        catch(Exception e)
        {
            e.printStackTrace();
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls1);
        Assert.assertTrue(cls1 instanceof TestClassWithDefaultConstructorOnly);

        testObject.registerType(TestInterface.class,
                                TestClassWithDefaultAndParameterConstructor.class);

        TestInterface cls3 = null;

        try
        {
            cls3 = testObject.resolve(TestInterface.class);
        }
        catch(Exception e)
        {
            e.printStackTrace();
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls3);
        Assert.assertTrue(cls3 instanceof TestClassWithDefaultAndParameterConstructor);
    }

    @Test
    public void testRegisterWhenInheritanceFromAbstractClass()
    {
        testObject.registerType(TestAbstractClass.class, TestClassInheritsFromAbstractClass.class);

        TestAbstractClass cls = null;

        try
        {
            cls = testObject.resolve(TestAbstractClass.class);
        }
        catch(Exception e)
        {
            e.printStackTrace();
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls);
        Assert.assertTrue(cls instanceof TestClassInheritsFromAbstractClass);
    }

    @Test
    public void testRegisterWhenInheritanceFromConcreteClass()
    {
        testObject.registerType(TestClassWithParameterConstructorOnly.class,
                                TestClassInheritsFromClassWithParameterConstructorOnly.class);

        TestClassWithParameterConstructorOnly cls = null;

        try
        {
            cls = testObject.resolve(TestClassWithParameterConstructorOnly.class);
        }
        catch(Exception e)
        {
            e.printStackTrace();
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls);
        Assert.assertTrue(cls instanceof TestClassInheritsFromClassWithParameterConstructorOnly);
    }

    @Test
    public void testRegisterWhenTwoStepsOfHierarchy()
    {
        testObject.registerType(TestInterface.class, TestAbstractClass.class);
        testObject.registerType(TestAbstractClass.class, TestClassInheritsFromAbstractClass.class);

        TestInterface cls = null;

        try
        {
            cls = testObject.resolve(TestInterface.class);
        }
        catch(Exception e)
        {
            e.printStackTrace();
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls);
        Assert.assertTrue(cls instanceof TestClassInheritsFromAbstractClass);
    }

    @Test
    public void testRegisterInstanceWhenInterface()
    {
        TestClassWithDefaultConstructorOnly obj = new TestClassWithDefaultConstructorOnly();

        testObject.registerInstance(TestInterface.class, obj);

        TestInterface cls = null;

        try
        {
            cls = testObject.resolve(TestInterface.class);
        }
        catch(Exception e)
        {
            e.printStackTrace();
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls);
        Assert.assertTrue(cls instanceof TestClassWithDefaultConstructorOnly);
        Assert.assertSame(obj, cls);
    }

    @Test
    public void testRegisterInstanceWhenAbstractClass()
    {
        TestClassInheritsFromAbstractClass obj = new TestClassInheritsFromAbstractClass();

        testObject.registerInstance(TestAbstractClass.class, obj);

        TestAbstractClass cls = null;

        try
        {
            cls = testObject.resolve(TestAbstractClass.class);
        }
        catch(Exception e)
        {
            e.printStackTrace();
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls);
        Assert.assertTrue(cls instanceof TestClassInheritsFromAbstractClass);
        Assert.assertSame(obj, cls);
    }

    @Test
    public void testRegisterInstanceWhenSameConcreteClass()
    {
        TestClassWithDefaultAndParameterConstructor obj = new TestClassWithDefaultAndParameterConstructor();

        testObject.registerInstance(TestClassWithDefaultAndParameterConstructor.class, obj);

        TestClassWithDefaultAndParameterConstructor cls = null;

        try
        {
            cls = testObject.resolve(TestClassWithDefaultAndParameterConstructor.class);
        }
        catch(Exception e)
        {
            e.printStackTrace();
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls);
        Assert.assertTrue(cls instanceof TestClassWithDefaultAndParameterConstructor);
        Assert.assertSame(obj, cls);
    }

    @Test
    public void testRegisterInstanceWhenDerivedConcreteClass()
    {
        TestClassInheritsFromClassWithParameterConstructorOnly obj = new TestClassInheritsFromClassWithParameterConstructorOnly();

        testObject.registerInstance(TestClassWithParameterConstructorOnly.class, obj);

        TestClassWithParameterConstructorOnly cls = null;

        try
        {
            cls = testObject.resolve(TestClassWithParameterConstructorOnly.class);
        }
        catch(Exception e)
        {
            e.printStackTrace();
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls);
        Assert.assertTrue(cls instanceof TestClassInheritsFromClassWithParameterConstructorOnly);
        Assert.assertSame(obj, cls);
    }

    @Test(expected = IllegalArgumentException.class)
    public void testRegisterInstanceWhenInstanceIsNull()
        throws IllegalArgumentException
    {
        testObject.registerInstance(TestClassWithDefaultAndParameterConstructor.class, null);
    }

    @Test
    public void testResolveWhenClassHasDefaultConstructorOnly()
    {
        TestClassWithDefaultConstructorOnly cls = null;

        try
        {
            cls = testObject.resolve(TestClassWithDefaultConstructorOnly.class);
        }
        catch(Exception e)
        {
            e.printStackTrace();
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls);
        Assert.assertTrue(cls instanceof TestClassWithDefaultConstructorOnly);
    }

    @Test
    public void testResolveWhenClassInheritsFromConcreteClass()
    {
        TestClassInheritsFromClassWithParameterConstructorOnly cls = null;

        try
        {
            cls = testObject.resolve(TestClassInheritsFromClassWithParameterConstructorOnly.class);
        }
        catch(Exception e)
        {
            e.printStackTrace();
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls);
        Assert.assertTrue(cls instanceof TestClassInheritsFromClassWithParameterConstructorOnly);
    }

    @Test
    public void testResolveWhenClassInheritsFromAbstractClass()
    {
        TestClassInheritsFromAbstractClass cls = null;

        try
        {
            cls = testObject.resolve(TestClassInheritsFromAbstractClass.class);
        }
        catch(Exception e)
        {
            e.printStackTrace();
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls);
        Assert.assertTrue(cls instanceof TestClassInheritsFromAbstractClass);
    }

    @Test(expected = MissingDependenciesException.class)
    public void testResolveWhenClassHasParameterConstructorWithoutRegisteredParameter()
        throws AbstractTypeException, NoSuitableConstructorException,
        MultipleAnnotatedConstructorsException, CircularDependenciesException,
        MissingDependenciesException

    {
        testObject.resolve(TestClassWithParameterConstructorOnly.class);
    }

    @Test
    public void testResolveWhenClassHasParameterConstructorWithRegisteredPrimitiveParameter()
    {
        testObject.registerInstance(int.class, 10);

        TestClassWithParameterConstructorOnly cls = null;

        try
        {
            cls = testObject.resolve(TestClassWithParameterConstructorOnly.class);
        }
        catch(Exception e)
        {
            e.printStackTrace();
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls);
        Assert.assertTrue(cls instanceof TestClassWithParameterConstructorOnly);
    }

    @Test
    public void testResolveWhenClassHasParameterConstructorWithRegisteredReferenceParameter()
    {
        testObject.registerInstance(Integer.class, 10);

        TestClassWithParameterConstructorOnly cls = null;

        try
        {
            cls = testObject.resolve(TestClassWithParameterConstructorOnly.class);
        }
        catch(Exception e)
        {
            e.printStackTrace();
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls);
        Assert.assertTrue(cls instanceof TestClassWithParameterConstructorOnly);
    }

    @Test
    public void testResolveWhenClassHasDefaultAndParameterConstructorWithoutRegisteredParameter()
    {
        TestClassWithDefaultAndParameterConstructor cls = null;
        try
        {
            cls = testObject.resolve(TestClassWithDefaultAndParameterConstructor.class);
        }
        catch(Exception e)
        {
            e.printStackTrace();
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls);
        Assert.assertTrue(cls instanceof TestClassWithDefaultAndParameterConstructor);
    }

    @Test(expected = AbstractTypeException.class)
    public void testResolveWhenInterface()
        throws AbstractTypeException, NoSuitableConstructorException,
        MultipleAnnotatedConstructorsException, CircularDependenciesException,
        MissingDependenciesException

    {
        testObject.resolve(TestInterface.class);
    }

    @Test(expected = AbstractTypeException.class)
    public void testResolveWhenAbstractClass()
        throws AbstractTypeException, NoSuitableConstructorException,
        MultipleAnnotatedConstructorsException, CircularDependenciesException,
        MissingDependenciesException

    {
        testObject.resolve(TestAbstractClass.class);
    }

    @Test(expected = MultipleAnnotatedConstructorsException.class)
    public void testResolveWhenMultipleAnnotatedConstructors()
        throws AbstractTypeException, NoSuitableConstructorException,
        MultipleAnnotatedConstructorsException, CircularDependenciesException,
        MissingDependenciesException

    {
        testObject.resolve(TestClassWithMultipleAnnotatedConstructors.class);
    }

    @Test(expected = NoSuitableConstructorException.class)
    public void testResolveWhenNoPublicConstructors()
        throws AbstractTypeException, NoSuitableConstructorException,
        MultipleAnnotatedConstructorsException, CircularDependenciesException,
        MissingDependenciesException

    {
        testObject.resolve(TestClassWithPrivateConstructorOnly.class);
    }

    @Test(expected = NoSuitableConstructorException.class)
    public void testResolveWhenNoDeclaredConstructors()
        throws AbstractTypeException, NoSuitableConstructorException,
        MultipleAnnotatedConstructorsException, CircularDependenciesException,
        MissingDependenciesException

    {
        testObject.resolve(TestClassWithNoDeclaredConstructors.class);
    }

    @Test
    public void testResolveDependenciesWithRegisteredInstance()
    {
        String string = "String";

        testObject.registerInstance(String.class, string);
        testObject.registerType(TestDependencyInterface1.class, TestDependencyClass1.class);
        testObject.registerType(TestDependencyInterface2.class, TestDependencyClass2.class);
        testObject.registerType(TestDependencyInterface3.class, TestDependencyClass3.class);
        testObject.registerType(TestDependencyInterface4.class, TestDependencyClass4.class);

        TestDependencyInterface4 cls = null;

        try
        {
            cls = testObject.resolve(TestDependencyInterface4.class);
        }
        catch(Exception e)
        {
            e.printStackTrace();
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls);
        Assert.assertNotNull(cls.getObject2());
        Assert.assertNotNull(cls.getObject3());
        Assert.assertNotNull(cls.getObject2().getObject());
        Assert.assertNotNull(cls.getObject3().getString());
        Assert.assertEquals(string, cls.getObject3().getString());
        Assert.assertTrue(cls instanceof TestDependencyClass4);
    }

    @Test
    public void testResolveDependenciesWithoutAnnotatedConstructorsWithAllDependencies()
    {
        testObject.registerType(TestDependencyInterface1.class, TestDependencyClass1.class);
        testObject.registerType(TestDependencyInterface2.class, TestDependencyClass2.class);
        testObject.registerType(TestDependencyInterface3.class, TestDependencyClass3.class);
        testObject.registerType(TestDependencyInterface4.class, TestDependencyClass4.class);

        TestDependencyInterface4 cls = null;

        try
        {
            cls = testObject.resolve(TestDependencyInterface4.class);
        }
        catch(Exception e)
        {
            e.printStackTrace();
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls);
        Assert.assertNotNull(cls.getObject2());
        Assert.assertNotNull(cls.getObject3());
        Assert.assertNotNull(cls.getObject2().getObject());
        Assert.assertNotNull(cls.getObject3().getString());
        Assert.assertEquals("", cls.getObject3().getString());
        Assert.assertTrue(cls instanceof TestDependencyClass4);
    }

    @Test
    public void testResolveDependenciesWithoutAnnotatedConstructorsWithoutSomeDependencies()
    {
        testObject.registerType(TestDependencyInterface1.class, TestDependencyClass1.class);
        testObject.registerType(TestDependencyInterface2.class, TestDependencyClass2.class);
        testObject.registerType(TestDependencyInterface4.class, TestDependencyClass4.class);

        TestDependencyInterface4 cls = null;

        try
        {
            cls = testObject.resolve(TestDependencyInterface4.class);
        }
        catch(Exception e)
        {
            e.printStackTrace();
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls);
        Assert.assertNotNull(cls.getObject2());
        Assert.assertNull(cls.getObject3());
        Assert.assertNotNull(cls.getObject2().getObject());
        Assert.assertTrue(cls instanceof TestDependencyClass4);
    }

    @Test
    public void testResolveDependenciesWithAnnotatedConstructor()
    {
        testObject.registerType(TestDependencyInterface1.class, TestDependencyClass1.class);
        testObject.registerType(TestDependencyInterface2.class, TestDependencyClass2.class);
        testObject.registerType(TestDependencyInterface3.class, TestDependencyClass3.class);
        testObject.registerType(TestDependencyInterface5.class, TestDependencyClass5.class);

        TestDependencyInterface5 cls = null;

        try
        {
            cls = testObject.resolve(TestDependencyInterface5.class);
        }
        catch(Exception e)
        {
            e.printStackTrace();
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls);
        Assert.assertNotNull(cls.getObject2());
        Assert.assertNotNull(cls.getObject3());
        Assert.assertNotNull(cls.getObject2().getObject());
        Assert.assertNotNull(cls.getObject3().getString());
        Assert.assertEquals("", cls.getObject3().getString());
        Assert.assertTrue(cls instanceof TestDependencyClass5);
    }

    @Test(expected = MissingDependenciesException.class)
    public void testResolveDependenciesWithAnnotatedConstructorWithoutSomeDependencies()
        throws AbstractTypeException, NoSuitableConstructorException,
        MultipleAnnotatedConstructorsException, CircularDependenciesException,
        MissingDependenciesException

    {
        testObject.registerType(TestDependencyInterface2.class, TestDependencyClass2.class);
        testObject.registerType(TestDependencyInterface8.class, TestDependencyClass8.class);
        testObject.registerType(TestDependencyInterface9.class, TestDependencyClass9.class);

        testObject.resolve(TestDependencyInterface9.class);
    }

    @Test
    public void testResolveDiamondDependenciesWithoutSingleton()
    {
        testObject.registerType(TestDependencyInterface1.class, TestDependencyClass1.class);
        testObject.registerType(TestDependencyInterface2.class, TestDependencyClass2.class);
        testObject.registerType(TestDependencyInterface8.class, TestDependencyClass8.class);
        testObject.registerType(TestDependencyInterface9.class, TestDependencyClass9.class);

        TestDependencyInterface9 cls = null;

        try
        {
            cls = testObject.resolve(TestDependencyInterface9.class);
        }
        catch(Exception e)
        {
            e.printStackTrace();
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls);
        Assert.assertNotNull(cls.getObject2());
        Assert.assertNotNull(cls.getObject8());
        Assert.assertNotNull(cls.getObject2().getObject());
        Assert.assertNotNull(cls.getObject8().getObject());
        Assert.assertNotSame(cls.getObject2().getObject(), cls.getObject8().getObject());
        Assert.assertTrue(cls instanceof TestDependencyClass9);
    }

    @Test
    public void testResolveDiamondDependenciesWithSingleton()
    {
        testObject.registerType(TestDependencyInterface1.class, TestDependencyClass1.class, true);
        testObject.registerType(TestDependencyInterface2.class, TestDependencyClass2.class);
        testObject.registerType(TestDependencyInterface8.class, TestDependencyClass8.class);
        testObject.registerType(TestDependencyInterface9.class, TestDependencyClass9.class);

        TestDependencyInterface9 cls = null;

        try
        {
            cls = testObject.resolve(TestDependencyInterface9.class);
        }
        catch(Exception e)
        {
            e.printStackTrace();
            Assert.fail("An instance of " + e.getClass().getSimpleName() + " was thrown.");
        }

        Assert.assertNotNull(cls);
        Assert.assertNotNull(cls.getObject2());
        Assert.assertNotNull(cls.getObject8());
        Assert.assertNotNull(cls.getObject2().getObject());
        Assert.assertNotNull(cls.getObject8().getObject());
        Assert.assertSame(cls.getObject2().getObject(), cls.getObject8().getObject());
        Assert.assertTrue(cls instanceof TestDependencyClass9);
    }

    @Test(expected = CircularDependenciesException.class)
    public void testResolveCircularDependencies()
        throws AbstractTypeException, NoSuitableConstructorException,
        MultipleAnnotatedConstructorsException, CircularDependenciesException,
        MissingDependenciesException

    {
        testObject.registerType(TestDependencyInterface6.class, TestDependencyClass6.class);
        testObject.registerType(TestDependencyInterface7.class, TestDependencyClass7.class);

        testObject.resolve(TestDependencyInterface7.class);
    }
}

interface TestInterface
{
}

interface TestDependencyInterface1
{
}

interface TestDependencyInterface2
{
    TestDependencyInterface1 getObject();
}

interface TestDependencyInterface3
{
    String getString();
}

interface TestDependencyInterface4
{
    TestDependencyInterface2 getObject2();

    TestDependencyInterface3 getObject3();
}

interface TestDependencyInterface5
{
    TestDependencyInterface2 getObject2();

    TestDependencyInterface3 getObject3();
}

interface TestDependencyInterface6
{
}

interface TestDependencyInterface7
{
}

interface TestDependencyInterface8
{
    TestDependencyInterface1 getObject();
}

interface TestDependencyInterface9
{
    TestDependencyInterface2 getObject2();

    TestDependencyInterface8 getObject8();
}

abstract class TestAbstractClass
    implements TestInterface
{
    public TestAbstractClass()
    {
    }
}

class TestClassWithDefaultConstructorOnly
    implements TestInterface
{
    public TestClassWithDefaultConstructorOnly()
    {
    }
}

class TestClassWithParameterConstructorOnly
    implements TestInterface
{
    int number;

    public TestClassWithParameterConstructorOnly(int number)
    {
        this.number = number;
    }
}

class TestClassInheritsFromClassWithParameterConstructorOnly
    extends TestClassWithParameterConstructorOnly
{
    public TestClassInheritsFromClassWithParameterConstructorOnly()
    {
        super(1);
    }
}

class TestClassWithDefaultAndParameterConstructor
    implements TestInterface
{
    String text;

    public TestClassWithDefaultAndParameterConstructor()
    {
        this.text = "";
    }

    public TestClassWithDefaultAndParameterConstructor(String text)
    {
        this.text = text;
    }
}

class TestClassInheritsFromAbstractClass
    extends TestAbstractClass
{
    public TestClassInheritsFromAbstractClass()
    {
        super();
    }
}

class TestClassWithAnnotatedDefaultConstructorOnly
{
    @DependencyConstructor
    public TestClassWithAnnotatedDefaultConstructorOnly()
    {
    }
}

class TestClassWithMultipleAnnotatedConstructors
{
    String text;

    @DependencyConstructor
    public TestClassWithMultipleAnnotatedConstructors()
    {
    }

    @DependencyConstructor
    public TestClassWithMultipleAnnotatedConstructors(String text)
    {
        this.text = text;
    }
}

class TestClassWithPrivateConstructorOnly
{
    private TestClassWithPrivateConstructorOnly()
    {
    }
}

class TestClassWithNoDeclaredConstructors
{
}

class TestDependencyClass1
    implements TestDependencyInterface1
{
    public TestDependencyClass1()
    {
    }
}

class TestDependencyClass2
    implements TestDependencyInterface2
{
    private TestDependencyInterface1 object;

    public TestDependencyClass2()
    {
        this.object = null;
    }

    public TestDependencyClass2(TestDependencyInterface1 object)
    {
        this.object = object;
    }

    @Override
    public TestDependencyInterface1 getObject()
    {
        return object;
    }
}

class TestDependencyClass3
    implements TestDependencyInterface3
{
    private String text;

    public TestDependencyClass3()
    {
        this.text = "";
    }

    public TestDependencyClass3(String text)
    {
        this.text = text;
    }

    @Override
    public String getString()
    {
        return text;
    }
}

class TestDependencyClass4
    implements TestDependencyInterface4
{
    private TestDependencyInterface2 object2;
    private TestDependencyInterface3 object3;

    public TestDependencyClass4(TestDependencyInterface2 object2)
    {
        this.object2 = object2;
        this.object3 = null;
    }

    public TestDependencyClass4(TestDependencyInterface2 object2, TestDependencyInterface3 object3)
    {
        this.object2 = object2;
        this.object3 = object3;
    }

    @Override
    public TestDependencyInterface2 getObject2()
    {
        return object2;
    }

    @Override
    public TestDependencyInterface3 getObject3()
    {
        return object3;
    }
}

class TestDependencyClass5
    implements TestDependencyInterface5
{
    private TestDependencyInterface2 object2;
    private TestDependencyInterface3 object3;

    @DependencyConstructor
    public TestDependencyClass5(TestDependencyInterface2 object2, TestDependencyInterface3 object3)
    {
        this.object2 = object2;
        this.object3 = object3;
    }

    @Override
    public TestDependencyInterface2 getObject2()
    {
        return object2;
    }

    @Override
    public TestDependencyInterface3 getObject3()
    {
        return object3;
    }
}

class TestDependencyClass6
    implements TestDependencyInterface6
{
    private TestDependencyInterface7 object;

    public TestDependencyClass6(TestDependencyInterface7 object)
    {
        this.object = object;
    }
}

class TestDependencyClass7
    implements TestDependencyInterface7
{
    private TestDependencyInterface6 object;

    public TestDependencyClass7(TestDependencyInterface6 object)
    {
        this.object = object;
    }
}

class TestDependencyClass8
    implements TestDependencyInterface8
{
    private TestDependencyInterface1 object;

    public TestDependencyClass8(TestDependencyInterface1 object)
    {
        this.object = object;
    }

    @Override
    public TestDependencyInterface1 getObject()
    {
        return object;
    }
}

class TestDependencyClass9
    implements TestDependencyInterface9
{
    private TestDependencyInterface2 object2;
    private TestDependencyInterface8 object8;

    @DependencyConstructor
    public TestDependencyClass9(TestDependencyInterface2 object2, TestDependencyInterface8 object8)
    {
        this.object2 = object2;
        this.object8 = object8;
    }

    @Override
    public TestDependencyInterface2 getObject2()
    {
        return object2;
    }

    @Override
    public TestDependencyInterface8 getObject8()
    {
        return object8;
    }
}
