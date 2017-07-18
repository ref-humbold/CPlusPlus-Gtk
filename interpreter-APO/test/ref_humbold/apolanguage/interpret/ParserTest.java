package ref_humbold.apolanguage.interpret;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.StringReader;

import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import ref_humbold.apolanguage.errors.LanguageError;

public class ParserTest
{
    private static final String PROGRAM = "";
    private Parser testObject;
    private BufferedReader reader;

    @Before
    public void setUp()
        throws Exception
    {
        testObject = new Parser(null);
        reader = new BufferedReader(new StringReader(PROGRAM));
    }

    @After
    public void tearDown()
        throws Exception
    {
        testObject = null;
        reader = null;
    }

    @Test
    public void parse()
    {
        InstructionList result = null;

        try
        {
            result = testObject.parse(reader);
        }
        catch(IOException | LanguageError e)
        {
            e.printStackTrace();
            Assert.fail("Unexpected Exception was thrown.");
        }

        Assert.assertNotNull(result);
    }

    @Test
    public void initVariables()
    {
        VariableSet result = null;
        int zeroValue = -1;

        try
        {
            result = testObject.initVariables(reader);
            zeroValue = result.getValue("zero");
        }
        catch(Exception e)
        {
            e.printStackTrace();
            Assert.fail("Unexpected Exception was thrown.");
        }

        Assert.assertNotNull(result);
        Assert.assertEquals(0, zeroValue);
    }
}
