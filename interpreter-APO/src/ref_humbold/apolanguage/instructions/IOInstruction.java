package ref_humbold.apolanguage.instructions;

import ref_humbold.apolanguage.errors.LanguageError;
import ref_humbold.apolanguage.interpret.IOConnector;
import ref_humbold.apolanguage.interpret.VariableSet;

public class IOInstruction
    extends Instruction
{
    private IOConnector connector;

    public IOInstruction(IOConnector connector, int lineNumber, String name, int[] args)
    {
        super(lineNumber, name, args);
        this.connector = connector;
    }

    public void execute(VariableSet variables)
        throws LanguageError
    {
        switch(name)
        {
            case "PTLN":
                break;

            case "PTINT":
                break;

            case "PTCHR":
                break;

            case "RDINT":
                break;

            case "RDCHR":
                break;
        }
    }
}
