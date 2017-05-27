package ref_humbold.apolanguage.instructions;

import java.util.Arrays;

/**
 * Klasa przechowujaca pojedyncza instrukcje w liscie rozkazow. Instrukcje skokow sa przechowywane w
 * klasie {@link JumpInstruction}.
 */
public class Instruction
{
    /** Numer wiersza programu. */
    protected int lineNumber;

    /** Nazwa operacji. */
    protected String name;

    /** Argumenty operacji. */
    protected int[] args;

    /** Wskaznik na nastepny element listy. */
    protected Instruction next;

    /** Tworzy element odpowiadajacy jednej instrukcji w programie. */
    public Instruction(int lineNumber, String name, int... args)
    {
        this.lineNumber = lineNumber;
        this.name = name;
        this.args = args;
        this.next = null;
    }

    public int getLineNumber()
    {
        return lineNumber;
    }

    public String getName()
    {
        return name;
    }

    public int getArgsNumber()
    {
        return args.length;
    }

    public int getArg(int index)
    {
        return args[index];
    }

    public Instruction getNext(boolean isJump)
    {
        return next;
    }

    public void setNext(Instruction e)
    {
        next = e;
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

        if(name == null && other.name != null || !name.equals(other.name))
            return false;

        return true;
    }

    @Override
    public int hashCode()
    {
        final int prime = 37;
        int result = 1;

        result = prime * result + Arrays.hashCode(args);
        result = prime * result + (name == null ? 0 : name.hashCode());

        return result;
    }

    // public abstract void execute(VariableSet variables) throws LanguageError;
}
