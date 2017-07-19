package ref_humbold.di_container;

public class MissingDependenciesException
    extends DIException
{
    private static final long serialVersionUID = 7265031467533657162L;

    public MissingDependenciesException()
    {
        super();
    }

    public MissingDependenciesException(String s)
    {
        super(s);
    }

    public MissingDependenciesException(Throwable t)
    {
        super(t);
    }

    public MissingDependenciesException(String s, Throwable t)
    {
        super(s, t);
    }
}
