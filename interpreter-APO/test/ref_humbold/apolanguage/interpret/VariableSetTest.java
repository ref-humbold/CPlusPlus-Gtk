package ref_humbold.apolanguage.interpret;

import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

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
    public void testGetSetValueNoArguments()
    {
        String name = "var";

        testObject.setValue(name);

        int result = testObject.getValue(name);

        Assert.assertEquals(0, result);
    }

    @Test
    public void testGetSetValueWithArgument()
    {
        String name = "var";
        int value = 10;

        testObject.setValue(name, value);

        int result = testObject.getValue(name);

        Assert.assertEquals(value, result);
    }

    @Test
    public void testContains()
    {
        String name = "var";

        testObject.setValue(name);

        Assert.assertTrue(testObject.contains(name));
    }
}
