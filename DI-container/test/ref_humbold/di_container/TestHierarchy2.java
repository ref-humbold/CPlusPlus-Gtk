package ref_humbold.di_container;

interface TestInterface2
{
}

class TestClass2
    implements TestInterface2
{
    int number;

    public TestClass2(int number)
    {
        this.number = number;
    }
}

class TestClass20
    extends TestClass2
{
    public TestClass20()
    {
        super(20);
    }
}
