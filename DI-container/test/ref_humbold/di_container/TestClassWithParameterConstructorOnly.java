package ref_humbold.di_container;

class TestClassWithParameterConstructorOnly
    implements TestBasicInterface
{
    private int number;

    public TestClassWithParameterConstructorOnly(int number)
    {
        this.number = number;
    }

    public int getNumber()
    {
        return number;
    }
}