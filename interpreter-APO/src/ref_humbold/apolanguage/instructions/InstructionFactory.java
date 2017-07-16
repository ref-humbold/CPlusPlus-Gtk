package ref_humbold.apolanguage.instructions;

import ref_humbold.apolanguage.errors.SymbolError;
import ref_humbold.apolanguage.interpret.Memory;

public class InstructionFactory
{
    public static Memory memory;

    public static Instruction create(int lineNumber, String name, int... args)
        throws SymbolError
    {
        Instruction instruction;

        switch(name)
        {
            case "ADD":
            case "ADDI":
            case "SUB":
            case "SUBI":
            case "MUL":
            case "MULI":
            case "DIV":
            case "DIVI":
                instruction = new ArithmeticInstruction(lineNumber, toName(name), args);
                break;

            case "SHLT":
            case "SHRT":
            case "SHRS":
            case "AND":
            case "ANDI":
            case "OR":
            case "ORI":
            case "XOR":
            case "XORI":
            case "NAND":
            case "NOR":
                instruction = new LogicalInstruction(lineNumber, toName(name), args);
                break;

            case "JUMP":
            case "JPEQ":
            case "JPNE":
            case "JPLT":
            case "JPGT":
                instruction = new JumpInstruction(lineNumber, toName(name), args);
                break;

            case "LDW":
            case "LDB":
            case "STW":
            case "STB":
                instruction = new MemoryInstruction(memory, lineNumber, toName(name), args);
                break;

            case "PTLN":
            case "PTINT":
            case "PTCHR":
            case "RDINT":
            case "RDCHR":
                instruction = new IOInstruction(lineNumber, toName(name), args);
                break;

            case "NOP":
                instruction = new NOPInstruction(lineNumber, toName(name));
                break;

            default:
                throw new SymbolError(SymbolError.NO_SUCH_INSTRUCTION, lineNumber);
        }

        return instruction;
    }

    private static InstructionName toName(String name)
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
        }

        return InstructionName.NOP;
    }
}
