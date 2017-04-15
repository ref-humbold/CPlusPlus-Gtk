package ref_humbold.apolanguage.errors;

public class LabelError
	extends LanguageError
{
	private static final long serialVersionUID = 7536066731780429351L;
	private static String[] messages = new String[]{"Label not found.", "Duplicated label.", "Variables and labels cannot have the same name.", "Invalid symbols in label name. Labels contain lower case only."};
	
	/** @see LanguageError#LanguageError(String, int) */
	public LabelError(String message, int curline)
	{
		super(message, curline);
	}

	/** @see LanguageError#LanguageError(String) */
	public LabelError(String message)
	{
		super(message);
	}
	
	/**
	 * Tworzy blad na podstawie numeru.
	 * @param msgNum numer komunikatu
	 * @param curline numer linii wywołania błędu
	 */
	public LabelError(int msgNum, int curline)
	{
		super(messages[msgNum], curline);
	}
	
	/**
	 * Tworzy blad na podstawie numeru.
	 * @param msgNum numer komunikatu
	 */
	public LabelError(int msgNum)
	{
		super(messages[msgNum]);
	}
}
