package refhumbold.apolang.instructions;

import refhumbold.apolang.interpret.VariableSet;

public class NOPInstruction
    extends Instruction
{
    public NOPInstruction(int lineNumber)
    {
        super(lineNumber, InstructionName.NOP);
    }

    @Override
    public void execute(VariableSet variables)
    {
    }
}
