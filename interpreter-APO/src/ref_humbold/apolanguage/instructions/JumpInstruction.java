package ref_humbold.apolanguage.instructions;

import ref_humbold.apolanguage.errors.LanguageError;
import ref_humbold.apolanguage.interpret.VariableSet;

/**
 * Klasa przechowująca pojedynczą instrukcję skoku w liście rozkazów.
 * @see Instruction
 */
public class JumpInstruction
    extends Instruction
{
    private Instruction link = null;
    private boolean isJump = false;

    public JumpInstruction(int lineNumber, String name, int... args)
    {
        super(lineNumber, name, args);
    }

    /**
     * Przechodzi do następnej instrukcji zależnej od wykonania skoku.
     * @param isJump informuje o wykonaniu skoku
     * @return następna instrukcja do wykonania
     */
    @Override
    public Instruction getNext(boolean isJump)
    {
        return this.isJump ? this.link : super.next;
    }

    @Override
    public Instruction clone()
    {
        JumpInstruction instruction = new JumpInstruction(lineNumber, name, args);

        instruction.setLink(link);
        instruction.setJump(isJump);

        return instruction;
    }

    /**
     * Ustawia wskaźnik do instrukcji, do ktorej może zostać wykonany skok.
     * @param link referencja do instrukcji
     */
    public void setLink(Instruction link)
    {
        this.link = link;
    }

    public void setJump(boolean jump)
    {
        this.isJump = jump;
    }

    public void execute(VariableSet variables)
        throws LanguageError
    {
        int argValue0;
        int argValue1;

        switch(name)
        {
            case "JUMP":
                isJump = true;
                break;

            case "JPEQ":
                argValue0 = variables.getValue(args[0]);
                argValue1 = variables.getValue(args[1]);
                isJump = argValue0 == argValue1;
                break;

            case "JPNE":
                argValue0 = variables.getValue(args[0]);
                argValue1 = variables.getValue(args[1]);
                isJump = argValue0 != argValue1;
                break;

            case "JPLT":
                argValue0 = variables.getValue(args[0]);
                argValue1 = variables.getValue(args[1]);
                isJump = argValue0 < argValue1;
                break;

            case "JPGT":
                argValue0 = variables.getValue(args[0]);
                argValue1 = variables.getValue(args[1]);
                isJump = argValue0 > argValue1;
                break;
        }
    }
}
