package ref_humbold.di_container;

interface TestInterface3
{
}

class TestClass3
    implements TestInterface3
{
    String text;

    public TestClass3()
    {
        this.text = "";
    }

    public TestClass3(String text)
    {
        this.text = text;
    }
}
