package ref_humbold.apolanguage.interpret;

import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import ref_humbold.apolanguage.errors.MemoryException;

public class MemoryTest
{
    private Memory testObject;

    @Before
    public void setUp()
        throws Exception
    {
        testObject = new Memory(1);
    }

    @After
    public void tearDown()
        throws Exception
    {
        testObject = null;
    }

    @Test(expected = MemoryException.class)
    public void testStoreWordWhenInvalidAddress()
        throws MemoryException
    {
        int value = 0x01ABCDEF;
        int address = 7;

        testObject.storeWord(address, value);
    }

    @Test
    public void testStoreWordThenLoadWord()
    {
        int value = 0x01ABCDEF;
        int address = 0;
        int result;

        try
        {
            testObject.storeWord(address, value);
            result = testObject.loadWord(address);

            Assert.assertEquals(value, result);
        }
        catch(MemoryException e)
        {
            e.printStackTrace();
            Assert.fail("Unexpected MemoryException was thrown.");
        }
    }

    @Test
    public void testStoreByteThenLoadByte()
    {
        int value = 0x78;
        int address = 10;
        int result;

        try
        {
            testObject.storeByte(address, value);
            result = testObject.loadByte(address);

            Assert.assertEquals(value, result);
        }
        catch(MemoryException e)
        {
            e.printStackTrace();
            Assert.fail("Unexpected MemoryException was thrown.");
        }
    }

    @Test
    public void testStoreByteThenLoadWordWhenCorrectAddress()
    {
        int[] values = new int[]{0x78, 0xED, 0x40, 0x9C};
        int address = 16;
        int expected = (values[0] << 24) | (values[1] << 16) | (values[2] << 8) | values[3];
        int result = 0;

        try
        {
            testObject.storeByte(address, values[0]);
            testObject.storeByte(address + 1, values[1]);
            testObject.storeByte(address + 2, values[2]);
            testObject.storeByte(address + 3, values[3]);
            result = testObject.loadWord(address);
        }
        catch(MemoryException e)
        {
            e.printStackTrace();
            Assert.fail("Unexpected MemoryException was thrown.");
        }

        Assert.assertEquals(expected, result);
    }

    @Test(expected = MemoryException.class)
    public void testStoreByteThenLoadWordWhenInvalidAddress()
        throws MemoryException
    {
        int[] values = new int[]{0x78, 0xED, 0x40, 0x9C};
        int address = 23;

        try
        {
            testObject.storeByte(address, values[0]);
            testObject.storeByte(address + 1, values[1]);
            testObject.storeByte(address + 2, values[2]);
            testObject.storeByte(address + 3, values[3]);
        }
        catch(MemoryException e)
        {
            e.printStackTrace();
            Assert.fail("Unexpected MemoryException was thrown.");
        }

        testObject.loadWord(address);
    }

    @Test
    public void testStoreWordThenLoadByte()
    {
        int[] values = new int[]{0x23, 0x45, 0xBD, 0xDE};
        int address = 32;
        int value = (values[0] << 24) | (values[1] << 16) | (values[2] << 8) | values[3];
        int[] results = new int[4];

        try
        {
            testObject.storeWord(address, value);
            results[0] = testObject.loadByte(address);
            results[1] = testObject.loadByte(address + 1);
            results[2] = testObject.loadByte(address + 2);
            results[3] = testObject.loadByte(address + 3);

            Assert.assertEquals(values[0], results[0]);
            Assert.assertEquals(values[1], results[1]);
            Assert.assertEquals(values[2], results[2]);
            Assert.assertEquals(values[3], results[3]);
        }
        catch(MemoryException e)
        {
            Assert.fail("Unexpected MemoryException was thrown: " + e.getMessage());
        }
    }
}
