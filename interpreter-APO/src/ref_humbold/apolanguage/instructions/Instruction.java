package ref_humbold.apolanguage.instructions;

import java.util.Arrays;

import ref_humbold.apolanguage.errors.LanguageError;
import ref_humbold.apolanguage.interpret.VariableSet;

/**
 * Bazowa klasa do przechowywania pojedynczej instrukcji w liście rozkazów.
 */
public abstract class Instruction
    implements Cloneable
{
    /**
     * Numer wiersza programu.
     */
    protected int lineNumber;

    /**
     * Nazwa operacji.
     */
    protected String name;

    /**
     * Argumenty operacji.
     */
    protected int[] args;

    /**
     * Wskaźnik na następny element listy.
     */
    protected Instruction next = null;

    public Instruction(int lineNumber, String name, int... args)
    {
        this.lineNumber = lineNumber;
        this.name = name;
        this.args = args;
    }

    public int getLineNumber()
    {
        return this.lineNumber;
    }

    public String getName()
    {
        return this.name;
    }

    public int getArgsNumber()
    {
        return this.args.length;
    }

    public int getArg(int index)
    {
        return this.args[index];
    }

    public Instruction getNext(boolean isJump)
    {
        return this.next;
    }

    public void setNext(Instruction next)
    {
        this.next = next;
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

        if(!Arrays.equals(args, other.args))
            return false;

        if(name == null)
            return other.name == null;

        return name.equals(other.name);
    }

    public boolean equalsLine(Object obj)
    {
        if(!equals(obj))
            return false;

        Instruction other = (Instruction)obj;

        return lineNumber == other.lineNumber;
    }

    @Override
    public abstract Instruction clone();

    @Override
    public int hashCode()
    {
        final int prime = 37;
        int result = 1;

        result = prime * result + Arrays.hashCode(args);
        result = prime * result + (name == null ? 0 : name.hashCode());

        return result;
    }

    public abstract void execute(VariableSet variables)
        throws LanguageError;
}
