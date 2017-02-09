package interpret;

/**
Klasa przechowujaca liste instrukcji programu.
Lista zostaje utworzona podczas parsowania.
@see interpret.Parser#parse
*/
class InstructionList
{
    /** Iterator przemieszczajacy sie po liscie instrukcji */
    interpret.Element it;

    private interpret.Element beg;
    private interpret.Element end;

    /** Tworzy nowa pusta liste rozkazow. */
    public InstructionList()
    {
        beg = null;
        end = null;
    }

    /**
    Dodaje nowa instrukcje do listy.
    @param cnt numer wiersza
    @param n nazwa instrukcji
    @param a argumenty instrukcji
    @param isLbl czy instrukcje poprzedza etykieta
    @return referencja do utworzonego elementu
    @see interpret.Element
    */
    interpret.Element addInstr(int cnt, String n, int a[], boolean isLbl)
    {
        interpret.Element e = n.startsWith("J") ? new interpret.ElemJump(cnt, n, a) : new interpret.Element(cnt, n, a);

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
    Bierze kolejny element listy.
    @param isJmp czy zostanie wykonany skok
    */
    void nextIt(boolean isJmp)
    {
        it = it.takeNext(isJmp);
    }

    /**
    Ustawia referencje do elementu, do ktorego moze zostac wykonany skok.
    @param e referencja do instrukcji, do ktorej moze zostac wykonany skok
    */
    void setLink(interpret.Element e)
    {
        it.setLink(e);
    }
}
