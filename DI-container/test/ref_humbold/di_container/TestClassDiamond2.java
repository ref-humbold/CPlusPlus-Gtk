package ref_humbold.di_container;

class TestClassDiamond2
    implements TestInterfaceDiamond2
{
    private TestBasicInterface object;

    public TestClassDiamond2(TestBasicInterface object)
    {
        this.object = object;
    }

    @Override
    public TestBasicInterface getObject()
    {
        return object;
    }
}