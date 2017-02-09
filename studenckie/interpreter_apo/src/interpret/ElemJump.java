package interpret;

/**
Klasa przechowujaca pojedyncza instrukcje skoku w liscie rozkazow.
Stanowi rozszerzenie klasy {@link interpret.Element}.
*/
class ElemJump extends interpret.Element
{
 private interpret.Element link;
 
 	/** Tworzy element odpowiadajacy jednej instrukcji skoku. */
	public ElemJump(int cnt, String n, int a[])
	{
	 super(cnt, n, a);
	 link=null;
	}
	
	/**
	Przechodzi do nastepnej instrukcji zaleznej od wykonania skoku.
	Nadpisana metoda {@link interpret.Element#take_next} z klasy nadrzednej.
	@param is_jmp informuje o wykonaniu skoku
	@return nastepna instrukcja do wykonania
	*/
	interpret.Element take_next(boolean is_jmp)
	{
		if(is_jmp)
		{
		 return link;
		}
		else
		{
		 return super.next;
		}
	}
	
	/**
	Ustawia wskaznik do instrukcji, do ktorej zostanie wykonany skok, jesli sie powiedzie.
	Nadpisana metoda {@link interpret.Element#set_link} z klasy nadrzednej.
	@param e referencja do instrukcji, do ktorej wykonany zostanie skok.
	*/
	void set_link(interpret.Element e)
	{
	 link=e;
	}
}
