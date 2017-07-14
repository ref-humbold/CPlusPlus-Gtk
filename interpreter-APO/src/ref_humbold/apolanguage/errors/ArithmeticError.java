package ref_humbold.apolanguage.errors;

public class ArithmeticError
    extends LanguageError
{
    private static final long serialVersionUID = -5079970583212010548L;
    public static final String ZERO_DIVISION = "Division by zero.";
    public static final String NOT_A_NUMBER = "Not a number.";
    public static final String INVALID_FORMAT = "Invalid number format.";
    public static final String NEGATIVE_SHIFT = "Shift by negative value.";

    public ArithmeticError(String message, int lineNumber)
    {
        super(message, lineNumber);
    }

    public ArithmeticError(String message)
    {
        super(message);
    }

    public ArithmeticError(String message, Throwable t)
    {
        super(message, t);
    }
}
