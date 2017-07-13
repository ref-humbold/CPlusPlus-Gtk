package ref_humbold.apolanguage.instructions;

import ref_humbold.apolanguage.errors.ArithmeticError;
import ref_humbold.apolanguage.interpret.VariableSet;

public class ArithmeticInstruction
    extends Instruction
{
    public ArithmeticInstruction(int lineNumber, String name, int... args)
    {
        super(lineNumber, name, args);
    }

    @Override
    public ArithmeticInstruction clone()
    {
        ArithmeticInstruction instruction = new ArithmeticInstruction(lineNumber, name, args);

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
            case "ADD":
                argValue1 = variables.getValue(args[1]);
                argValue2 = variables.getValue(args[2]);
                variables.setValue(args[0], argValue1 + argValue2);
                break;

            case "ADDI":
                argValue1 = variables.getValue(args[1]);
                variables.setValue(args[0], argValue1 + args[2]);
                break;

            case "SUB":
                argValue1 = variables.getValue(args[1]);
                argValue2 = variables.getValue(args[2]);
                variables.setValue(args[0], argValue1 - argValue2);
                break;

            case "SUBI":
                argValue1 = variables.getValue(args[1]);
                variables.setValue(args[0], argValue1 - args[2]);
                break;

            case "MUL":
                argValue1 = variables.getValue(args[1]);
                argValue2 = variables.getValue(args[2]);
                variables.setValue(args[0], argValue1 * argValue2);
                break;

            case "MULI":
                argValue1 = variables.getValue(args[1]);
                variables.setValue(args[0], argValue1 * args[2]);
                break;

            case "DIV":
                argValue1 = variables.getValue(args[1]);
                argValue2 = variables.getValue(args[2]);

                if(argValue2 == 0)
                {
                    if(argValue1 == 0)
                        throw new ArithmeticError(ArithmeticError.NOT_A_NUMBER, lineNumber);

                    throw new ArithmeticError(ArithmeticError.ZERO_DIVISION, lineNumber);
                }

                variables.setValue(args[0], argValue1 / argValue2);
                break;

            case "DIVI":
                argValue1 = variables.getValue(args[1]);

                if(args[2] == 0)
                {
                    if(argValue1 == 0)
                        throw new ArithmeticError(ArithmeticError.NOT_A_NUMBER, lineNumber);

                    throw new ArithmeticError(ArithmeticError.ZERO_DIVISION, lineNumber);
                }

                variables.setValue(args[0], argValue1 / args[2]);
                break;
        }
    }
}
