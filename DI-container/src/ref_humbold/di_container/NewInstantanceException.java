package ref_humbold.di_container;

public class NewInstantanceException
    extends Exception
{
    private static final long serialVersionUID = -9158372096510983551L;

    public NewInstantanceException()
    {
        super();
    }

    public NewInstantanceException(String s)
    {
        super(s);
    }

    public NewInstantanceException(Throwable t)
    {
        super(t);
    }

    public NewInstantanceException(String s, Throwable t)
    {
        super(s, t);
    }

    public NewInstantanceException(String s, Throwable t, boolean b1, boolean b2)
    {
        super(s, t, b1, b2);
    }

}
