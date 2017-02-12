package ref_humbold.apolanguage.interpret;

import java.nio.file.*;
import java.nio.charset.*;
import java.io.*;
import java.util.*;

/**
Klasa kontrolujaca przebieg pracy interpretera.
Odpowiada za rozpoczecie parsowania oraz poprawne wykonanie interpretacji.
*/
public class Controler
{
    private interpret.Parser prs;
    private interpret.VariableList vrs;
    private interpret.Memory mry;
    private interpret.IOConnector iop;
    private interpret.InstructionList instr;

    /**
    Rozpoczyna prace interpretera i inicjalizuje jego skladniki.
    @param memLen rozmiar pamieci do alokacji
    @param p sciezka dostepu do pliku programu
    */
    public Controler(int memLen, Path p)
    {
        prs = new interpret.Parser(p);
        vrs = new interpret.VariableList();
        mry = new interpret.Memory(memLen);
        iop = new interpret.IOConnector();
        instr = null;
    }

    /**
    Dokonuje interpretacji programu.
    Na poczatku uruchamia parser ({@link interpret.Parser}) tworzacy liste instrukcji.
    Nastepnie kolejno odczytuje instrukcje z listy, pobiera zmienne, wykonuje operacje i zapisuje nowe wartosci do zmiennych.
    W razie potrzeby wywoluje dodatkowe skladniki interpretera.
    @see interpret.Memory
    @see interpret.IOConnector
    */
    public void make() throws Exception
    {
        System.out.print("parsing>> ");

        try
        {
            instr = prs.parse(vrs);
        }
        catch (Exception e)
        {
            System.err.println("Exception while parsing. Execution stopped.");
            return;
        }

        System.out.println("done");
        instr.startIt();
        vrs.setValue(0, 0);

        while(instr.it != null)
        {
            String curInstr = instr.it.name;
            int pc = instr.it.counter;
            int arg0, arg1, arg2;

            switch(curInstr)
            {
                case "ADD":
                   arg1 = vrs.getValue(instr.it.arg[1]);
                   arg2 = vrs.getValue(instr.it.arg[2]);
                   vrs.setValue(instr.it.arg[0], arg1+arg2);
                   instr.nextIt(false);
                   break;

                case "ADDI":
                   arg1 = vrs.getValue(instr.it.arg[1]);
                   arg2 = instr.it.arg[2];
                   vrs.setValue(instr.it.arg[0], arg1+arg2);
                   instr.nextIt(false);
                   break;

                case "SUB":
                   arg1 = vrs.getValue(instr.it.arg[1]);
                   arg2 = vrs.getValue(instr.it.arg[2]);
                   vrs.setValue(instr.it.arg[0], arg1-arg2);
                   instr.nextIt(false);
                   break;

                case "SUBI":
                   arg1 = vrs.getValue(instr.it.arg[1]);
                   arg2 = instr.it.arg[2];
                   vrs.setValue(instr.it.arg[0], arg1-arg2);
                   instr.nextIt(false);
                   break;

                case "MUL":
                   arg1 = vrs.getValue(instr.it.arg[1]);
                   arg2 = vrs.getValue(instr.it.arg[2]);
                   vrs.setValue(instr.it.arg[0], arg1*arg2);
                   instr.nextIt(false);
                   break;

                case "MULI":
                   arg1 = vrs.getValue(instr.it.arg[1]);
                   arg2 = instr.it.arg[2];
                   vrs.setValue(instr.it.arg[0], arg1*arg2);
                   instr.nextIt(false);
                   break;

                case "DIV":
                   arg1 = vrs.getValue(instr.it.arg[1]);
                   arg2 = vrs.getValue(instr.it.arg[2]);

                       if(arg2 == 0)
                       {
                           interpret.Errors.aritErr(0, pc);
                       }

                   vrs.setValue(instr.it.arg[0], arg1/arg2);
                   instr.nextIt(false);
                   break;

                case "DIVI":
                   arg1 = vrs.getValue(instr.it.arg[1]);
                   arg2 = instr.it.arg[2];

                       if(arg2 == 0)
                       {
                           interpret.Errors.aritErr(0, pc);
                       }

                   vrs.setValue(instr.it.arg[0], arg1/arg2);
                   instr.nextIt(false);
                   break;

                case "SHLT":
                   arg1 = vrs.getValue(instr.it.arg[1]);
                   arg2 = instr.it.arg[2];
                   vrs.setValue(instr.it.arg[0], (arg1<<arg2));
                   instr.nextIt(false);
                   break;

                case "SHRT":
                   arg1 = vrs.getValue(instr.it.arg[1]);
                   arg2 = instr.it.arg[2];
                   vrs.setValue(instr.it.arg[0], (arg1>>>arg2));
                   instr.nextIt(false);
                   break;

                case "SHRS":
                   arg1 = vrs.getValue(instr.it.arg[1]);
                   arg2 = instr.it.arg[2];
                   vrs.setValue(instr.it.arg[0], (arg1>>arg2));
                   instr.nextIt(false);
                   break;

                case "AND":
                   arg1 = vrs.getValue(instr.it.arg[1]);
                   arg2 = vrs.getValue(instr.it.arg[2]);
                   vrs.setValue(instr.it.arg[0], arg1&arg2);
                   instr.nextIt(false);
                   break;

                case "ANDI":
                   arg1 = vrs.getValue(instr.it.arg[1]);
                   arg2 = instr.it.arg[2];
                   vrs.setValue(instr.it.arg[0], arg1&arg2);
                   instr.nextIt(false);
                   break;

                case "OR":
                   arg1 = vrs.getValue(instr.it.arg[1]);
                   arg2 = vrs.getValue(instr.it.arg[2]);
                   vrs.setValue(instr.it.arg[0], arg1|arg2);
                   instr.nextIt(false);
                   break;

                case "ORI":
                   arg1 = vrs.getValue(instr.it.arg[1]);
                   arg2 = instr.it.arg[2];
                   vrs.setValue(instr.it.arg[0], arg1|arg2);
                   instr.nextIt(false);
                   break;

                case "XOR":
                   arg1 = vrs.getValue(instr.it.arg[1]);
                   arg2 = vrs.getValue(instr.it.arg[2]);
                   vrs.setValue(instr.it.arg[0], arg1^arg2);
                   instr.nextIt(false);
                   break;

                case "XORI":
                   arg1 = vrs.getValue(instr.it.arg[1]);
                   arg2 = instr.it.arg[2];
                   vrs.setValue(instr.it.arg[0], arg1^arg2);
                   instr.nextIt(false);
                   break;

                case "NAND":
                   arg1 = vrs.getValue(instr.it.arg[1]);
                   arg2 = vrs.getValue(instr.it.arg[2]);
                   vrs.setValue(instr.it.arg[0], ~(arg1&arg2));
                   instr.nextIt(false);
                   break;

                case "NOR":
                   arg1 = vrs.getValue(instr.it.arg[1]);
                   arg2 = vrs.getValue(instr.it.arg[2]);
                   vrs.setValue(instr.it.arg[0], ~(arg1|arg2));
                   instr.nextIt(false);
                   break;

                case "JUMP":
                   instr.nextIt(true);
                   break;

                case "JPEQ":
                   arg0 = vrs.getValue(instr.it.arg[0]);
                   arg1 = vrs.getValue(instr.it.arg[1]);
                   instr.nextIt(arg0 == arg1);
                   break;

                case "JPNE":
                   arg0 = vrs.getValue(instr.it.arg[0]);
                   arg1 = vrs.getValue(instr.it.arg[1]);
                   instr.nextIt(arg0 != arg1);
                   break;

                case "JPLT":
                   arg0 = vrs.getValue(instr.it.arg[0]);
                   arg1 = vrs.getValue(instr.it.arg[1]);
                   instr.nextIt(arg0 < arg1);
                   break;

                case "JPGT":
                   arg0 = vrs.getValue(instr.it.arg[0]);
                   arg1 = vrs.getValue(instr.it.arg[1]);
                   instr.nextIt(arg0 > arg1);
                   break;

                case "LDW":
                   arg1 = vrs.getValue(instr.it.arg[1]);
                   vrs.setValue(instr.it.arg[0], mry.loadWord(arg1, pc));
                   instr.nextIt(false);
                   break;

                case "LDB":
                   arg1 = vrs.getValue(instr.it.arg[1]);
                   vrs.setValue(instr.it.arg[0], mry.loadByte(arg1, pc));
                   instr.nextIt(false);
                   break;

                case "STW":
                   arg0 = vrs.getValue(instr.it.arg[0]);
                   arg1 = vrs.getValue(instr.it.arg[1]);
                   mry.storeWord(arg1, arg0, pc);
                   instr.nextIt(false);
                   break;

                case "STB":
                   arg0 = vrs.getValue(instr.it.arg[0]);
                   arg1 = vrs.getValue(instr.it.arg[1]);
                   mry.storeByte(arg1, arg0, pc);
                   instr.nextIt(false);
                   break;

                case "PTLN":
                   iop.printLine();
                   instr.nextIt(false);
                   break;

                case "PTINT":
                   arg0 = vrs.getValue(instr.it.arg[0]);
                   iop.printInt(arg0);
                   instr.nextIt(false);
                   break;

                case "PTCHR":
                   arg0 = vrs.getValue(instr.it.arg[0]);
                   iop.printChar(arg0);
                   instr.nextIt(false);
                   break;

                case "RDINT":
                   vrs.setValue(instr.it.arg[0], iop.readInt());
                   instr.nextIt(false);
                   break;

                case "RDCHR":
                   vrs.setValue(instr.it.arg[0], iop.readChar());
                   instr.nextIt(false);
                   break;

                case "NOP":
                   instr.nextIt(false);
                   break;
            }
        }
    }
}
