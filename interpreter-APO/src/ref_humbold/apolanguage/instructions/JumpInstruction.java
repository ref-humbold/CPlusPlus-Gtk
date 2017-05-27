package ref_humbold.apolanguage.instructions;


/**
 * Klasa przechowujaca pojedyncza instrukcje skoku w liscie rozkazow. Stanowi rozszerzenie klasy
 * {@link Instruction}.
 */
public class JumpInstruction
    extends Instruction
{
    private Instruction link;

    /** Tworzy element odpowiadajacy jednej instrukcji skoku. */
    public JumpInstruction(int lineNumber, String name, int... args)
    {
        super(lineNumber, name, args);
        link = null;
    }

    /**
     * Przechodzi do nastepnej instrukcji zaleznej od wykonania skoku. Nadpisana metoda
     * {@link Instruction#getNext} z klasy nadrzednej.
     * @param isJump informuje o wykonaniu skoku
     * @return nastepna instrukcja do wykonania
     */
    @Override
    public Instruction getNext(boolean isJump)
    {
        return isJump ? link : super.next;
    }

    /**
     * Ustawia wskaznik do instrukcji, do ktorej zostanie wykonany skok, jesli sie powiedzie.
     * @param e referencja do instrukcji, do ktorej wykonany zostanie skok.
     */
    public void setLink(Instruction e)
    {
        link = e;
    }

    /*
     * public void execute(VariableSet variables)
     * throws LanguageError
     * {
     * case "JUMP":
     * break;
     * case "JPEQ":
     * break;
     * case "JPNE":
     * break;
     * case "JPLT":
     * break;
     * case "JPGT":
     * break;
     * }
     */
}
