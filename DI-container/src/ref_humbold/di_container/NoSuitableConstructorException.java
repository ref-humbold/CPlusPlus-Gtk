package ref_humbold.di_container;

public class NoSuitableConstructorException
    extends DIException
{
    private static final long serialVersionUID = 902034423730601801L;

    public NoSuitableConstructorException()
    {
        super();
    }

    public NoSuitableConstructorException(String s)
    {
        super(s);
    }

    public NoSuitableConstructorException(Throwable t)
    {
        super(t);
    }

    public NoSuitableConstructorException(String s, Throwable t)
    {
        super(s, t);
    }
}
