package ref_humbold.di_container;

class TestClassDiamond1
    implements TestInterfaceDiamond1
{
    private TestBasicInterface object;

    public TestClassDiamond1()
    {
        this.object = null;
    }

    public TestClassDiamond1(TestBasicInterface object)
    {
        this.object = object;
    }

    @Override
    public TestBasicInterface getObject()
    {
        return object;
    }
}