package ref_humbold.di_container;

public class CircularDependenciesException
    extends DIException
{
    private static final long serialVersionUID = 607229069481348756L;

    public CircularDependenciesException()
    {
        super();
    }

    public CircularDependenciesException(String s)
    {
        super(s);
    }

    public CircularDependenciesException(Throwable t)
    {
        super(t);
    }

    public CircularDependenciesException(String s, Throwable t)
    {
        super(s, t);
    }

    public CircularDependenciesException(String s, Throwable t, boolean b1, boolean b2)
    {
        super(s, t, b1, b2);
    }

}
