package ref_humbold.apolanguage.instructions;

import ref_humbold.apolanguage.errors.LanguageError;
import ref_humbold.apolanguage.interpret.VariableSet;

public class ArithmeticInstruction
    extends Instruction
{
    public ArithmeticInstruction(int lineNumber, String name, int... args)
    {
        super(lineNumber, name, args);
    }

    public void execute(VariableSet variables)
        throws LanguageError
    {
        switch(name)
        {
            case "ADD":
                break;

            case "ADDI":
                break;

            case "SUB":
                break;

            case "SUBI":
                break;

            case "MUL":
                break;

            case "MULI":
                break;

            case "DIV":
                break;

            case "DIVI":
                break;
        }
    }
}
