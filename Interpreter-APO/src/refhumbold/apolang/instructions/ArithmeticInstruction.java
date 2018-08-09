package refhumbold.apolang.instructions;

import refhumbold.apolang.errors.ArithmeticException;
import refhumbold.apolang.errors.SymbolException;
import refhumbold.apolang.interpret.VariableSet;

public class ArithmeticInstruction
    extends Instruction
{
    public ArithmeticInstruction(int lineNumber, InstructionName name, int... args)
    {
        super(lineNumber, name, args);
    }

    @Override
    public void execute(VariableSet variables)
        throws ArithmeticException, SymbolException
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
                catch(SymbolException e)
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
                catch(SymbolException e)
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
                catch(SymbolException e)
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
                catch(SymbolException e)
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
                catch(SymbolException e)
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
                catch(SymbolException e)
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
                catch(SymbolException e)
                {
                    throw new SymbolException(e.getMessage(), lineNumber);
                }

                if(argValue2 == 0)
                {
                    if(argValue1 == 0)
                        throw new ArithmeticException(ArithmeticException.NOT_A_NUMBER, lineNumber);

                    throw new ArithmeticException(ArithmeticException.ZERO_DIVISION, lineNumber);
                }

                try
                {
                    variables.setValue(args[0], argValue1 / argValue2);
                }
                catch(SymbolException e)
                {
                    throw new SymbolException(e.getMessage(), lineNumber);
                }

                break;

            case DIVI:
                try
                {
                    argValue1 = variables.getValue(args[1]);
                }
                catch(SymbolException e)
                {
                    throw new SymbolException(e.getMessage(), lineNumber);
                }

                if(args[2] == 0)
                {
                    if(argValue1 == 0)
                        throw new ArithmeticException(ArithmeticException.NOT_A_NUMBER, lineNumber);

                    throw new ArithmeticException(ArithmeticException.ZERO_DIVISION, lineNumber);
                }

                try
                {
                    variables.setValue(args[0], argValue1 / args[2]);
                }
                catch(SymbolException e)
                {
                    throw new SymbolException(e.getMessage(), lineNumber);
                }

                break;

            default:
                break;
        }
    }
}
