package ref_humbold.di_container.exception;

public class MultipleAnnotatedConstructorsException
    extends DIException
{
    private static final long serialVersionUID = 9149838622398855405L;

    public MultipleAnnotatedConstructorsException(String s)
    {
        super(s);
    }
}
