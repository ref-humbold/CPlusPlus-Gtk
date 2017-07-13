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
                instruction = new ArithmeticInstruction(lineNumber, name, args);
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
                instruction = new LogicalInstruction(lineNumber, name, args);
                break;

            case "JUMP":
            case "JPEQ":
            case "JPNE":
            case "JPLT":
            case "JPGT":
                instruction = new JumpInstruction(lineNumber, name, args);
                break;

            case "LDW":
            case "LDB":
            case "STW":
            case "STB":
                instruction = new MemoryInstruction(memory, lineNumber, name, args);
                break;

            case "PTLN":
            case "PTINT":
            case "PTCHR":
            case "RDINT":
            case "RDCHR":
                instruction = new IOInstruction(lineNumber, name, args);
                break;

            case "NOP":
                instruction = new NOPInstruction(lineNumber, name);
                break;

            default:
                throw new SymbolError(SymbolError.NO_SUCH_INSTRUCTION, lineNumber);
        }

        return instruction;
    }
}
