package ref_humbold.apolanguage.instructions;

import ref_humbold.apolanguage.errors.LanguageError;
import ref_humbold.apolanguage.interpret.VariableSet;

public class LogicalInstruction
    extends Instruction
{
    public LogicalInstruction(int lineNumber, String name, int... args)
    {
        super(lineNumber, name, args);
        // TODO Auto-generated constructor stub
    }

    public void execute(VariableSet variables)
        throws LanguageError
    {
        switch(name)
        {
            case "SHLT":
                break;

            case "SHRT":
                break;

            case "SHRS":
                break;

            case "AND":
                break;

            case "ANDI":
                break;

            case "OR":
                break;

            case "ORI":
                break;

            case "XOR":
                break;

            case "XORI":
                break;

            case "NAND":
                break;

            case "NOR":
                break;
        }
    }
}
