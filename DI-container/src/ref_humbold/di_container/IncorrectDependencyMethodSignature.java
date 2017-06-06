package ref_humbold.di_container;

public class IncorrectDependencyMethodSignature
    extends DIException
{
    private static final long serialVersionUID = 3707239480399538423L;

    public IncorrectDependencyMethodSignature()
    {
        super();
    }

    public IncorrectDependencyMethodSignature(String s)
    {
        super(s);
    }

    public IncorrectDependencyMethodSignature(Throwable t)
    {
        super(t);
    }

    public IncorrectDependencyMethodSignature(String s, Throwable t)
    {
        super(s, t);
    }

    public IncorrectDependencyMethodSignature(String s, Throwable t, boolean b1, boolean b2)
    {
        super(s, t, b1, b2);
    }

}
