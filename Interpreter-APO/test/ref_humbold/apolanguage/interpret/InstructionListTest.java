package ref_humbold.apolanguage.interpret;

import java.util.Iterator;

import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import ref_humbold.apolanguage.errors.LanguageException;
import ref_humbold.apolanguage.errors.SymbolException;
import ref_humbold.apolanguage.instructions.Instruction;
import ref_humbold.apolanguage.instructions.InstructionFactory;
import ref_humbold.apolanguage.instructions.InstructionName;
import ref_humbold.apolanguage.instructions.JumpInstruction;

public class InstructionListTest
{
    private static final String[] vars = new String[]{"zero", "one", "two", "tree", "res"};
    private InstructionList testObject;
    private VariableSet variableSet;

    @Before

    public void setUp()
        throws Exception
    {
        testObject = new InstructionList();
        variableSet = new VariableSet();

        for(int i = 0; i < vars.length; ++i)
            variableSet.setValue(vars[i], i);
    }

    @After
    public void tearDown()
        throws Exception
    {
        testObject = null;
        variableSet = null;
    }

    @Test
    public void testAddWhenEmpty()
    {
        int count = 1;
        InstructionName name = InstructionName.ADD;
        int[] args = new int[]{4, 1, 2};

        Instruction instruction = null;

        try
        {
            instruction = InstructionFactory.create(count, name, args);
        }
        catch(SymbolException e)
        {
            e.printStackTrace();
            Assert.fail("Unexpected SymbolException was thrown.");
        }

        testObject.add(instruction);

        Iterator<Instruction> it = testObject.iterator();

        Assert.assertTrue(it.hasNext());
        Assert.assertEquals(instruction, it.next());
        Assert.assertFalse(it.hasNext());
    }

    @Test
    public void testAddWhenNotEmpty()
    {
        int count1 = 1;
        InstructionName name1 = InstructionName.ADD;
        int[] args1 = new int[]{4, 1, 2};
        int count2 = 1;
        InstructionName name2 = InstructionName.MUL;
        int[] args2 = new int[]{4, 1, 2};

        Instruction instruction1 = null;
        Instruction instruction2 = null;

        try
        {
            instruction1 = InstructionFactory.create(count1, name1, args1);
            instruction2 = InstructionFactory.create(count2, name2, args2);
        }
        catch(SymbolException e)
        {
            e.printStackTrace();
            Assert.fail("Unexpected SymbolException was thrown.");
        }

        testObject.add(instruction1);
        testObject.add(instruction2);

        Iterator<Instruction> it = testObject.iterator();

        Assert.assertTrue(it.hasNext());
        Assert.assertEquals(instruction1, it.next());
        Assert.assertTrue(it.hasNext());
        Assert.assertEquals(instruction2, it.next());
        Assert.assertFalse(it.hasNext());
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
        int[] args = new int[]{4, 1, 2};
        Instruction instruction = null;

        try
        {
            instruction = InstructionFactory.create(count, name, args);
        }
        catch(SymbolException e)
        {
            e.printStackTrace();
            Assert.fail("Unexpected SymbolException was thrown.");
        }

        testObject.add(instruction);

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
        InstructionName name1 = InstructionName.JPNE;
        int[] args1 = new int[]{1, 2};
        JumpInstruction instruction1 = new JumpInstruction(count1, name1, args1);
        int count2 = 2;
        InstructionName name2 = InstructionName.ADD;
        int[] args2 = new int[]{4, 1, 3};
        Instruction instruction2 = null;
        int count3 = 2;
        InstructionName name3 = InstructionName.MUL;
        int[] args3 = new int[]{4, 1, 3};
        Instruction instruction3 = null;

        try
        {
            instruction2 = InstructionFactory.create(count2, name2, args2);
            instruction3 = InstructionFactory.create(count3, name3, args3);
        }
        catch(SymbolException e)
        {
            e.printStackTrace();
            Assert.fail("Unexpected SymbolException was thrown.");
        }

        instruction1.setLink(instruction3);

        testObject.add(instruction1);
        testObject.add(instruction2);
        testObject.add(instruction3);

        Iterator<Instruction> iterator = testObject.iterator();

        Assert.assertTrue(iterator.hasNext());

        Instruction result1 = iterator.next();

        Assert.assertEquals(instruction1, result1);
        Assert.assertTrue(iterator.hasNext());

        try
        {
            result1.execute(variableSet);
        }
        catch(LanguageException e)
        {
            e.printStackTrace();
            Assert.fail("Unexpected LanguageException was thrown.");
        }

        Instruction result3 = iterator.next();

        Assert.assertEquals(instruction3, result3);
        Assert.assertFalse(iterator.hasNext());
    }

    @Test
    public void testIteratorNextWhenNoJump()
    {
        int count1 = 1;
        InstructionName name1 = InstructionName.JPEQ;
        int[] args1 = new int[]{1, 2};
        JumpInstruction instruction1 = new JumpInstruction(count1, name1, args1);
        int count2 = 2;
        InstructionName name2 = InstructionName.ADD;
        int[] args2 = new int[]{4, 1, 3};
        Instruction instruction2 = null;
        int count3 = 2;
        InstructionName name3 = InstructionName.MUL;
        int[] args3 = new int[]{4, 1, 3};
        Instruction instruction3 = null;

        try
        {
            instruction2 = InstructionFactory.create(count2, name2, args2);
            instruction3 = InstructionFactory.create(count3, name3, args3);
        }
        catch(SymbolException e)
        {
            e.printStackTrace();
            Assert.fail("Unexpected SymbolException was thrown.");
        }

        instruction1.setLink(instruction3);

        testObject.add(instruction1);
        testObject.add(instruction2);
        testObject.add(instruction3);

        Iterator<Instruction> iterator = testObject.iterator();

        Assert.assertTrue(iterator.hasNext());

        Instruction result1 = iterator.next();

        Assert.assertEquals(instruction1, result1);
        Assert.assertTrue(iterator.hasNext());

        try
        {
            result1.execute(variableSet);
        }
        catch(LanguageException e)
        {
            e.printStackTrace();
            Assert.fail("Unexpected LanguageException was thrown.");
        }

        Instruction result2 = iterator.next();

        Assert.assertEquals(instruction2, result2);
        Assert.assertTrue(iterator.hasNext());

        Instruction result3 = iterator.next();

        Assert.assertEquals(instruction3, result3);
        Assert.assertFalse(iterator.hasNext());
    }
}
