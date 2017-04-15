package ref_humbold.apolanguage.interpret;

/**
Klasa przechowujaca pojedyncza instrukcje w liscie rozkazow.
Instrukcje skokow sa przechowywane w klasie {@link ElemJump}.
*/
class Element
{
    /** Numer wiersza programu. */
    protected int counter;

    /** Nazwa operacji. */
    protected String name;

    /** Argumenty operacji. */
    protected int[] arg;

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
    Metoda zostanie nadpisana w klasie {@link ElemJump}.
    @param isJmp informuje o wykonaniu skoku
    @return nastepna instrukcja do wykonania
    */
    Element getNext(boolean isJmp)
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
     * Porownuje dwa elementy na rownosc
     * @param obj element do porownania
     * @return czy oba elementy rowne
     */
    @Override
    public boolean equals(Object obj)
    {
    	if( !(obj instanceof Element) )
        	return false;
    
    	Element e = (Element)obj;
    		
    	return this.name == e.name && this.arg.equals(e.arg);
    }

    /**
    Metoda zostanie nadpisana w klasie {@link ElemJump}.
    @param e referencja do instrukcji, do ktorej wykonany zostanie skok
    */
    void setLink(Element e)
    {
    }
}
