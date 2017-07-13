package ref_humbold.apolanguage.interpret;

import ref_humbold.apolanguage.errors.MemoryError;

/**
 * Klasa odpowiedzialna za interakcje programu z pamiecia. Wykonuje instrukcje zapisu i odczytu
 * danych z pamieci.
 */
public class Memory
{
    private int[] memory;

    /**
     * Alokuje pamiec na potrzeby programu.
     * @param memorySize rozmiar pamieci do zaalokowania.
     */
    public Memory(int memorySize)
    {
        memory = new int[memorySize * 256];
        System.out.println("memory>> " + memorySize + "kB allocated");
    }

    /**
     * Odczytuje słowo 32 bit z pamieci.
     * @param address adres do zapisu
     * @param lineNumber numer linii programu
     */
    public int loadWord(int address, int lineNumber)
        throws MemoryError
    {
        if(address < 0 || address >= memory.length)
            throw new MemoryError(MemoryError.OUT_OF_MEMORY, lineNumber);

        if(address % 4 > 0)
            throw new MemoryError(MemoryError.ADDRESS_NOT_A_WORD, lineNumber);

        return memory[address / 4];
    }

    /**
     * Zapisuje słowo 32 bit do pamieci.
     * @param address adres do zapisu
     * @param value wartosc do zapisu
     * @param lineNumber numer linii programu
     */
    public void storeWord(int address, int value, int lineNumber)
        throws MemoryError
    {
        if(address < 0 || address >= memory.length)
            throw new MemoryError(MemoryError.OUT_OF_MEMORY, lineNumber);

        if(address % 4 > 0)
            throw new MemoryError(MemoryError.ADDRESS_NOT_A_WORD, lineNumber);

        memory[address / 4] = value;
    }

    /**
     * Odczytuje pojedynczy bajt z pamieci.
     * @param address adres do odczytu
     * @param lineNumber numer linii programu
     */
    public int loadByte(int address, int lineNumber)
        throws MemoryError
    {
        if(address < 0 || address >= memory.length)
            throw new MemoryError(MemoryError.OUT_OF_MEMORY, lineNumber);

        int shift = (3 - address % 4) * 8;

        return (memory[address / 4] & 0xFF << shift) >>> shift;
    }

    /**
     * Zapisuje liczbe okreslona na 1 bajcie do pamieci.
     * @param address adres do zapisu
     * @param value wartosc do zapisu
     * @param lineNumber numer linii programu
     */
    public void storeByte(int address, int value, int lineNumber)
        throws MemoryError
    {
        if(address < 0 || address >= memory.length)
            throw new MemoryError(MemoryError.OUT_OF_MEMORY, lineNumber);

        if(value < 0 || value >= 256)
            throw new MemoryError(MemoryError.NUMBER_NOT_IN_BYTE, lineNumber);

        int shift = (3 - address % 4) * 8;
        int tmp = memory[address / 4] & ~(0xFF << shift);

        memory[address / 4] = tmp | value << shift;
    }
}
