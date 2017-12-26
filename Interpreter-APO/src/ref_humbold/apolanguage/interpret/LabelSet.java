package ref_humbold.apolanguage.interpret;

import java.util.HashMap;
import java.util.Map;

import ref_humbold.apolanguage.errors.LabelException;
import ref_humbold.apolanguage.instructions.Instruction;

/**
 * Klasa przechowujaca liste etykiet wraz z odpowiadajacymi im instrukcjami.
 */
public class LabelSet
{
    private int variableCount = 0;
    private Map<String, Integer> labelNumbers = new HashMap<>();
    private Map<Integer, Instruction> labelInstructions = new HashMap<>();

    public LabelSet()
    {
    }

    /**
     * Okreslanie numeru etykiety wzgledem jej nazwy.
     * @param name nazwa etykiety
     * @return numer etykiety
     */
    public int getNumber(String name)
    {
        return labelNumbers.get(name);
    }

    /**
     * Sprawdzanie, czy etykieta o okreslonej nazwie juz istnieje.
     * @param index numer etykiety
     * @return czy etykieta istnieje
     */
    public boolean contains(int index)
    {
        return labelInstructions.containsKey(index);
    }

    /**
     * Sprawdzanie, czy etykieta o okreslonej nazwie juz istnieje.
     * @param name nazwa etykiety
     * @return czy etykieta istnieje
     */
    public boolean contains(String name)
    {
        return labelNumbers.containsKey(name);
    }

    /**
     * Pobiera wartosc etykiety okreslona nazwa.
     * @param name nazwa etykiety
     * @return wartosc etykiety
     */
    public Instruction getInstruction(String name)
        throws LabelException
    {
        if(!contains(name))
            throw new LabelException(LabelException.LABEL_NOT_FOUND);

        return getInstruction(getNumber(name));
    }

    /**
     * Pobiera wartosc etykiety okreslonej numerem.
     * @param index numer etykiety
     * @return wartosc etykiety
     */
    public Instruction getInstruction(int index)
        throws LabelException
    {
        if(!contains(index))
            throw new LabelException(LabelException.LABEL_NOT_FOUND);

        return labelInstructions.get(index);
    }

    /**
     * Przypisuje nowa wartosc do etykiety okreslona nazwa.
     * @param name nazwa etykiety
     * @param value wartosc do zapisu
     */
    public void setInstruction(String name, Instruction value)
    {
        if(!contains(name))
        {
            labelNumbers.put(name, variableCount);
            ++variableCount;
        }

        labelInstructions.put(getNumber(name), value);
    }

    /**
     * Przypisuje nowa wartosc do etykiety okeslonej numerem.
     * @param index numer etykiety
     * @param value wartosc do zapisu
     */
    public void setInstruction(int index, Instruction value)
        throws LabelException
    {
        if(!contains(index))
            throw new LabelException(LabelException.LABEL_NOT_FOUND);

        labelInstructions.put(index, value);
    }
}
