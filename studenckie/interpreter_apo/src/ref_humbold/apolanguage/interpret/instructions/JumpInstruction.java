package ref_humbold.apolanguage.interpret.instructions;

/**
Klasa przechowujaca pojedyncza instrukcje skoku w liscie rozkazow.
*/
public class JumpInstruction
	extends Instruction
{
	/** Instrukcja, do ktorego wykonamy skok */
	private Instruction linkedInstruction;
	
	/** czy wykona się skok */
	private boolean isJump;
	
	/** @see Instruction#Instruction() */
	public JumpInstruction(int lineNumber, String name, int[] args)
	{
		super(lineNumber, name, args);
		this.linkedInstruction = null;
		isJump = false;
	}
	
	void setLinkedInstruction(Instruction linked)
	{
		linkedInstruction = linked;
	}
	
	Instruction getNextInstruction()
	{
		return isJump ? linkedInstruction : nextInstruction;
	}
}

