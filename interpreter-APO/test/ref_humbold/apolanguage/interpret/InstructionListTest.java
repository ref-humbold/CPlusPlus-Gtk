package ref_humbold.apolanguage.interpret;

import java.util.Iterator;

import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import ref_humbold.apolanguage.errors.SymbolError;
import ref_humbold.apolanguage.instructions.Instruction;
import ref_humbold.apolanguage.instructions.InstructionFactory;
import ref_humbold.apolanguage.instructions.InstructionName;
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
    public void testAddWhenLabel()
    {
        int count = 1;
        InstructionName name = InstructionName.ADD;
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

        Instruction e = testObject.add(instruction, true);

        Assert.assertNotNull(e);
        Assert.assertEquals(instruction, e);
    }

    @Test
    public void testAddWhenNoLabel()
    {
        int count = 1;
        InstructionName name = InstructionName.ADD;
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

        Instruction e = testObject.add(instruction, false);

        Assert.assertNull(e);
    }

    @Test
    public void testAddWhenJumpAndLabel()
    {
        int count = 1;
        InstructionName name = InstructionName.JUMP;
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

        Instruction e = testObject.add(instruction, true);

        Assert.assertNotNull(e);
        Assert.assertEquals(instruction, e);
    }

    @Test
    public void testAddWhenJumpAndNoLabel()
    {
        int count = 1;
        InstructionName name = InstructionName.JUMP;
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

        Instruction e = testObject.add(instruction, false);

        Assert.assertNull(e);
    }

    @Test
    public void testIteratorWhenEmptyList()
    {
        Iterator<Instruction> iterator = testObject.iterator();

        Assert.assertFalse(iterator.hasNext());
    }

    @Test
    public void testIteratorWhenNonEmptyList()
    {
        int count = 1;
        InstructionName name = InstructionName.ADD;
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

        testObject.add(instruction, false);

        Iterator<Instruction> iterator = testObject.iterator();

        Assert.assertTrue(iterator.hasNext());

        Instruction result = iterator.next();

        Assert.assertEquals(instruction, result);
        Assert.assertFalse(iterator.hasNext());
    }

    @Test
    public void testIteratorNextWhenJump()
    {
        int count1 = 1;
        InstructionName name1 = InstructionName.JPEQ;
        int[] args1 = new int[]{10, 20, 5};
        JumpInstruction instruction1 = new JumpInstruction(count1, name1, args1);
        int count2 = 2;
        InstructionName name2 = InstructionName.ADD;
        int[] args2 = new int[]{10, 20, 5};
        Instruction instruction2 = null;
        int count3 = 2;
        InstructionName name3 = InstructionName.MUL;
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

        testObject.add(instruction1, false);
        testObject.add(instruction2, false);
        testObject.add(instruction3, true);

        Iterator<Instruction> iterator = testObject.iterator();

        Assert.assertTrue(iterator.hasNext());

        Instruction result1 = iterator.next();

        Assert.assertEquals(instruction1, result1);

        Instruction result3 = iterator.next();

        Assert.assertEquals(instruction3, result3);
        Assert.assertFalse(iterator.hasNext());
    }

    @Test
    public void testIteratorNextWhenNoJump()
    {
        int count1 = 1;
        InstructionName name1 = InstructionName.JPEQ;
        int[] args1 = new int[]{10, 20, 5};
        JumpInstruction instruction1 = new JumpInstruction(count1, name1, args1);
        int count2 = 2;
        InstructionName name2 = InstructionName.ADD;
        int[] args2 = new int[]{10, 20, 5};
        Instruction instruction2 = null;
        int count3 = 2;
        InstructionName name3 = InstructionName.MUL;
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

        testObject.add(instruction1, false);
        testObject.add(instruction2, false);
        testObject.add(instruction3, true);

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
