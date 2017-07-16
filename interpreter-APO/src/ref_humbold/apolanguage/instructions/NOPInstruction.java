package ref_humbold.apolanguage.instructions;

import ref_humbold.apolanguage.interpret.VariableSet;

public class NOPInstruction
    extends Instruction
{
    public NOPInstruction(int lineNumber, InstructionName name)
    {
        super(lineNumber, name);
    }

    @Override
    public NOPInstruction clone()
    {
        return new NOPInstruction(super.lineNumber, super.name);
    }

    @Override
    public void execute(VariableSet variables)
    {
    }
}
