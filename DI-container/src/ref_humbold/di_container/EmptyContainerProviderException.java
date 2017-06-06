package ref_humbold.di_container;

public class EmptyContainerProviderException
    extends DIException
{
    private static final long serialVersionUID = 6099774839770839995L;

    public EmptyContainerProviderException()
    {
        super();
    }

    public EmptyContainerProviderException(String s)
    {
        super(s);
    }

    public EmptyContainerProviderException(Throwable t)
    {
        super(t);
    }

    public EmptyContainerProviderException(String s, Throwable t)
    {
        super(s, t);
    }

    public EmptyContainerProviderException(String s, Throwable t, boolean b1, boolean b2)
    {
        super(s, t, b1, b2);
    }
}
