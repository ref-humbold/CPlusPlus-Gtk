package ref_humbold.di_container;

class TestClassWithDependencySetterAndConstructor
    implements TestInterfaceDependencySetter
{
    private TestInterfaceBasic basicObject;

    public TestClassWithDependencySetterAndConstructor(TestInterfaceBasic basicObject)
    {
        this.basicObject = basicObject;
    }

    @Override
    public TestInterfaceBasic getBasicObject()
    {
        return basicObject;
    }

    @Override
    @DependencyMethod
    public void setBasicObject(TestInterfaceBasic basicObject)
    {
        this.basicObject = basicObject;
    }
}