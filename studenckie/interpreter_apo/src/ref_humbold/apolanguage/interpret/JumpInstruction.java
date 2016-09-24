package ref_humbold.apolanguage.interpret;

/**
Klasa przechowujaca pojedyncza instrukcje skoku w liscie rozkazow.
*/
class JumpInstruction
	extends Instruction
{
	/** Instrukcja, do ktorego wykonamy skok */
	Element linkedInstruction;
	
	/** @see Instruction#Instruction() */
	public JumpInstruction(int lineNumber, String name, int[] args)
	{
		super(lineNumber, name, args);
		this.linkedInstruction = null;
	}
}

