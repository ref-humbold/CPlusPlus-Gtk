package ref_humbold.apolanguage.interpret;

import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import ref_humbold.apolanguage.errors.MemoryError;

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

     @Test(expected=MemoryError.class)
     public void testStoreWord()
          throws MemoryError
     {
          testObject.storeWord(7, 0x01ABCDEF, 10);
     }

     @Test
     public void testStoreWordThenLoadWord()
     {
          int value = 0x01ABCDEF;
          int address = 0;
          int result;
          
          try
          {
               testObject.storeWord(address, value, 10);
               result = testObject.loadWord(address, 11);
          
               Assert.assertEquals(value, result);
          }
          catch(MemoryError e)
          {
               Assert.fail("MemoryError: "+e.getMessage());
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
               testObject.storeByte(address, value, 10);
               result = testObject.loadByte(address, 11);
          
               Assert.assertEquals(value, result);
          }
          catch(MemoryError e)
          {
               Assert.fail("MemoryError: "+e.getMessage());
          }
     }

     @Test
     public void testStoreByteThenLoadWordCorrect()
     {
          int[] values = new int[]{0x78, 0xED, 0x40, 0x9C};
          int address = 16;
          int expected = (values[0]<<24)|(values[1]<<16)|(values[2]<<8)|values[3];;
          int result;
          
          try
          {
               testObject.storeByte(address, values[0], 10);
               testObject.storeByte(address+1, values[1], 11);
               testObject.storeByte(address+2, values[2], 12);
               testObject.storeByte(address+3, values[3], 13);
               result = testObject.loadWord(address, 14);
          
               Assert.assertEquals(expected, result);
          }
          catch(MemoryError e)
          {
               Assert.fail("MemoryError: "+e.getMessage());
          }
     }


     @Test(expected=MemoryError.class)
     public void testStoreByteThenLoadWordError()
          throws MemoryError
     {
          int[] values = new int[]{0x78, 0xED, 0x40, 0x9C};
          int address = 23;
          
          try
          {
               testObject.storeByte(address, values[0], 10);
               testObject.storeByte(address+1, values[1], 11);
               testObject.storeByte(address+2, values[2], 12);
               testObject.storeByte(address+3, values[3], 13);
          }
          catch(MemoryError e)
          {
               Assert.fail("MemoryError: "+e.getMessage());
          }
          
          testObject.loadWord(address, 14);
     }

     @Test
     public void testStoreWordThenLoadByte()
     {
          int[] values = new int[]{0x23, 0x45, 0xBD, 0xDE};
          int address = 32;
          int value = (values[0]<<24)|(values[1]<<16)|(values[2]<<8)|values[3];
          int[] results = new int[4];
          
          try
          {
               testObject.storeWord(address, value, 10);
               results[0] = testObject.loadByte(address, 11);
               results[1] = testObject.loadByte(address+1, 12);
               results[2] = testObject.loadByte(address+2, 13);
               results[3] = testObject.loadByte(address+3, 14);
          
               Assert.assertEquals(values[0], results[0]);
               Assert.assertEquals(values[1], results[1]);
               Assert.assertEquals(values[2], results[2]);
               Assert.assertEquals(values[3], results[3]);
          }
          catch(MemoryError e)
          {
               Assert.fail("MemoryError: "+e.getMessage());
          }
     }
}
