package ref_humbold.apolanguage.interpret;

import java.util.Iterator;
import java.util.NoSuchElementException;

import ref_humbold.apolanguage.instructions.Instruction;

/**
 * Klasa przechowująca listę instrukcji programu. Lista zostaje utworzona podczas parsowania.
 * @see Parser#parse
 */
public class InstructionList
    implements Iterable<Instruction>
{
    private class InstructionIterator
        implements Iterator<Instruction>
    {
        Instruction current;
        Instruction previous = null;

        public InstructionIterator(Instruction current)
        {
            this.current = current;
        }

        @Override
        public boolean hasNext()
        {
            return current != null;
        }

        @Override
        public Instruction next()
            throws NoSuchElementException
        {
            if(previous != null)
            {
                Instruction next = previous.getNext(false);

                if(next != null && !next.equalsLine(current))
                    current = next;
            }

            if(!hasNext())
                throw new NoSuchElementException();

            previous = current.clone();
            current = current.getNext(false);

            return previous;
        }
    }

    /**
     * Iterator przemieszczający sie po liście instrukcji
     */
    Instruction it;

    private Instruction begin = null;
    private Instruction end = null;

    public InstructionList()
    {
    }

    @Override
    public Iterator<Instruction> iterator()
    {
        return new InstructionIterator(begin);
    }

    /**
     * Dodaje nowa instrukcję do listy.
     * @param instruction instrukcja
     * @param isLabeled czy instrukcję poprzedza etykieta
     * @return referencja do utworzonego elementu
     * @see Instruction
     */
    Instruction addInstruction(Instruction instruction, boolean isLabeled)
    {
        if(begin == null)
            begin = instruction;
        else
            end.setNext(instruction);

        end = instruction;

        return isLabeled ? instruction : null;
    }

    /**
     * Rozpoczyna iterację po liście, ustawiając iterator na początek listy.
     */
    void startIt()
    {
        it = begin;
    }

    /**
     * Bierze kolejny element listy.
     * @param isJump czy zostanie wykonany skok
     */
    void nextIt(boolean isJump)
    {
        it = it.getNext(isJump);
    }
}
