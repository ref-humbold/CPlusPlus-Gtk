package refhumbold.apolang.errors;

public class MemoryException
    extends LanguageException
{
    public static final String OUT_OF_MEMORY = "Out of memory.";
    public static final String ADDRESS_NOT_A_WORD = "Address is not alligned to a word.";
    public static final String NUMBER_NOT_IN_BYTE = "Number to store not in a byte.";
    private static final long serialVersionUID = 3780871563838319276L;

    public MemoryException(String message, int lineNumber)
    {
        super(message, lineNumber);
    }

    public MemoryException(String message)
    {
        super(message);
    }

    public MemoryException(String message, Throwable t)
    {
        super(message, t);
    }
}
