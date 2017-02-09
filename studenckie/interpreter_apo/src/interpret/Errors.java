package interpret;

/**
Klasa rzucajaca wyjatki podczas wykonywania programu.
Wywolanie wyjatku powoduje natychmiastowe zakonczenie pracy interpretera.
*/
class Errors
{
 private static String[] arit_types={"Division by zero.", "Argument is not a number."};
 private static String[] mem_types={"Out of memory.", "Address is not alligned to a word.", "Number to store not in a byte."};
 private static String[] sym_types={"Cannot change variable \'zero\'.", "Not existing instruction.", "Too few arguments.", "Invalid symbols in variable name.\tVariables contain lower case only."};
 private static String[] lbl_types={"Label not found.", "Duplicated label.", "Variables and labels cannot have the same name.", "Invalid symbols in label name.\tLabels contain lower case only."};
 
 	/**
 	Wypisuje komunikat o wystapieniu wyjatku zwiazanego z operacjami arytmetycznymi.
 	@param x szczegolowy typ wyjatku
 	@param curline wiersz programu, w ktorym nastapil wyjatek
 	*/
	public static void arit_err(int x, int curline)
	{
	 System.out.println("error>> ArithmeticError at line "+curline+"\t"+arit_types[x]);
	 System.exit(0);
	}
	
	/**
	Wypisuje komunikat o wystapieniu wyjatku zwiazanego z operacjami na pamieci.
	@param x szczegolowy typ wyjatku
 	@param curline wiersz programu, w ktorym nastapil wyjatek
 	*/
	public static void mem_err(int x, int curline)
	{
	 System.out.println("error>> MemoryError at line "+curline+"\t"+mem_types[x]);
	 System.exit(0);
	}
	
	/**
	Wypisuje komunikat o wystapieniu wyjatku zwiazanego z instrukcjami badz zmiennymi.
	@param x szczegolowy typ wyjatku
 	@param curline wiersz programu, w ktorym nastapil wyjatek
	*/
	public static void sym_err(int x, int curline)
	{
	 System.out.println("error>> SymbolError at line "+curline+"\t"+sym_types[x]);
	 System.exit(0);
	}
	
	/**
	Wypisuje komunikat o wystapieniu wyjatku zwiazanego z etykietami.
	@param x szczegolowy typ wyjatku
 	@param curline wiersz programu, w ktorym nastapil wyjatek
 	*/
	public static void lbl_err(int x, int curline)
	{
	 System.out.println("error>> LabelError at line "+curline+"\t"+lbl_types[x]);
	 System.exit(0);
	}
}
