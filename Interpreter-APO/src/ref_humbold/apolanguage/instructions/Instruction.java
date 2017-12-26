package ref_humbold.apolanguage.instructions;

import java.util.Arrays;

import ref_humbold.apolanguage.errors.LanguageException;
import ref_humbold.apolanguage.interpret.VariableSet;

/**
 * Bazowa klasa do przechowywania pojedynczej instrukcji w liscie rozkazow.
 */
public abstract class Instruction
{
    /**
     * Numer wiersza programu.
     */
    protected int lineNumber;

    /**
     * Nazwa operacji.
     */
    protected InstructionName name;

    /**
     * Argumenty operacji.
     */
    protected int[] args;

    /**
     * Wskaznik na nastepny element listy.
     */
    protected Instruction next = null;

    public Instruction(int lineNumber, InstructionName name, int... args)
    {
        if(name == null)
            throw new IllegalArgumentException("Instruction name is null.");

        this.lineNumber = lineNumber;
        this.name = name;
        this.args = args;
    }

    public int getLineNumber()
    {
        return this.lineNumber;
    }

    public InstructionName getName()
    {
        return this.name;
    }

    public int getArgsNumber()
    {
        return this.args.length;
    }

    public Instruction getNext()
    {
        return this.next;
    }

    public void setNext(Instruction next)
    {
        this.next = next;
    }

    public int getArg(int index)
    {
        return this.args[index];
    }

    @Override
    public boolean equals(Object obj)
    {
        if(this == obj)
            return true;

        if(obj == null)
            return false;

        if(!(obj instanceof Instruction))
            return false;

        Instruction other = (Instruction)obj;

        return lineNumber == other.lineNumber && name.equals(other.name) && Arrays.equals(args,
                                                                                          other.args);
    }

    @Override
    public int hashCode()
    {
        int prime = 37;
        int result = 1;

        result = prime * result + Arrays.hashCode(args);
        result = prime * result + (name == null ? 0 : name.hashCode());

        return result;
    }

    public abstract void execute(VariableSet variables)
        throws LanguageException;
}
