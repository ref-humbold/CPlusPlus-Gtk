package interpret;

/**
Klasa przechowujaca liste instrukcji programu.
Lista zostaje utworzona podczas parsowania.
@see interpret.Parser#parse
*/
class Instructions
{
 /** Iterator przemieszczajacy sie po liscie instrukcji */
 interpret.Element it;
 
 private interpret.Element beg;
 private interpret.Element end;
 
 	/** Tworzy nowa pusta liste rozkazow. */
	public Instructions()
	{
	 beg=null;
	 end=null;
	}
	
	/**
	Dodaje nowa instrukcje do listy.
	@param cnt numer wiersza 
	@param n nazwa instrukcji
	@param a argumenty instrukcji
	@param is_lbl czy instrukcje poprzedza etykieta
	@return referencja do utworzonego elementu
	@see interpret.Element
	*/
	interpret.Element add_instr(int cnt, String n, int a[], boolean is_lbl)
	{
	 interpret.Element e;
	 
		if(n.startsWith("J"))
		{
		 e=new interpret.ElemJump(cnt, n, a);
		}
		else
		{
		 e=new interpret.Element(cnt, n, a);
		}
		 
	 	if(beg==null)
		{
		 beg=e;
		}
		else
		{
		 end.set_next(e);
		}
			
	 end=e;
	 
		if(is_lbl)
		{
		 return e;
		}
			
	 return null;
	}
	
	/** Rozpoczyna iteracje po liscie, ustawiajac iterator na poczatek listy. */
	void start_it()
	{
	 it=beg;
	}
	
	/**
	Bierze kolejny element listy.
	@param is_jmp czy zostanie wykonany skok
	*/
	void next_it(boolean is_jmp)
	{
	 it=it.take_next(is_jmp);
	}
	
	/**
	Ustawia referencje do elementu, do ktorego moze zostac wykonany skok.
	@param e referencja do instrukcji, do ktorej moze zostac wykonany skok
	*/
	void set_link(interpret.Element e)
	{
	 it.set_link(e);
	}
}
