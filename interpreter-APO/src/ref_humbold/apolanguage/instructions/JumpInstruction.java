package ref_humbold.apolanguage.instructions;

import ref_humbold.apolanguage.errors.SymbolError;
import ref_humbold.apolanguage.interpret.VariableSet;

/**
 * Klasa przechowujaca pojedyncza instrukcje skoku w liscie rozkazow.
 * @see Instruction
 */
public class JumpInstruction
    extends Instruction
{
    private Instruction link = null;
    private boolean isJump = false;

    public JumpInstruction(int lineNumber, InstructionName name, int... args)
    {
        super(lineNumber, name, args);
    }

    /**
     * Przechodzi do nastepnej instrukcji zaleznej od wykonania skoku.
     * @return nastepna instrukcja do wykonania
     */
    @Override
    public Instruction getNext()
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
     * Ustawia wskaznik do instrukcji, do ktorej moze zostac wykonany skok.
     * @param link referencja do instrukcji
     */
    public void setLink(Instruction link)
    {
        this.link = link;
    }

    /**
     * Ustawia mozliwosc wykonania skoku.
     * @param isJump czy wykonac skok
     */
    public void setJump(boolean isJump)
    {
        this.isJump = isJump;
    }

    @Override
    public void execute(VariableSet variables)
        throws SymbolError
    {
        int argValue0;
        int argValue1;

        switch(name)
        {
            case JUMP:
                isJump = true;
                break;

            case JPEQ:
                try
                {
                    argValue0 = variables.getValue(args[0]);
                    argValue1 = variables.getValue(args[1]);
                }
                catch(SymbolError e)
                {
                    e.setLineNumber(lineNumber);

                    throw e;
                }

                isJump = argValue0 == argValue1;
                break;

            case JPNE:
                try
                {
                    argValue0 = variables.getValue(args[0]);
                    argValue1 = variables.getValue(args[1]);
                }
                catch(SymbolError e)
                {
                    e.setLineNumber(lineNumber);

                    throw e;
                }

                isJump = argValue0 != argValue1;
                break;

            case JPLT:
                try
                {
                    argValue0 = variables.getValue(args[0]);
                    argValue1 = variables.getValue(args[1]);
                }
                catch(SymbolError e)
                {
                    e.setLineNumber(lineNumber);

                    throw e;
                }

                isJump = argValue0 < argValue1;
                break;

            case JPGT:
                try
                {
                    argValue0 = variables.getValue(args[0]);
                    argValue1 = variables.getValue(args[1]);
                }
                catch(SymbolError e)
                {
                    e.setLineNumber(lineNumber);

                    throw e;
                }

                isJump = argValue0 > argValue1;
                break;
        }
    }
}
