package ref_humbold.apolanguage.interpret;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.StringReader;
import java.util.Arrays;

import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import ref_humbold.apolanguage.errors.LabelError;
import ref_humbold.apolanguage.errors.LanguageError;
import ref_humbold.apolanguage.errors.SymbolError;
import ref_humbold.apolanguage.instructions.ArithmeticInstruction;
import ref_humbold.apolanguage.instructions.IOInstruction;
import ref_humbold.apolanguage.instructions.Instruction;
import ref_humbold.apolanguage.instructions.InstructionName;
import ref_humbold.apolanguage.instructions.JumpInstruction;

public class ParserTest
{
    private String program;
    private Parser testObject;

    @Before
    public void setUp()
        throws Exception
    {
        testObject = new Parser(null);
        program = "#test\nADDI var zero 16\nJPGT var zero label # var > 0\nMULI res var var\nlabel: PTINT res\n";
    }

    @After
    public void tearDown()
        throws Exception
    {
        testObject = null;
    }

    @Test
    public void parse()
    {
        BufferedReader reader = new BufferedReader(new StringReader(program));
        InstructionList result = null;

        try
        {
            result = testObject.parse(reader);
        }
        catch(IOException | LanguageError e)
        {
            e.printStackTrace();
            Assert.fail("Unexpected " + e.getClass() + " was thrown.");
        }

        Instruction ins1 = new ArithmeticInstruction(1, InstructionName.ADDI, 1, 0, 16);
        JumpInstruction ins2 = new JumpInstruction(2, InstructionName.JPGT, 1, 0, 0);
        Instruction ins3 = new ArithmeticInstruction(3, InstructionName.MUL, 2, 1, 1);
        Instruction ins4 = new IOInstruction(4, InstructionName.PTINT, 2);

        ins2.setLink(ins4);

        InstructionList expected = new InstructionList(Arrays.asList(ins1, ins2, ins3, ins4));

        Assert.assertNotNull(result);
        Assert.assertEquals(expected, result);
    }

    @Test(expected = LabelError.class)
    public void parseWhenNotExistingLabel()
        throws LanguageError
    {
        program += "JPEQ var zero none\n";
        BufferedReader reader = new BufferedReader(new StringReader(program));

        try
        {
            testObject.parse(reader);
        }
        catch(IOException e)
        {
            e.printStackTrace();
            Assert.fail("Unexpected IOException was thrown.");
        }
    }

    @Test(expected = SymbolError.class)
    public void parseWhenNotExistingInstruction()
        throws LanguageError
    {
        program += "NONE vb zero zero\n";
        BufferedReader reader = new BufferedReader(new StringReader(program));

        try
        {
            testObject.parse(reader);
        }
        catch(IOException e)
        {
            e.printStackTrace();
            Assert.fail("Unexpected IOException was thrown.");
        }
    }

    @Test
    public void initVariables()
    {
        BufferedReader reader = new BufferedReader(new StringReader(program));
        VariableSet result = null;
        int[] values = new int[]{-1, -1, -1};

        try
        {
            result = testObject.initVariables(reader);
            values[0] = result.getValue("zero");
            values[1] = result.getValue("var");
            values[2] = result.getValue("res");
        }
        catch(IOException | LanguageError e)
        {
            e.printStackTrace();
            Assert.fail("Unexpected " + e.getClass() + " was thrown.");
        }

        Assert.assertNotNull(result);
        Assert.assertArrayEquals(new int[]{0, 0, 0}, values);
    }

    @Test(expected = LabelError.class)
    public void initVariablesWhenLabelHasTheSameName()
        throws LanguageError
    {
        program += "var: DIVI res res 2\n";
        BufferedReader reader = new BufferedReader(new StringReader(program));

        try
        {
            testObject.initVariables(reader);
        }
        catch(IOException e)
        {
            e.printStackTrace();
            Assert.fail("Unexpected IOException was thrown.");
        }
    }
}
