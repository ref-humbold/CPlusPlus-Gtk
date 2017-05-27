package ref_humbold.apolanguage.instructions;

import ref_humbold.apolanguage.errors.LanguageError;
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

    public void execute(VariableSet variables)
        throws LanguageError
    {
        switch(name)
        {
            case "LDW":
                break;

            case "LDB":
                break;

            case "STW":
                break;

            case "STB":
                break;
        }
    }
}
