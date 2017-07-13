package ref_humbold.apolanguage.instructions;

import ref_humbold.apolanguage.errors.LanguageError;
import ref_humbold.apolanguage.interpret.IOConnector;
import ref_humbold.apolanguage.interpret.VariableSet;

public class IOInstruction
    extends Instruction
{
    IOConnector connector;

    public IOInstruction(int lineNumber, String name, int[] args)
    {
        super(lineNumber, name, args);
        this.connector = IOConnector.getInstance();
    }

    @Override
    public IOInstruction clone()
    {
        IOInstruction instruction = new IOInstruction(lineNumber, name, args);

        instruction.setNext(next);

        return instruction;
    }

    public void execute(VariableSet variables)
        throws LanguageError
    {
        int argValue;

        switch(name)
        {
            case "PTLN":
                connector.printLine();
                break;

            case "PTINT":
                argValue = variables.getValue(args[0]);
                connector.printInt(argValue);
                break;

            case "PTCHR":
                argValue = variables.getValue(args[0]);
                connector.printChar(argValue);
                break;

            case "RDINT":
                argValue = connector.readInt();
                variables.setValue(args[0], argValue);
                break;

            case "RDCHR":
                argValue = connector.readChar();
                variables.setValue(args[0], argValue);
                break;
        }
    }
}
