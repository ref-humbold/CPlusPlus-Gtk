package ref_humbold.di_container;

public class MultipleAnnotatedConstructorsException
    extends DIException
{
    private static final long serialVersionUID = 9149838622398855405L;

    public MultipleAnnotatedConstructorsException(String s)
    {
        super(s);
    }

    public MultipleAnnotatedConstructorsException(String s, Throwable t)
    {
        super(s, t);
    }
}
