package ref_humbold.apolanguage.errors;

public class LanguageError
    extends Exception
{
    private static final long serialVersionUID = 6805782578123143695L;
    private int lineNumber;

    public LanguageError(String message, int lineNumber)
        throws IllegalArgumentException
    {
        super(message);

        if(lineNumber < 0)
            throw new IllegalArgumentException("Line number has to be non-negative.");

        this.lineNumber = lineNumber;
    }

    public LanguageError(String message)
    {
        this(message, null);
    }

    public LanguageError(String message, Throwable t)
    {
        super(message, t);
        this.lineNumber = -1;
    }

    @Override
    public String toString()
    {
        return lineNumber >= 0 ? getClass().getSimpleName() + " at line " + lineNumber + ": "
                                 + getMessage() : getClass().getSimpleName() + ": " + getMessage();
    }

    public void setLineNumber(int lineNumber)
    {
        if(lineNumber < 0)
            throw new IllegalArgumentException("Line number has to be non-negative.");

        this.lineNumber = lineNumber;
    }
}
