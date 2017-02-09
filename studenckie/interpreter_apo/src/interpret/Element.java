package interpret;

/**
Klasa przechowujaca pojedyncza instrukcje w liscie rozkazow.
Instrukcje skokow sa przechowywane w klasie {@link interpret.ElemJump}.
*/
class Element
{
    /** Numer wiersza programu. */
    int counter;

    /** Nazwa operacji. */
    String name;

    /** Argumenty operacji. */
    int[] arg;

    /** Wskaznik na nastepny element listy. */
    protected Element next;

    /** Tworzy element odpowiadajacy jednej instrukcji w programie. */
    public Element(int cnt, String n, int a[])
    {
        counter = cnt;
        name = n;
        arg = a;
        next = null;
    }

    /**
    Przechodzi do następnej instrukcji.
    Metoda zostanie nadpisana w klasie {@link interpret.ElemJump}.
    @param isJmp informuje o wykonaniu skoku
    @return nastepna instrukcja do wykonania
    */
    Element takeNext(boolean isJmp)
    {
        return next;
    }

    /**
    Ustawia wskaznika na nastepny element.
    @param e referencja do nastepnej instrukcji
    */
    void setNext(Element e)
    {
        next = e;
    }

    /**
    Metoda zostanie nadpisana w klasie {@link interpret.ElemJump}.
    @param e referencja do instrukcji, do ktorej wykonany zostanie skok
    */
    void setLink(Element e)
    {
    }
}
