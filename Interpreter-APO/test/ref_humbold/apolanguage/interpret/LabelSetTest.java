package ref_humbold.apolanguage.interpret;

import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import ref_humbold.apolanguage.errors.LabelException;
import ref_humbold.apolanguage.instructions.Instruction;
import ref_humbold.apolanguage.instructions.NOPInstruction;

public class LabelSetTest
{
    private LabelSet testObject;

    @Before
    public void setUp()
        throws Exception
    {
        testObject = new LabelSet();
    }

    @After
    public void tearDown()
        throws Exception
    {
        testObject = null;
    }

    @Test
    public void testGetSetValue()
    {
        String name = "label";
        Instruction value = new NOPInstruction(1);
        Instruction result = null;

        testObject.setInstruction(name, value);

        try
        {
            result = testObject.getInstruction(name);
        }
        catch(LabelException e)
        {
            e.printStackTrace();
            Assert.fail("Unexpected LabelException was thrown.");
        }

        Assert.assertEquals(value, result);
    }

    @Test
    public void testContains()
    {
        String name1 = "label1";
        String name2 = "label2";
        Instruction value = new NOPInstruction(1);

        testObject.setInstruction(name1, value);

        boolean result1 = testObject.contains(name1);
        boolean result2 = testObject.contains(name2);

        Assert.assertTrue(result1);
        Assert.assertFalse(result2);
    }

    @Test
    public void testGetSetValueByNumber()
    {
        String name = "label";
        Instruction value1 = new NOPInstruction(1);
        Instruction value2 = new NOPInstruction(2);
        Instruction result1 = null;
        Instruction result2 = null;

        testObject.setInstruction(name, value1);

        int number = testObject.getNumber(name);

        try
        {
            testObject.setInstruction(number, value2);
            result1 = testObject.getInstruction(name);
            result2 = testObject.getInstruction(number);
        }
        catch(LabelException e)
        {
            e.printStackTrace();
            Assert.fail("Unexpected LabelException was thrown.");
        }

        Assert.assertEquals(value2, result1);
        Assert.assertEquals(value2, result2);
    }

    @Test(expected = LabelException.class)
    public void testGetSetValueByNumberWhenVariableNotSet()
        throws LabelException
    {
        Instruction value = new NOPInstruction(1);
        int number = 1;

        testObject.setInstruction(number, value);
    }
}
