package ref_humbold.di_container;

public class IncorrectDependencyMethodException
    extends DIException
{
    private static final long serialVersionUID = 3707239480399538423L;

    public IncorrectDependencyMethodException()
    {
        super();
    }

    public IncorrectDependencyMethodException(String s)
    {
        super(s);
    }

    public IncorrectDependencyMethodException(Throwable t)
    {
        super(t);
    }

    public IncorrectDependencyMethodException(String s, Throwable t)
    {
        super(s, t);
    }
}