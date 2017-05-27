package ref_humbold.apolanguage.interpret;

import ref_humbold.apolanguage.instructions.Instruction;
import ref_humbold.apolanguage.instructions.JumpInstruction;

/**
 * Klasa przechowujaca liste instrukcji programu. Lista zostaje utworzona podczas parsowania.
 * @see Parser#parse
 */
public class InstructionList
{
    /** Iterator przemieszczajacy sie po liscie instrukcji */
    Instruction it;

    private Instruction beg;
    private Instruction end;

    /** Tworzy nowa pusta liste rozkazow. */
    public InstructionList()
    {
        beg = null;
        end = null;
    }

    /**
     * Dodaje nowa instrukcje do listy.
     * @param cnt numer wiersza
     * @param n nazwa instrukcji
     * @param a argumenty instrukcji
     * @param isLbl czy instrukcje poprzedza etykieta
     * @return referencja do utworzonego elementu
     * @see Instruction
     */
    Instruction addInstr(int cnt, String n, int a[], boolean isLbl)
    {
        Instruction e = n.startsWith("J") ? new JumpInstruction(cnt, n, a) : new Instruction(cnt, n, a);

        if(beg == null)
            beg = e;
        else
            end.setNext(e);

        end = e;

        return isLbl ? e : null;
    }

    /** Rozpoczyna iteracje po liscie, ustawiajac iterator na poczatek listy. */
    void startIt()
    {
        it = beg;
    }

    /**
     * Bierze kolejny element listy.
     * @param isJmp czy zostanie wykonany skok
     */
    void nextIt(boolean isJmp)
    {
        it = it.getNext(isJmp);
    }
}
