package ref_humbold.apolanguage.errors;

public class LanguageError
    extends Exception
{
    private static final long serialVersionUID = 6805782578123143695L;
    private int line;

    public LanguageError(String message, int lineNumber)
        throws IllegalArgumentException
    {
        super(message);

        if(lineNumber < 0)
            throw new IllegalArgumentException("Line number has to be nonnegative.");

        line = lineNumber;
    }

    public LanguageError(String message)
    {
        super(message);
        line = -1;
    }

    public LanguageError(String message, Throwable t)
    {
        super(message, t);
        line = -1;
    }

    /** Wyświetla treść błędu na ekranie. */
    public void printError()
    {
        if(line >= 0)
            System.err.println("error>> " + this.getClass().getSimpleName() + " at line " + line
                               + "\t" + super.getMessage());
        else
            System.err.println("error>> " + this.getClass().getSimpleName() + "\t"
                               + super.getMessage());
    }
}
