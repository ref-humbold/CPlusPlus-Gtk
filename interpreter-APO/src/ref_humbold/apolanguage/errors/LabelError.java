package ref_humbold.apolanguage.errors;

public class LabelError
    extends LanguageError
{
    private static final long serialVersionUID = 7536066731780429351L;
    public static final String LABEL_NOT_FOUND = "Label not found.";
    public static final String DUPLICATED = "Duplicated label.";
    public static final String SAME_VARIABLE_NAME = "Label has the same name as variable.";
    public static final String INVALID_CHARACTERS = "Invalid characters in label name.";

    public LabelError(String message, int lineNumber)
    {
        super(message, lineNumber);
    }

    public LabelError(String message)
    {
        super(message);
    }

    public LabelError(String message, Throwable t)
    {
        super(message, t);
    }
}
