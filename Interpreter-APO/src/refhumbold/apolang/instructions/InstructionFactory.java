package refhumbold.apolang.instructions;

import refhumbold.apolang.errors.SymbolException;
import refhumbold.apolang.interpret.Memory;

public class InstructionFactory
{
    public static Memory memory;

    public static Instruction create(int lineNumber, InstructionName name, int... args)
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
                return new ArithmeticInstruction(lineNumber, name, args);

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
                return new LogicalInstruction(lineNumber, name, args);

            case JUMP:
            case JPEQ:
            case JPLT:
            case JPGT:
                return new JumpInstruction(lineNumber, name, args);

            case LDW:
            case LDB:
            case STW:
            case STB:
                return new MemoryInstruction(memory, lineNumber, name, args);

            case PTLN:
            case PTINT:
            case PTCHR:
            case RDINT:
            case RDCHR:
                return new IOInstruction(lineNumber, name, args);

            case NOP:
                return new NOPInstruction(lineNumber);
        }

        throw new SymbolException(SymbolException.NO_SUCH_INSTRUCTION, lineNumber);
    }
}
