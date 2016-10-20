package ref_humbold.apolanguage.interpret.instructions;

/**
Klasa przechowujaca pojedyncza standardowa instrukcje w liscie rozkazow.
*/
public class StandardInstruction
    extends Instruction
{
     /** Tworzy element odpowiadajacy jednej instrukcji w programie. */
    public StandardInstruction(int lineNumber, String name, int[] args)
    {
        super(lineNumber, name, args);
    }
}

