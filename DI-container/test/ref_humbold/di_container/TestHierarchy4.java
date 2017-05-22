package ref_humbold.di_container;

interface TestInterface4
{
}

abstract class TestAbstractClass4
    implements TestInterface4
{
    public TestAbstractClass4()
    {
    }
}

class TestClass4
    extends TestAbstractClass4
{
    public TestClass4()
    {
        super();
    }
}
