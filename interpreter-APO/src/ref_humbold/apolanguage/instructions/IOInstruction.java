package ref_humbold.apolanguage.instructions;

import ref_humbold.apolanguage.errors.LanguageError;
import ref_humbold.apolanguage.errors.SymbolError;
import ref_humbold.apolanguage.interpret.IOConnector;
import ref_humbold.apolanguage.interpret.VariableSet;

public class IOInstruction
    extends Instruction
{
    private IOConnector connector;

    public IOInstruction(int lineNumber, InstructionName name, int... args)
    {
        super(lineNumber, name, args);
        this.connector = IOConnector.getInstance();
    }

    @Override
    public void execute(VariableSet variables)
        throws LanguageError
    {
        int argValue;

        switch(name)
        {
            case PTLN:
                connector.printLine();
                break;

            case PTINT:
                try
                {
                    argValue = variables.getValue(args[0]);
                }
                catch(SymbolError e)
                {
                    e.setLineNumber(lineNumber);

                    throw e;
                }

                connector.printInt(argValue);
                break;

            case PTCHR:
                try
                {
                    argValue = variables.getValue(args[0]);
                }
                catch(SymbolError e)
                {
                    e.setLineNumber(lineNumber);

                    throw e;
                }

                connector.printChar(argValue);
                break;

            case RDINT:
                argValue = connector.readInt();

                try
                {
                    variables.setValue(args[0], argValue);
                }
                catch(SymbolError e)
                {
                    e.setLineNumber(lineNumber);

                    throw e;
                }

                break;

            case RDCHR:
                argValue = connector.readChar();

                try
                {
                    variables.setValue(args[0], argValue);
                }
                catch(SymbolError e)
                {
                    e.setLineNumber(lineNumber);

                    throw e;
                }

                break;
        }
    }
}
