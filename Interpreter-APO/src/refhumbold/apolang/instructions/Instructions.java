package refhumbold.apolang.instructions;

import refhumbold.apolang.errors.SymbolException;

public class Instructions
{
    /**
     * Zamienia nazwe instrukcji podana jako {@link String} na {@link InstructionName}.
     * @param name nazwa instrukcji
     * @return symbol instrukcji
     */
    public static InstructionName convertToName(String name)
        throws SymbolException
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

        throw new SymbolException(SymbolException.NO_SUCH_INSTRUCTION);
    }

    /**
     * @param name nazwa instrukcji
     * @return czy instrukcja zapisuje wartosc
     */
    public static boolean isValueSet(InstructionName name)
        throws SymbolException
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
            case JPNE:
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

        throw new SymbolException(SymbolException.NO_SUCH_INSTRUCTION);
    }

    /**
     * @param name nazwa instrukcji
     * @return liczba argumentow instrukcji
     */
    public int getArgsNumber(InstructionName name)
        throws SymbolException
    {
        switch(name)
        {
            case PTLN:
            case NOP:
                return 0;

            case LDW:
            case LDB:
            case PTINT:
            case PTCHR:
            case RDINT:
            case RDCHR:
                return 1;

            case STW:
            case STB:
                return 2;

            case JUMP:
            case JPEQ:
            case JPNE:
            case JPLT:
            case JPGT:
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
                return 3;
        }

        throw new SymbolException(SymbolException.NO_SUCH_INSTRUCTION);
    }
}
