package ref_humbold.apolanguage.interpret;

import java.nio.file.Path;

import ref_humbold.apolanguage.errors.ArithmeticError;
import ref_humbold.apolanguage.errors.LanguageError;

/**
 * Klasa kontrolujaca przebieg pracy interpretera. Odpowiada za rozpoczecie parsowania oraz poprawne
 * wykonanie interpretacji.
 */
public class Controler
{
    private Parser prs;
    private VariableSet vrs;
    private Memory mry;
    private IOConnector iocon;
    private InstructionList instr;

    /**
     * Rozpoczyna prace interpretera i inicjalizuje jego skladniki.
     * @param memLen rozmiar pamieci do alokacji
     * @param p sciezka dostepu do pliku programu
     */
    public Controler(int memLen, Path p)
    {
        prs = new Parser(p);
        vrs = new VariableSet();
        mry = new Memory(memLen);
        iocon = new IOConnector();
        instr = null;
    }

    /**
     * Dokonuje parsowania programu. Uruchamia parser ({@link Parser}) tworzacy liste instrukcji.
     */
    public void parse()
        throws LanguageError, Exception
    {
        System.out.print("parsing>> ");
        instr = prs.parse(vrs);
        System.out.println("done");
    }

    /**
     * Dokonuje interpretacji programu. Kolejno odczytuje instrukcje z listy, pobiera zmienne,
     * wykonuje operacje i zapisuje nowe wartosci do zmiennych. W razie potrzeby wywoluje dodatkowe
     * skladniki interpretera.
     * @see Memory
     * @see IOConnector
     */
    public void make()
        throws LanguageError
    {
        instr.startIt();
        vrs.setValue(0, 0);

        while(instr.it != null)
        {
            String curInstr = instr.it.getName();
            int pc = instr.it.getLineNumber();
            int arg0, arg1, arg2;

            switch(curInstr)
            {
                case "ADD":
                    arg1 = vrs.getValue(instr.it.getArg(1));
                    arg2 = vrs.getValue(instr.it.getArg(2));
                    vrs.setValue(instr.it.getArg(0), arg1 + arg2);
                    instr.nextIt(false);
                    break;

                case "ADDI":
                    arg1 = vrs.getValue(instr.it.getArg(1));
                    arg2 = instr.it.getArg(2);
                    vrs.setValue(instr.it.getArg(0), arg1 + arg2);
                    instr.nextIt(false);
                    break;

                case "SUB":
                    arg1 = vrs.getValue(instr.it.getArg(1));
                    arg2 = vrs.getValue(instr.it.getArg(2));
                    vrs.setValue(instr.it.getArg(0), arg1 - arg2);
                    instr.nextIt(false);
                    break;

                case "SUBI":
                    arg1 = vrs.getValue(instr.it.getArg(1));
                    arg2 = instr.it.getArg(2);
                    vrs.setValue(instr.it.getArg(0), arg1 - arg2);
                    instr.nextIt(false);
                    break;

                case "MUL":
                    arg1 = vrs.getValue(instr.it.getArg(1));
                    arg2 = vrs.getValue(instr.it.getArg(2));
                    vrs.setValue(instr.it.getArg(0), arg1 * arg2);
                    instr.nextIt(false);
                    break;

                case "MULI":
                    arg1 = vrs.getValue(instr.it.getArg(1));
                    arg2 = instr.it.getArg(2);
                    vrs.setValue(instr.it.getArg(0), arg1 * arg2);
                    instr.nextIt(false);
                    break;

                case "DIV":
                    arg1 = vrs.getValue(instr.it.getArg(1));
                    arg2 = vrs.getValue(instr.it.getArg(2));

                    if(arg2 == 0)
                        throw new ArithmeticError(ArithmeticError.ZERO_DIVISION, pc);

                    vrs.setValue(instr.it.getArg(0), arg1 / arg2);
                    instr.nextIt(false);
                    break;

                case "DIVI":
                    arg1 = vrs.getValue(instr.it.getArg(1));
                    arg2 = instr.it.getArg(2);

                    if(arg2 == 0)
                        throw new ArithmeticError(ArithmeticError.ZERO_DIVISION, pc);

                    vrs.setValue(instr.it.getArg(0), arg1 / arg2);
                    instr.nextIt(false);
                    break;

                case "SHLT":
                    arg1 = vrs.getValue(instr.it.getArg(1));
                    arg2 = instr.it.getArg(2);
                    vrs.setValue(instr.it.getArg(0), arg1 << arg2);
                    instr.nextIt(false);
                    break;

                case "SHRT":
                    arg1 = vrs.getValue(instr.it.getArg(1));
                    arg2 = instr.it.getArg(2);
                    vrs.setValue(instr.it.getArg(0), arg1 >>> arg2);
                    instr.nextIt(false);
                    break;

                case "SHRS":
                    arg1 = vrs.getValue(instr.it.getArg(1));
                    arg2 = instr.it.getArg(2);
                    vrs.setValue(instr.it.getArg(0), arg1 >> arg2);
                    instr.nextIt(false);
                    break;

                case "AND":
                    arg1 = vrs.getValue(instr.it.getArg(1));
                    arg2 = vrs.getValue(instr.it.getArg(2));
                    vrs.setValue(instr.it.getArg(0), arg1 & arg2);
                    instr.nextIt(false);
                    break;

                case "ANDI":
                    arg1 = vrs.getValue(instr.it.getArg(1));
                    arg2 = instr.it.getArg(2);
                    vrs.setValue(instr.it.getArg(0), arg1 & arg2);
                    instr.nextIt(false);
                    break;

                case "OR":
                    arg1 = vrs.getValue(instr.it.getArg(1));
                    arg2 = vrs.getValue(instr.it.getArg(2));
                    vrs.setValue(instr.it.getArg(0), arg1 | arg2);
                    instr.nextIt(false);
                    break;

                case "ORI":
                    arg1 = vrs.getValue(instr.it.getArg(1));
                    arg2 = instr.it.getArg(2);
                    vrs.setValue(instr.it.getArg(0), arg1 | arg2);
                    instr.nextIt(false);
                    break;

                case "XOR":
                    arg1 = vrs.getValue(instr.it.getArg(1));
                    arg2 = vrs.getValue(instr.it.getArg(2));
                    vrs.setValue(instr.it.getArg(0), arg1 ^ arg2);
                    instr.nextIt(false);
                    break;

                case "XORI":
                    arg1 = vrs.getValue(instr.it.getArg(1));
                    arg2 = instr.it.getArg(2);
                    vrs.setValue(instr.it.getArg(0), arg1 ^ arg2);
                    instr.nextIt(false);
                    break;

                case "NAND":
                    arg1 = vrs.getValue(instr.it.getArg(1));
                    arg2 = vrs.getValue(instr.it.getArg(2));
                    vrs.setValue(instr.it.getArg(0), ~(arg1 & arg2));
                    instr.nextIt(false);
                    break;

                case "NOR":
                    arg1 = vrs.getValue(instr.it.getArg(1));
                    arg2 = vrs.getValue(instr.it.getArg(2));
                    vrs.setValue(instr.it.getArg(0), ~(arg1 | arg2));
                    instr.nextIt(false);
                    break;

                case "JUMP":
                    instr.nextIt(true);
                    break;

                case "JPEQ":
                    arg0 = vrs.getValue(instr.it.getArg(0));
                    arg1 = vrs.getValue(instr.it.getArg(1));
                    instr.nextIt(arg0 == arg1);
                    break;

                case "JPNE":
                    arg0 = vrs.getValue(instr.it.getArg(0));
                    arg1 = vrs.getValue(instr.it.getArg(1));
                    instr.nextIt(arg0 != arg1);
                    break;

                case "JPLT":
                    arg0 = vrs.getValue(instr.it.getArg(0));
                    arg1 = vrs.getValue(instr.it.getArg(1));
                    instr.nextIt(arg0 < arg1);
                    break;

                case "JPGT":
                    arg0 = vrs.getValue(instr.it.getArg(0));
                    arg1 = vrs.getValue(instr.it.getArg(1));
                    instr.nextIt(arg0 > arg1);
                    break;

                case "LDW":
                    arg1 = vrs.getValue(instr.it.getArg(1));
                    vrs.setValue(instr.it.getArg(0), mry.loadWord(arg1, pc));
                    instr.nextIt(false);
                    break;

                case "LDB":
                    arg1 = vrs.getValue(instr.it.getArg(1));
                    vrs.setValue(instr.it.getArg(0), mry.loadByte(arg1, pc));
                    instr.nextIt(false);
                    break;

                case "STW":
                    arg0 = vrs.getValue(instr.it.getArg(0));
                    arg1 = vrs.getValue(instr.it.getArg(1));
                    mry.storeWord(arg1, arg0, pc);
                    instr.nextIt(false);
                    break;

                case "STB":
                    arg0 = vrs.getValue(instr.it.getArg(0));
                    arg1 = vrs.getValue(instr.it.getArg(1));
                    mry.storeByte(arg1, arg0, pc);
                    instr.nextIt(false);
                    break;

                case "PTLN":
                    iocon.printLine();
                    instr.nextIt(false);
                    break;

                case "PTINT":
                    arg0 = vrs.getValue(instr.it.getArg(0));
                    iocon.printInt(arg0);
                    instr.nextIt(false);
                    break;

                case "PTCHR":
                    arg0 = vrs.getValue(instr.it.getArg(0));
                    iocon.printChar(arg0);
                    instr.nextIt(false);
                    break;

                case "RDINT":
                    vrs.setValue(instr.it.getArg(0), iocon.readInt());
                    instr.nextIt(false);
                    break;

                case "RDCHR":
                    vrs.setValue(instr.it.getArg(0), iocon.readChar());
                    instr.nextIt(false);
                    break;

                case "NOP":
                    instr.nextIt(false);
                    break;
            }
        }
    }
}
