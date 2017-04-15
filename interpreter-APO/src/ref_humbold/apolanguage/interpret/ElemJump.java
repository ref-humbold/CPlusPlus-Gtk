package ref_humbold.apolanguage.interpret;

/**
Klasa przechowujaca pojedyncza instrukcje skoku w liscie rozkazow.
Stanowi rozszerzenie klasy {@link Element}.
*/
class ElemJump extends Element
{
    private Element link;

    /** Tworzy element odpowiadajacy jednej instrukcji skoku. */
    public ElemJump(int cnt, String n, int a[])
    {
        super(cnt, n, a);
        link = null;
    }

    /**
    Przechodzi do nastepnej instrukcji zaleznej od wykonania skoku.
    Nadpisana metoda {@link Element#getNext} z klasy nadrzednej.
    @param isJump informuje o wykonaniu skoku
    @return nastepna instrukcja do wykonania
    */
    Element getNext(boolean isJump)
    {
        return isJump ? link : super.next;
    }

    /**
    Ustawia wskaznik do instrukcji, do ktorej zostanie wykonany skok, jesli sie powiedzie.
    @param e referencja do instrukcji, do ktorej wykonany zostanie skok.
    */
    @Override
    void setLink(Element e)
    {
        link = e;
    }
}
