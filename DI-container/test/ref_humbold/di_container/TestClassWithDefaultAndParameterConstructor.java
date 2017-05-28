package ref_humbold.di_container;

class TestClassWithDefaultAndParameterConstructor
    implements TestBasicInterface
{
    private String text;

    public TestClassWithDefaultAndParameterConstructor()
    {
        this.text = "";
    }

    public TestClassWithDefaultAndParameterConstructor(String text)
    {
        this.text = text;
    }

    public String getText()
    {
        return text;
    }
}