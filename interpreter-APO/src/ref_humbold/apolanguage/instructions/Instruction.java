package ref_humbold.apolanguage.instructions;

import java.util.Arrays;

import ref_humbold.apolanguage.errors.LanguageError;
import ref_humbold.apolanguage.errors.SymbolError;
import ref_humbold.apolanguage.interpret.VariableSet;

/**
 * Bazowa klasa do przechowywania pojedynczej instrukcji w liscie rozkazow.
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
        this.lineNumber = lineNumber;
        this.name = name;
        this.args = args;
    }

    /**
     * Zamienia nazwe instrukcji podana jako {@link String} na {@link InstructionName}.
     * @param name nazwa instrukcji
     * @return symbol instrukcji
     */
    public static InstructionName convertToName(String name)
        throws SymbolError
    {
        switch(name)
        {
            case "ADD":
                return InstructionName.ADD;

            case "ADDI":
                return InstructionName.ADDI;

            case "SUB":
                return InstructionName.SUB;

            case "SUBI":
                return InstructionName.SUBI;

            case "MUL":
                return InstructionName.MUL;

            case "MULI":
                return InstructionName.MULI;

            case "DIV":
                return InstructionName.DIV;

            case "DIVI":
                return InstructionName.DIVI;

            case "SHLT":
                return InstructionName.SHLT;

            case "SHRT":
                return InstructionName.SHRT;

            case "SHRS":
                return InstructionName.SHRS;

            case "AND":
                return InstructionName.AND;

            case "ANDI":
                return InstructionName.ANDI;

            case "OR":
                return InstructionName.OR;

            case "ORI":
                return InstructionName.ORI;

            case "XOR":
                return InstructionName.XOR;

            case "XORI":
                return InstructionName.XORI;

            case "NAND":
                return InstructionName.NAND;

            case "NOR":
                return InstructionName.NOR;

            case "JUMP":
                return InstructionName.JUMP;

            case "JPEQ":
                return InstructionName.JPEQ;

            case "JPNE":
                return InstructionName.JPNE;

            case "JPLT":
                return InstructionName.JPLT;

            case "JPGT":
                return InstructionName.JPGT;

            case "LDW":
                return InstructionName.LDW;

            case "LDB":
                return InstructionName.LDB;

            case "STW":
                return InstructionName.STW;

            case "STB":
                return InstructionName.STB;

            case "PTLN":
                return InstructionName.PTLN;

            case "PTINT":
                return InstructionName.PTINT;

            case "PTCHR":
                return InstructionName.PTCHR;

            case "RDINT":
                return InstructionName.RDINT;

            case "RDCHR":
                return InstructionName.RDCHR;

            case "NOP":
                return InstructionName.NOP;
        }

        throw new SymbolError(SymbolError.NO_SUCH_INSTRUCTION);
    }

    /**
     * Okresla, czy instrukcja zapisuje wynik swojej operacji do zmiennej.
     * @param name nazwa instrukcji
     * @return czy zapisuje do zmiennej
     */
    public static boolean setsValue(InstructionName name)
        throws SymbolError
    {
        switch(name)
        {
            case ADD:
            case ADDI:
            case SUB:
            case SUBI:
            case MUL:
            case MULI:
            case DIV:
            case DIVI:
            case SHLT:
            case SHRT:
            case SHRS:
            case AND:
            case ANDI:
            case OR:
            case ORI:
            case XOR:
            case XORI:
            case NAND:
            case NOR:
            case RDINT:
            case RDCHR:
            case LDW:
            case LDB:
                return true;

            case JUMP:
            case JPEQ:
            case JPLT:
            case JPGT:
            case STW:
            case STB:
            case PTLN:
            case PTINT:
            case PTCHR:
            case NOP:
                return false;
        }

        throw new SymbolError(SymbolError.NO_SUCH_INSTRUCTION);
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

    public int getArg(int index)
    {
        return this.args[index];
    }

    public Instruction getNext()
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
