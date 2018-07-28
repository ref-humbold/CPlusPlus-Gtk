package ref_humbold.di_container.auxiliary.basics;

import ref_humbold.di_container.annotation.Dependency;
import ref_humbold.di_container.auxiliary.diamonds.InterfaceDiamonds1;

public class ClassBasicsComplexDependency
    implements InterfaceBasicsComplexDependency
{
    private InterfaceDiamonds1 firstObject;
    private InterfaceBasicsStringGetter secondObject;
    private InterfaceBasics basicObject;

    @Dependency
    public ClassBasicsComplexDependency(InterfaceDiamonds1 firstObject,
                                        InterfaceBasicsStringGetter secondObject)
    {
        this.firstObject = firstObject;
        this.secondObject = secondObject;
    }

    @Override
    public InterfaceDiamonds1 getFirstObject()
    {
        return firstObject;
    }

    @Override
    public InterfaceBasicsStringGetter getSecondObject()
    {
        return secondObject;
    }

    @Override
    public InterfaceBasics getBasicObject()
    {
        return basicObject;
    }

    @Override
    @Dependency
    public void setBasicObject(InterfaceBasics basicObject)
    {
        this.basicObject = basicObject;
    }
}
