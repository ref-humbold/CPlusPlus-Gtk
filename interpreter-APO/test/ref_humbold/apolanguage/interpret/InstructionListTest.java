package ref_humbold.apolanguage.interpret;

import java.util.Iterator;

import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import ref_humbold.apolanguage.errors.SymbolError;
import ref_humbold.apolanguage.instructions.Instruction;
import ref_humbold.apolanguage.instructions.InstructionFactory;
import ref_humbold.apolanguage.instructions.JumpInstruction;

public class InstructionListTest
{
    private InstructionList testObject;

    @Before
    public void setUp()
        throws Exception
    {
        testObject = new InstructionList();
    }

    @After
    public void tearDown()
        throws Exception
    {
        testObject = null;
    }

    @Test
    public void testAddInstructionIfIsLabel()
    {
        int count = 1;
        String name = "ADD";
        int[] args = new int[]{10, 20, 30};

        Instruction instruction = null;

        try
        {
            instruction = InstructionFactory.create(count, name, args);
        }
        catch(SymbolError e)
        {
            e.printStackTrace();
            Assert.fail("Unexpected SymbolError was thrown.");
        }

        Instruction e = testObject.addInstruction(instruction, true);

        Assert.assertNotNull(e);
        Assert.assertEquals(instruction, e);
    }

    @Test
    public void testAddInstructionIfIsNoLabel()
    {
        int count = 1;
        String name = "ADD";
        int[] args = new int[]{10, 20, 30};

        Instruction instruction = null;

        try
        {
            instruction = InstructionFactory.create(count, name, args);
        }
        catch(SymbolError e)
        {
            e.printStackTrace();
            Assert.fail("Unexpected SymbolError was thrown.");
        }

        Instruction e = testObject.addInstruction(instruction, false);

        Assert.assertNull(e);
    }

    @Test
    public void testAddInstrIfJumpAndIsLabel()
    {
        int count = 1;
        String name = "JUMP";
        int[] args = new int[]{};
        Instruction instruction = null;

        try
        {
            instruction = InstructionFactory.create(count, name, args);
        }
        catch(SymbolError e)
        {
            e.printStackTrace();
            Assert.fail("Unexpected SymbolError was thrown.");
        }

        Instruction e = testObject.addInstruction(instruction, true);

        Assert.assertNotNull(e);
        Assert.assertEquals(instruction, e);
    }

    @Test
    public void testAddInstrIfJumpAndIsNoLabel()
    {
        int count = 1;
        String name = "JUMP";
        int[] args = new int[]{};
        Instruction instruction = null;

        try
        {
            instruction = InstructionFactory.create(count, name, args);
        }
        catch(SymbolError e)
        {
            e.printStackTrace();
            Assert.fail("Unexpected SymbolError was thrown.");
        }

        Instruction e = testObject.addInstruction(instruction, false);

        Assert.assertNull(e);
    }

    @Test
    public void testIteratorWithEmptyList()
    {
        Iterator<Instruction> iterator = testObject.iterator();

        Assert.assertFalse(iterator.hasNext());
    }

    @Test
    public void testIteratorWithNonEmptyList()
    {
        int count = 1;
        String name = "ADD";
        int[] args = new int[]{10, 20, 30};
        Instruction instruction = null;

        try
        {
            instruction = InstructionFactory.create(count, name, args);
        }
        catch(SymbolError e)
        {
            e.printStackTrace();
            Assert.fail("Unexpected SymbolError was thrown.");
        }

        testObject.addInstruction(instruction, false);

        Iterator<Instruction> iterator = testObject.iterator();

        Assert.assertTrue(iterator.hasNext());

        Instruction result = iterator.next();

        Assert.assertEquals(instruction, result);
        Assert.assertFalse(iterator.hasNext());
    }

    @Test
    public void testIteratorNextIfIsJump()
    {
        int count1 = 1;
        String name1 = "JPEQ";
        int[] args1 = new int[]{10, 20, 5};
        JumpInstruction instruction1 = new JumpInstruction(count1, name1, args1);
        int count2 = 2;
        String name2 = "ADD";
        int[] args2 = new int[]{10, 20, 5};
        Instruction instruction2 = null;
        int count3 = 2;
        String name3 = "MUL";
        int[] args3 = new int[]{10, 20, 5};
        Instruction instruction3 = null;

        try
        {
            instruction2 = InstructionFactory.create(count2, name2, args2);
            instruction3 = InstructionFactory.create(count3, name3, args3);
        }
        catch(SymbolError e)
        {
            e.printStackTrace();
            Assert.fail("Unexpected SymbolError was thrown.");
        }

        instruction1.setLink(instruction3);
        instruction1.setJump(true);

        testObject.addInstruction(instruction1, false);
        testObject.addInstruction(instruction2, false);
        testObject.addInstruction(instruction3, true);

        Iterator<Instruction> iterator = testObject.iterator();

        Assert.assertTrue(iterator.hasNext());

        Instruction result1 = iterator.next();

        Assert.assertEquals(instruction1, result1);

        Instruction result3 = iterator.next();

        Assert.assertEquals(instruction3, result3);
        Assert.assertFalse(iterator.hasNext());
    }

    @Test
    public void testIteratorNextIfIsNoJump()
    {
        int count1 = 1;
        String name1 = "JPEQ";
        int[] args1 = new int[]{10, 20, 5};
        JumpInstruction instruction1 = new JumpInstruction(count1, name1, args1);
        int count2 = 2;
        String name2 = "ADD";
        int[] args2 = new int[]{10, 20, 5};
        Instruction instruction2 = null;
        int count3 = 2;
        String name3 = "MUL";
        int[] args3 = new int[]{10, 20, 5};
        Instruction instruction3 = null;

        try
        {
            instruction2 = InstructionFactory.create(count2, name2, args2);
            instruction3 = InstructionFactory.create(count3, name3, args3);
        }
        catch(SymbolError e)
        {
            e.printStackTrace();
            Assert.fail("Unexpected SymbolError was thrown.");
        }

        instruction1.setLink(instruction3);
        instruction1.setJump(false);

        testObject.addInstruction(instruction1, false);
        testObject.addInstruction(instruction2, false);
        testObject.addInstruction(instruction3, true);

        Iterator<Instruction> iterator = testObject.iterator();

        Assert.assertTrue(iterator.hasNext());

        Instruction result1 = iterator.next();

        Assert.assertEquals(instruction1, result1);

        Instruction result2 = iterator.next();

        Assert.assertEquals(instruction2, result2);
        Assert.assertTrue(iterator.hasNext());

        Instruction result3 = iterator.next();

        Assert.assertEquals(instruction3, result3);
        Assert.assertFalse(iterator.hasNext());
    }
}
