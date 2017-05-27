package ref_humbold.apolanguage.errors;

public class LabelError
    extends LanguageError
{
    private static final long serialVersionUID = 7536066731780429351L;
    public static final String LABEL_NOT_FOUND = "Label not found.";
    public static final String DUPLICATED = "Duplicated label.";
    public static final String SAME_VARIABLE_NAME = "Variables and labels cannot have the same name.";
    public static final String INVALID_CHARACTERS = "Invalid characters in label name.";

    /** @see LanguageError#LanguageError(String, int) */
    public LabelError(String message, int lineNumber)
    {
        super(message, lineNumber);
    }

    /** @see LanguageError#LanguageError(String) */
    public LabelError(String message)
    {
        super(message);
    }
}
