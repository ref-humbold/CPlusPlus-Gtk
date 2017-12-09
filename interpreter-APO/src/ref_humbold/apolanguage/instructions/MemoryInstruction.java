package ref_humbold.apolanguage.instructions;

import ref_humbold.apolanguage.errors.MemoryException;
import ref_humbold.apolanguage.errors.SymbolException;
import ref_humbold.apolanguage.interpret.Memory;
import ref_humbold.apolanguage.interpret.VariableSet;

public class MemoryInstruction
    extends Instruction
{
    private Memory memory;

    public MemoryInstruction(Memory memory, int lineNumber, InstructionName name, int... args)
    {
        super(lineNumber, name, args);
        this.memory = memory;
    }

    @Override
    public void execute(VariableSet variables)
        throws MemoryException, SymbolException
    {
        int argValue0;
        int argValue1;
        int result;

        switch(name)
        {
            case LDW:
                try
                {
                    argValue1 = variables.getValue(args[1]);
                    result = memory.loadWord(argValue1);
                    variables.setValue(args[0], result);
                }
                catch(SymbolException | MemoryException e)
                {
                    e.setLineNumber(lineNumber);

                    throw e;
                }

                break;

            case LDB:
                try
                {
                    argValue1 = variables.getValue(args[1]);
                    result = memory.loadByte(argValue1);
                    variables.setValue(args[0], result);
                }
                catch(SymbolException | MemoryException e)
                {
                    e.setLineNumber(lineNumber);

                    throw e;
                }

                break;

            case STW:
                try
                {
                    argValue0 = variables.getValue(args[0]);
                    argValue1 = variables.getValue(args[1]);
                    memory.storeWord(argValue1, argValue0);
                }
                catch(SymbolException | MemoryException e)
                {
                    e.setLineNumber(lineNumber);

                    throw e;
                }

                break;

            case STB:
                try
                {
                    argValue0 = variables.getValue(args[0]);
                    argValue1 = variables.getValue(args[1]);
                    memory.storeByte(argValue1, argValue0);
                }
                catch(SymbolException | MemoryException e)
                {
                    e.setLineNumber(lineNumber);

                    throw e;
                }

                break;
        }
    }
}
