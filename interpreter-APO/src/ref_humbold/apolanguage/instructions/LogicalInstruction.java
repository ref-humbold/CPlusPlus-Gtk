package ref_humbold.apolanguage.instructions;

import ref_humbold.apolanguage.errors.ArithmeticError;
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

    public void execute(VariableSet variables)
        throws ArithmeticError
    {
        int argValue1;
        int argValue2;

        switch(name)
        {
            case "SHLT":
                argValue1 = variables.getValue(args[1]);

                if(args[2] < 0)
                    throw new ArithmeticError(ArithmeticError.NEGATIVE_SHIFT, lineNumber);

                variables.setValue(args[0], argValue1 << args[2]);
                break;

            case "SHRT":
                argValue1 = variables.getValue(args[1]);

                if(args[2] < 0)
                    throw new ArithmeticError(ArithmeticError.NEGATIVE_SHIFT, lineNumber);

                variables.setValue(args[0], argValue1 >>> args[2]);
                break;

            case "SHRS":
                argValue1 = variables.getValue(args[1]);

                if(args[2] < 0)
                    throw new ArithmeticError(ArithmeticError.NEGATIVE_SHIFT, lineNumber);

                variables.setValue(args[0], argValue1 >> args[2]);
                break;

            case "AND":
                argValue1 = variables.getValue(args[1]);
                argValue2 = variables.getValue(args[2]);

                variables.setValue(args[0], argValue1 & argValue2);
                break;

            case "ANDI":
                argValue1 = variables.getValue(args[1]);

                variables.setValue(args[0], argValue1 & args[2]);
                break;

            case "OR":
                argValue1 = variables.getValue(args[1]);
                argValue2 = variables.getValue(args[2]);

                variables.setValue(args[0], argValue1 | argValue2);
                break;

            case "ORI":
                argValue1 = variables.getValue(args[1]);

                variables.setValue(args[0], argValue1 | args[2]);
                break;

            case "XOR":
                argValue1 = variables.getValue(args[1]);
                argValue2 = variables.getValue(args[2]);

                variables.setValue(args[0], argValue1 ^ argValue2);
                break;

            case "XORI":
                argValue1 = variables.getValue(args[1]);

                variables.setValue(args[0], argValue1 ^ args[2]);
                break;

            case "NAND":
                argValue1 = variables.getValue(args[1]);
                argValue2 = variables.getValue(args[2]);

                variables.setValue(args[0], ~(argValue1 & argValue2));
                break;

            case "NOR":
                argValue1 = variables.getValue(args[1]);
                argValue2 = variables.getValue(args[2]);

                variables.setValue(args[0], ~(argValue1 | argValue2));
                break;
        }
    }
}
