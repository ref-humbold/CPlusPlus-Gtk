package refhumbold.apolang.errors;

public class SymbolException
    extends LanguageException
{
    public static final String CHANGE_ZERO = "Cannot change variable \'zero\'.";
    public static final String NO_SUCH_INSTRUCTION = "Not existing instruction.";
    public static final String TOO_FEW_ARGUMENTS = "Too few arguments.";
    public static final String INVALID_CHARACTERS = "Invalid characters in variable name.";
    public static final String VARIABLE_NOT_INIT = "Variable was not initialized.";
    private static final long serialVersionUID = -7197078580020744575L;

    public SymbolException(String message, int lineNumber)
    {
        super(message, lineNumber);
    }

    public SymbolException(String message)
    {
        super(message);
    }

    public SymbolException(String message, Throwable t)
    {
        super(message, t);
    }
}
