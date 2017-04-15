package ref_humbold.apolanguage.interpret;

import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

public class VariableListTest
{
	private VariableList testObject;
	
	@Before
	public void setUp()
		throws Exception
	{
		testObject = new VariableList();
	}

	@After
	public void tearDown()
		throws Exception
	{
		testObject = null;
	}

	@Test
	public void testAddVar()
	{
		testObject.addVar();
		
		int result = testObject.getValue(0);
		
		Assert.assertEquals(0, result);
	}

	@Test
	public void testGetSetValue()
	{
		int value = 10;
		
		testObject.addVar();
		testObject.setValue(0, value);
		
		int result = testObject.getValue(0);
		
		Assert.assertEquals(value, result);
	}
}
