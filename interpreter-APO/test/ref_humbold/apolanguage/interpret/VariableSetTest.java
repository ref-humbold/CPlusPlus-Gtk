package ref_humbold.apolanguage.interpret;

import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import ref_humbold.apolanguage.errors.SymbolError;

public class VariableSetTest
{
    private VariableSet testObject;

    @Before
    public void setUp()
        throws Exception
    {
        testObject = new VariableSet();
    }

    @After
    public void tearDown()
        throws Exception
    {
        testObject = null;
    }

    @Test
    public void testGetSetValueWhenNoArguments()
    {
        String name = "var";
        int result = 1;

        testObject.setValue(name);

        try
        {
            result = testObject.getValue(name);
        }
        catch(SymbolError e)
        {
            e.printStackTrace();
            Assert.fail("Unexpected SymbolError was thrown.");
        }

        Assert.assertEquals(0, result);
    }

    @Test(expected = SymbolError.class)
    public void testGetValueWhenVariableNotSet()
        throws SymbolError
    {
        String name = "var";

        testObject.getValue(name);
    }

    @Test
    public void testGetSetValueWhenArgument()
    {
        String name = "var";
        int value = 10;
        int result = 0;

        testObject.setValue(name, value);

        try
        {
            result = testObject.getValue(name);
        }
        catch(SymbolError e)
        {
            e.printStackTrace();
            Assert.fail("Unexpected SymbolError was thrown.");
        }

        Assert.assertEquals(value, result);
    }

    @Test
    public void testContains()
    {
        String name = "var";

        testObject.setValue(name);

        Assert.assertTrue(testObject.contains(name));
    }

    @Test
    public void testGetSetValueByNumber()
    {
        String name = "var";
        int value = 10;
        int result1 = 0;
        int result2 = 0;

        testObject.setValue(name);

        int number = testObject.getNumber(name);

        try
        {
            testObject.setValue(number, value);
            result1 = testObject.getValue(name);
            result2 = testObject.getValue(number);
        }
        catch(SymbolError e)
        {
            e.printStackTrace();
            Assert.fail("Unexpected SymbolError was thrown.");
        }

        Assert.assertEquals(value, result1);
        Assert.assertEquals(value, result2);
    }

    @Test(expected = SymbolError.class)
    public void testGetSetValueByNumberWhenVariableNotSet()
        throws SymbolError
    {
        int value = 10;
        int number = 1;

        testObject.setValue(number, value);
    }
}
