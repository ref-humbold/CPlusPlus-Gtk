package ref_humbold.apolanguage.instructions;

import ref_humbold.apolanguage.errors.ArithmeticError;
import ref_humbold.apolanguage.errors.SymbolError;
import ref_humbold.apolanguage.interpret.VariableSet;

public class ArithmeticInstruction
    extends Instruction
{
    public ArithmeticInstruction(int lineNumber, InstructionName name, int... args)
    {
        super(lineNumber, name, args);
    }

    @Override
    public void execute(VariableSet variables)
        throws ArithmeticError, SymbolError
    {
        int argValue1;
        int argValue2;

        switch(name)
        {
            case ADD:

                try
                {
                    argValue1 = variables.getValue(args[1]);
                    argValue2 = variables.getValue(args[2]);
                    variables.setValue(args[0], argValue1 + argValue2);
                }
                catch(SymbolError e)
                {
                    e.setLineNumber(lineNumber);

                    throw e;
                }

                break;

            case ADDI:
                try
                {
                    argValue1 = variables.getValue(args[1]);
                    variables.setValue(args[0], argValue1 + args[2]);
                }
                catch(SymbolError e)
                {
                    e.setLineNumber(lineNumber);

                    throw e;
                }

                break;

            case SUB:
                try
                {
                    argValue1 = variables.getValue(args[1]);
                    argValue2 = variables.getValue(args[2]);
                    variables.setValue(args[0], argValue1 - argValue2);
                }
                catch(SymbolError e)
                {
                    e.setLineNumber(lineNumber);

                    throw e;
                }

                break;

            case SUBI:
                try
                {
                    argValue1 = variables.getValue(args[1]);
                    variables.setValue(args[0], argValue1 - args[2]);
                }
                catch(SymbolError e)
                {
                    e.setLineNumber(lineNumber);

                    throw e;
                }

                break;

            case MUL:
                try
                {
                    argValue1 = variables.getValue(args[1]);
                    argValue2 = variables.getValue(args[2]);
                    variables.setValue(args[0], argValue1 * argValue2);
                }
                catch(SymbolError e)
                {
                    e.setLineNumber(lineNumber);

                    throw e;
                }

                break;

            case MULI:
                try
                {
                    argValue1 = variables.getValue(args[1]);
                    variables.setValue(args[0], argValue1 * args[2]);
                }
                catch(SymbolError e)
                {
                    e.setLineNumber(lineNumber);

                    throw e;
                }

                break;

            case DIV:

                try
                {
                    argValue1 = variables.getValue(args[1]);
                    argValue2 = variables.getValue(args[2]);
                }
                catch(SymbolError e)
                {
                    throw new SymbolError(e.getMessage(), lineNumber);
                }

                if(argValue2 == 0)
                {
                    if(argValue1 == 0)
                        throw new ArithmeticError(ArithmeticError.NOT_A_NUMBER, lineNumber);

                    throw new ArithmeticError(ArithmeticError.ZERO_DIVISION, lineNumber);
                }

                try
                {
                    variables.setValue(args[0], argValue1 / argValue2);
                }
                catch(SymbolError e)
                {
                    throw new SymbolError(e.getMessage(), lineNumber);
                }

                break;

            case DIVI:
                try
                {
                    argValue1 = variables.getValue(args[1]);
                }
                catch(SymbolError e)
                {
                    throw new SymbolError(e.getMessage(), lineNumber);
                }

                if(args[2] == 0)
                {
                    if(argValue1 == 0)
                        throw new ArithmeticError(ArithmeticError.NOT_A_NUMBER, lineNumber);

                    throw new ArithmeticError(ArithmeticError.ZERO_DIVISION, lineNumber);
                }

                try
                {
                    variables.setValue(args[0], argValue1 / args[2]);
                }
                catch(SymbolError e)
                {
                    throw new SymbolError(e.getMessage(), lineNumber);
                }

                break;
        }
    }
}
