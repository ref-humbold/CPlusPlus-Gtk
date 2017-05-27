package ref_humbold.apolanguage.errors;

public class ArithmeticError
    extends LanguageError
{
    private static final long serialVersionUID = -5079970583212010548L;
    public static final String ZERO_DIVISION = "Division by zero.";
    public static final String NOT_A_NUMBER = "Argument is not a number.";

    /** @see LanguageError#LanguageError(String, int) */
    public ArithmeticError(String message, int lineNumber)
    {
        super(message, lineNumber);
    }

    /** @see LanguageError#LanguageError(String) */
    public ArithmeticError(String message)
    {
        super(message);
    }
}
