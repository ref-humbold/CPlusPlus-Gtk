package ref_humbold.apolanguage.instructions;

import ref_humbold.apolanguage.errors.ArithmeticError;
import ref_humbold.apolanguage.errors.SymbolError;
import ref_humbold.apolanguage.interpret.VariableSet;

public class LogicalInstruction
    extends Instruction
{
    public LogicalInstruction(int lineNumber, String name, int... args)
    {
        super(lineNumber, name, args);
    }

    @Override
    public LogicalInstruction clone()
    {
        LogicalInstruction instruction = new LogicalInstruction(lineNumber, name, args);

        instruction.setNext(next);

        return instruction;
    }

    @Override
    public void execute(VariableSet variables)
        throws ArithmeticError, SymbolError
    {
        int argValue1;
        int argValue2;

        switch(name)
        {
            case "SHLT":
                try
                {
                    argValue1 = variables.getValue(args[1]);
                }
                catch(SymbolError e)
                {
                    e.setLineNumber(lineNumber);

                    throw e;
                }

                if(args[2] < 0)
                    throw new ArithmeticError(ArithmeticError.NEGATIVE_SHIFT, lineNumber);

                try
                {
                    variables.setValue(args[0], argValue1 << args[2]);
                }
                catch(SymbolError e)
                {
                    e.setLineNumber(lineNumber);

                    throw e;
                }

                break;

            case "SHRT":
                try
                {
                    argValue1 = variables.getValue(args[1]);
                }
                catch(SymbolError e)
                {
                    e.setLineNumber(lineNumber);

                    throw e;
                }

                if(args[2] < 0)
                    throw new ArithmeticError(ArithmeticError.NEGATIVE_SHIFT, lineNumber);

                try
                {
                    variables.setValue(args[0], argValue1 >>> args[2]);
                }
                catch(SymbolError e)
                {
                    e.setLineNumber(lineNumber);

                    throw e;
                }

                break;

            case "SHRS":
                try
                {
                    argValue1 = variables.getValue(args[1]);
                }
                catch(SymbolError e)
                {
                    e.setLineNumber(lineNumber);

                    throw e;
                }

                if(args[2] < 0)
                    throw new ArithmeticError(ArithmeticError.NEGATIVE_SHIFT, lineNumber);

                try
                {
                    variables.setValue(args[0], argValue1 >> args[2]);
                }
                catch(SymbolError e)
                {
                    e.setLineNumber(lineNumber);

                    throw e;
                }

                break;

            case "AND":
                try
                {
                    argValue1 = variables.getValue(args[1]);
                    argValue2 = variables.getValue(args[2]);
                    variables.setValue(args[0], argValue1 & argValue2);
                }
                catch(SymbolError e)
                {
                    e.setLineNumber(lineNumber);

                    throw e;
                }

                break;

            case "ANDI":
                try
                {
                    argValue1 = variables.getValue(args[1]);
                    variables.setValue(args[0], argValue1 & args[2]);
                }
                catch(SymbolError e)
                {
                    e.setLineNumber(lineNumber);

                    throw e;
                }

                break;

            case "OR":
                try
                {
                    argValue1 = variables.getValue(args[1]);
                    argValue2 = variables.getValue(args[2]);
                    variables.setValue(args[0], argValue1 | argValue2);
                }
                catch(SymbolError e)
                {
                    e.setLineNumber(lineNumber);

                    throw e;
                }

                break;

            case "ORI":
                try
                {
                    argValue1 = variables.getValue(args[1]);
                    variables.setValue(args[0], argValue1 | args[2]);
                }
                catch(SymbolError e)
                {
                    e.setLineNumber(lineNumber);

                    throw e;
                }

                break;

            case "XOR":
                try
                {
                    argValue1 = variables.getValue(args[1]);
                    argValue2 = variables.getValue(args[2]);
                    variables.setValue(args[0], argValue1 ^ argValue2);
                }
                catch(SymbolError e)
                {
                    e.setLineNumber(lineNumber);

                    throw e;
                }

                break;

            case "XORI":
                try
                {
                    argValue1 = variables.getValue(args[1]);
                    variables.setValue(args[0], argValue1 ^ args[2]);
                }
                catch(SymbolError e)
                {
                    e.setLineNumber(lineNumber);

                    throw e;
                }

                break;

            case "NAND":
                try
                {
                    argValue1 = variables.getValue(args[1]);
                    argValue2 = variables.getValue(args[2]);
                    variables.setValue(args[0], ~(argValue1 & argValue2));
                }
                catch(SymbolError e)
                {
                    e.setLineNumber(lineNumber);

                    throw e;
                }

                break;

            case "NOR":
                try
                {
                    argValue1 = variables.getValue(args[1]);
                    argValue2 = variables.getValue(args[2]);
                    variables.setValue(args[0], ~(argValue1 | argValue2));
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
