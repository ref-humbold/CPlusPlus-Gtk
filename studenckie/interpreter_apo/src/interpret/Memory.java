package interpret;

/**
Klasa odpowiedzialna za interakcje programu z pamiecia.
Wykonuje instrukcje zapisu i odczytu danych z pamieci.
*/
class Memory
{
 private int length;
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
    {
        if(adr<0 || adr >= mem.length)
            interpret.Errors.memErr(0, curline);

        if(adr%4 > 0)
            interpret.Errors.memErr(1, curline);

        return mem[adr];
    }

    /**
    Zapisuje słowo 32 bit do pamieci.
    @param adr adres do zapisu
    @param var wartosc do zapisu
    @param curline numer linii programu
    */
    void storeWord(int adr, int var, int curline)
    {
        if(adr < 0 || adr >= mem.length)
            interpret.Errors.memErr(0, curline);

        if(adr%4 > 0)
            interpret.Errors.memErr(1, curline);

        mem[adr] = var;
    }

    /**
    Odczytuje pojedynczy bajt z pamieci.
    @param adr adres do odczytu
    @param curline numer linii programu
    */
    int loadByte(int adr, int curline)
    {
        if(adr < 0 || adr >= mem.length)
            interpret.Errors.memErr(0, curline);

        int shift = adr&3;
        int tmp = mem[adr-shift];
        tmp = ((tmp&(255<<(shift*8)))>>>(shift*8));
        return tmp;
    }

    /**
    Zapisuje liczbe okreslona na 1 bajcie do pamieci.
    @param adr adres do zapisu
    @param var wartosc do zapisu
    @param curline numer linii programu
    */
    void storeByte(int adr, int var, int curline)
    {
        if(adr < 0 || adr >= mem.length)
            interpret.Errors.memErr(0, curline);

         if(var < 0 || var >= 256)
            interpret.Errors.memErr(2, curline);

        int shift = adr&3;
        int tmp = mem[adr-shift]&(~(255<<(shift*8)));
        mem[adr-shift] = tmp|(var<<(shift*8));
    }
}
