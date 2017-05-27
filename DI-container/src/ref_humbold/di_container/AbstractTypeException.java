package ref_humbold.di_container;

public class AbstractTypeException
    extends DIException
{
    private static final long serialVersionUID = 5573956461991224741L;

    public AbstractTypeException()
    {
        super();
    }

    public AbstractTypeException(String s)
    {
        super(s);
    }

    public AbstractTypeException(Throwable t)
    {
        super(t);
    }

    public AbstractTypeException(String s, Throwable t)
    {
        super(s, t);
    }

    public AbstractTypeException(String s, Throwable t, boolean b1, boolean b2)
    {
        super(s, t, b1, b2);
    }

}
