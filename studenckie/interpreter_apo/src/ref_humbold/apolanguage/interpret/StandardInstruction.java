package ref_humbold.apolanguage.interpret;

/**
Klasa przechowujaca pojedyncza standardowa instrukcje w liscie rozkazow.
*/
class StandardInstruction
	extends Instruction
{
 	/** Tworzy element odpowiadajacy jednej instrukcji w programie. */
	public StandardInstruction(int lineNumber, String name, int[] args)
	{
		super(lineNumber, name, args);
	}
}

