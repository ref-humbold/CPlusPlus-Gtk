package ref_humbold.apolanguage.interpret;

import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

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
	public void testAddInstrIfIsLabel()
	{
		int cnt = 1;
		String name = "ADD";
		int[] args = new int[]{10, 20, 30};
		Element e = testObject.addInstr(cnt, name, args, true);
		Element expected = new Element(cnt, name, args);

		Assert.assertNotNull(e);
		Assert.assertEquals(expected, e);
	}

	@Test
	public void testAddInstrIfIsNoLabel()
	{
		int cnt = 1;
		String name = "ADD";
		int[] args = new int[]{10, 20, 30};
		Element e = testObject.addInstr(cnt, name, args, false);
		
		Assert.assertNull(e);
	}

	@Test
	public void testAddInstrIfJumpAndIsLabel()
	{
		int cnt = 1;
		String name = "JUMP";
		int[] args = new int[]{};
		Element e = testObject.addInstr(cnt, name, args, true);
		Element expected = new ElemJump(cnt, name, args);
		
		Assert.assertNotNull(e);
		Assert.assertEquals(expected, e);
	}

	@Test
	public void testAddInstrIfJumpAndIsNoLabel()
	{
		int cnt = 1;
		String name = "JUMP";
		int[] args = new int[]{};
		Element e = testObject.addInstr(cnt, name, args, false);
		
		Assert.assertNull(e);
	}

	@Test
	public void testStartItWithEmptyList()
	{
		testObject.startIt();
		Assert.assertNull(testObject.it);
	}

	@Test
	public void testStartItWithNonEmptyList()
	{
		int cnt = 1;
		String name = "ADD";
		int[] args = new int[]{10, 20, 30};
		Element expected = new Element(cnt, name, args);
		
		testObject.addInstr(cnt, name, args, false);
		testObject.startIt();
		
		Assert.assertEquals(expected, testObject.it);
	}

	@Test
	public void testNextItIfIsJump()
	{
		int cnt1 = 1;
		String name1 = "JPEQ";
		int[] args1 = new int[]{10, 20, 5};
		int cnt2 = 2;
		String name2 = "ADD";
		int[] args2 = new int[]{10, 20, 5};
		int cnt3 = 2;
		String name3 = "MULT";
		int[] args3 = new int[]{10, 20, 5};

		testObject.addInstr(cnt1, name1, args1, false);
		testObject.addInstr(cnt2, name2, args2, false);
		
		Element e = testObject.addInstr(cnt3, name3, args3, true);
		Element expected = new Element(cnt3, name3, args3);
		
		testObject.startIt();
		testObject.setLink(e);
		testObject.nextIt(true);

		Assert.assertEquals(expected, testObject.it);
	}

	@Test
	public void testNextItIfIsNoJump()
	{
		int cnt1 = 1;
		String name1 = "JPEQ";
		int[] args1 = new int[]{10, 20, 5};
		int cnt2 = 2;
		String name2 = "ADD";
		int[] args2 = new int[]{10, 20, 5};
		int cnt3 = 2;
		String name3 = "MULT";
		int[] args3 = new int[]{10, 20, 5};

		testObject.addInstr(cnt1, name1, args1, false);
		testObject.addInstr(cnt2, name2, args2, false);
		
		Element e = testObject.addInstr(cnt3, name3, args3, true);
		Element expected = new Element(cnt2, name2, args2);
		
		testObject.startIt();
		testObject.setLink(e);
		testObject.nextIt(false);

		Assert.assertEquals(expected, testObject.it);
	}
}
