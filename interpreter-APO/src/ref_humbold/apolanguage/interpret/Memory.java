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
     * Odczytuje slowo 32 bit z pamieci.
     * @param address adres do zapisu
     */
    public int loadWord(int address)
        throws MemoryError
    {
        if(address < 0 || address >= memory.length)
            throw new MemoryError(MemoryError.OUT_OF_MEMORY);

        if(address % 4 > 0)
            throw new MemoryError(MemoryError.ADDRESS_NOT_A_WORD);

        return memory[address / 4];
    }

    /**
     * Zapisuje slowo 32 bit do pamieci.
     * @param address adres do zapisu
     * @param value wartosc do zapisu
     */
    public void storeWord(int address, int value)
        throws MemoryError
    {
        if(address < 0 || address >= memory.length)
            throw new MemoryError(MemoryError.OUT_OF_MEMORY);

        if(address % 4 > 0)
            throw new MemoryError(MemoryError.ADDRESS_NOT_A_WORD);

        memory[address / 4] = value;
    }

    /**
     * Odczytuje pojedynczy bajt z pamieci.
     * @param address adres do odczytu
     */
    public int loadByte(int address)
        throws MemoryError
    {
        if(address < 0 || address >= memory.length)
            throw new MemoryError(MemoryError.OUT_OF_MEMORY);

        int shift = (3 - address % 4) * 8;

        return (memory[address / 4] & 0xFF << shift) >>> shift;
    }

    /**
     * Zapisuje liczbe okreslona na 1 bajcie do pamieci.
     * @param address adres do zapisu
     * @param value wartosc do zapisu
     */
    public void storeByte(int address, int value)
        throws MemoryError
    {
        if(address < 0 || address >= memory.length)
            throw new MemoryError(MemoryError.OUT_OF_MEMORY);

        if(value < 0 || value >= 256)
            throw new MemoryError(MemoryError.NUMBER_NOT_IN_BYTE);

        int shift = (3 - address % 4) * 8;
        int tmp = memory[address / 4] & ~(0xFF << shift);

        memory[address / 4] = tmp | value << shift;
    }
}
