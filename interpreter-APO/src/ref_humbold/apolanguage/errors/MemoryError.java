package ref_humbold.apolanguage.errors;

public class MemoryError
	extends LanguageError
{
	private static final long serialVersionUID = 3780871563838319276L;
	private static String[] messages = new String[]{"Out of memory.", "Address is not alligned to a word.", "Number to store not in a byte."};

	/** @see LanguageError#LanguageError(String, int) */
	public MemoryError(String message, int curline)
	{
		super(message, curline);
	}

	/** @see LanguageError#LanguageError(String) */
	public MemoryError(String message)
	{
		super(message);
	}

	/**
	 * Tworzy blad na podstawie numeru.
	 * @param msgNum numer komunikatu
	 * @param curline numer linii wywołania błędu
	 */
	public MemoryError(int msgNum, int curline)
	{
		super(messages[msgNum], curline);
	}

	/**
	 * Tworzy blad na podstawie numeru.
	 * @param msgNum numer komunikatu
	 */
	public MemoryError(int msgNum)
	{
		super(messages[msgNum]);
	}
}
