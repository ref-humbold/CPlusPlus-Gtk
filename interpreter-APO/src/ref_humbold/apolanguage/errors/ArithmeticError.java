package ref_humbold.apolanguage.errors;

public class ArithmeticError
	extends LanguageError
{
	private static final long serialVersionUID = -5079970583212010548L;
	private static String[] messages = new String[]{"Division by zero.", "Argument is not a number."};

	/** @see LanguageError#LanguageError(String, int) */
	public ArithmeticError(String message, int curline)
	{
		super(message, curline);
	}
	
	/** @see LanguageError#LanguageError(String) */
	public ArithmeticError(String message)
	{
		super(message);
	}

	/**
	 * Tworzy blad na podstawie numeru.
	 * @param msgNum numer komunikatu
	 * @param curline numer linii wywołania błędu
	 */
	public ArithmeticError(int msgNum, int curline)
	{
		super(messages[msgNum], curline);
	}

	/**
	 * Tworzy blad na podstawie numeru.
	 * @param msgNum numer komunikatu
	 */
	public ArithmeticError(int msgNum)
	{
		super(messages[msgNum]);
	}
}
