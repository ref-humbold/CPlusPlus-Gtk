package interpret;
import java.util.*;

/** Klasa przechowujaca liste zmiennych wraz z ich wartosciami. */
class Variables
{
 private ArrayList <Integer> var_tab;
 
 	/** Tworzy nowa pusta liste zmiennych. */
	public Variables()
	{
	 var_tab=new ArrayList <Integer>();
	}
	
	/** Dodaje nowa zmienna do listy i zapisuje jej domyslna wartość 0. */
	void add_var()
	{
	 var_tab.add(0);
	}
	
	/**
	Pobiera wartosc okreslonej zmiennej.
	@param indx indeks zmiennej w liscie
	@return wartosc zmiennej
	*/
	int get_value(int indx)	 
	{		
	 return var_tab.get(indx);
	}
	
	/**
	Przypisuje nowa wartosc do okreslonej zmiennej w liscie.
	@param indx indeks zmiennej w liscie
	@param val wartosc do zapisu
	*/
	void set_value(int indx, int val)
	{
	 var_tab.set(indx, val);
	}
}
