package ref_humbold.apolanguage.errors;

public class MemoryError
    extends LanguageError
{
    private static final long serialVersionUID = 3780871563838319276L;
    public static final String OUT_OF_MEMORY = "Out of memory.";
    public static final String ADDRESS_NOT_A_WORD = "Address is not alligned to a word.";
    public static final String NUMBER_NOT_IN_BYTE = "Number to store not in a byte.";

    /** @see LanguageError#LanguageError(String, int) */
    public MemoryError(String message, int lineNumber)
    {
        super(message, lineNumber);
    }

    /** @see LanguageError#LanguageError(String) */
    public MemoryError(String message)
    {
        super(message);
    }
}
