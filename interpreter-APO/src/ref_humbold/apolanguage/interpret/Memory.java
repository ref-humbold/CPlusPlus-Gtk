package ref_humbold.apolanguage.interpret;

import ref_humbold.apolanguage.errors.MemoryError;

/**
Klasa odpowiedzialna za interakcje programu z pamiecia.
Wykonuje instrukcje zapisu i odczytu danych z pamieci.
*/
class Memory
{
    private int[] mem;

    /**
    Alokuje pamiec na potrzeby programu.
    @param memLen rozmiar pamieci do zaalokowania.
    */
    public Memory(int memLen)
    {
        mem = new int[memLen*256];
        System.out.println("memory>> "+memLen+"kB allocated");
    }

    /**
    Odczytuje słowo 32 bit z pamieci.
    @param adr adres do zapisu
    @param curline numer linii programu
    */
    int loadWord(int adr, int curline)
    	throws MemoryError
    {
        if(adr < 0 || adr >= mem.length)
            throw new MemoryError(0, curline);

        if(adr%4 > 0)
            throw new MemoryError(1, curline);

        return mem[adr/4];
    }

    /**
    Zapisuje słowo 32 bit do pamieci.
    @param adr adres do zapisu
    @param var wartosc do zapisu
    @param curline numer linii programu
    */
    void storeWord(int adr, int var, int curline)
    	throws MemoryError
    {
        if(adr < 0 || adr >= mem.length)
            throw new MemoryError(0, curline);

        if(adr%4 > 0)
            throw new MemoryError(1, curline);

        mem[adr/4] = var;
    }

    /**
    Odczytuje pojedynczy bajt z pamieci.
    @param adr adres do odczytu
    @param curline numer linii programu
    */
    int loadByte(int adr, int curline)
    	throws MemoryError
    {
        if(adr < 0 || adr >= mem.length)
            throw new MemoryError(0, curline);

        int shift = (3-adr%4)*8;
        
        return (mem[adr/4]&(0xFF<<shift))>>>shift;
    }

    /**
    Zapisuje liczbe okreslona na 1 bajcie do pamieci.
    @param adr adres do zapisu
    @param var wartosc do zapisu
    @param curline numer linii programu
    */
    void storeByte(int adr, int var, int curline)
    	throws MemoryError
    {
        if(adr < 0 || adr >= mem.length)
            throw new MemoryError(0, curline);

         if(var < 0 || var >= 256)
            throw new MemoryError(2, curline);

        int shift = (3-adr%4)*8;
        int tmp = mem[adr/4]&(~(0xFF<<shift));
        
        mem[adr/4] = tmp|(var<<shift);
    }
}
