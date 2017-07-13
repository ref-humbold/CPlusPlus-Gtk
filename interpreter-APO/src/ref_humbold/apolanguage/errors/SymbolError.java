package ref_humbold.apolanguage.errors;

public class SymbolError
    extends LanguageError
{
    private static final long serialVersionUID = -7197078580020744575L;
    public static String CHANGE_ZERO = "Cannot change variable \'zero\'.";
    public static String NO_SUCH_INSTRUCTION = "Not existing instruction.";
    public static String TOO_FEW_ARGUMENTS = "Too few arguments.";
    public static String INVALID_CHARACTERS = "Invalid characters in variable name";

    public SymbolError(String message, int lineNumber)
    {
        super(message, lineNumber);
    }

    public SymbolError(String message)
    {
        super(message);
    }

    public SymbolError(String message, Throwable t)
    {
        super(message, t);
    }
}
