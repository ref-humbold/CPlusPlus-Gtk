package ref_humbold.apolanguage.errors;

public class SymbolError
	extends LanguageError
{
	private static final long serialVersionUID = -7197078580020744575L;
	private static String[] messages = new String[]{"Cannot change variable \'zero\'.", "Not existing instruction.", "Too few arguments.", "Invalid symbols in variable name.\tVariableList contain lower case only."};

	/** @see LanguageError#LanguageError(String, int) */
	public SymbolError(String message, int curline)
	{
		super(message, curline);
	}

	/** @see LanguageError#LanguageError(String) */
	public SymbolError(String message)
	{
		super(message);
	}

	/**
	 * Tworzy blad na podstawie numeru.
	 * @param msgNum numer komunikatu
	 * @param curline numer linii wywołania błędu
	 */
	public SymbolError(int msgNum, int curline)
	{
		super(messages[msgNum], curline);
	}

	/**
	 * Tworzy blad na podstawie numeru.
	 * @param msgNum numer komunikatu
	 */
	public SymbolError(int msgNum)
	{
		super(messages[msgNum]);
	}
}
