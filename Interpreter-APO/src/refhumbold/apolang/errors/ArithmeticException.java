package refhumbold.apolang.errors;

public class ArithmeticException
    extends LanguageException
{
    public static final String ZERO_DIVISION = "Division by zero.";
    public static final String NOT_A_NUMBER = "Not a number.";
    public static final String INVALID_FORMAT = "Invalid number format.";
    public static final String NEGATIVE_SHIFT = "Shift by negative value.";
    private static final long serialVersionUID = -5079970583212010548L;

    public ArithmeticException(String message, int lineNumber)
    {
        super(message, lineNumber);
    }

    public ArithmeticException(String message)
    {
        super(message);
    }

    public ArithmeticException(String message, Throwable t)
    {
        super(message, t);
    }
}
