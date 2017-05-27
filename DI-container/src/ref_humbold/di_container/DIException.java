package ref_humbold.di_container;

public class DIException
    extends Exception
{
    private static final long serialVersionUID = -3019200382390630637L;

    public DIException()
    {
        super();
    }

    public DIException(String s)
    {
        super(s);
    }

    public DIException(Throwable t)
    {
        super(t);
    }

    public DIException(String s, Throwable t)
    {
        super(s, t);
    }

    public DIException(String s, Throwable t, boolean b1, boolean b2)
    {
        super(s, t, b1, b2);
    }

}
