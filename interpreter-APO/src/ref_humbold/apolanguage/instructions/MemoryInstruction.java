package ref_humbold.apolanguage.instructions;

import ref_humbold.apolanguage.errors.MemoryError;
import ref_humbold.apolanguage.interpret.Memory;
import ref_humbold.apolanguage.interpret.VariableSet;

public class MemoryInstruction
    extends Instruction
{
    private Memory memory;

    public MemoryInstruction(Memory memory, int lineNumber, String name, int... args)
    {
        super(lineNumber, name, args);
        this.memory = memory;
    }

    @Override
    public MemoryInstruction clone()
    {
        MemoryInstruction instruction = new MemoryInstruction(memory, lineNumber, name, args);

        instruction.setNext(next);

        return instruction;
    }

    public void execute(VariableSet variables)
        throws MemoryError
    {
        int argValue0;
        int argValue1;

        switch(name)
        {
            case "LDW":
                argValue1 = variables.getValue(args[1]);
                variables.setValue(args[0], memory.loadWord(argValue1, lineNumber));
                break;

            case "LDB":
                argValue1 = variables.getValue(args[1]);
                variables.setValue(args[0], memory.loadByte(argValue1, lineNumber));
                break;

            case "STW":
                argValue0 = variables.getValue(args[0]);
                argValue1 = variables.getValue(args[1]);
                memory.storeWord(argValue1, argValue0, lineNumber);

                break;

            case "STB":
                argValue0 = variables.getValue(args[0]);
                argValue1 = variables.getValue(args[1]);
                memory.storeByte(argValue1, argValue0, lineNumber);
                break;
        }
    }
}
