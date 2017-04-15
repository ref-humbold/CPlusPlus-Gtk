package ref_humbold.apolanguage.interpret;

import java.nio.file.*;
import java.nio.charset.*;
import java.io.*;
import java.util.*;
import ref_humbold.apolanguage.errors.*;

/**
Klasa wykonujaca parsowanie programu.
Wczytuje kolejne linie programu, przetwarza je i tworzy liste instrukcji przechowywana w {@link InstructionList}.
Sprawdza poprawnosc składniowa programu oraz poprawnosc zapisu nazw operacji, zmiennych i etykiet.
Rowniez wykrywa komentarze w programie.
*/
class Parser
{
    private int varsNum;
    private Path plik;
    private ArrayList<String> etnums;
    private HashMap<String, Element> et;
    private HashMap<String, Integer> varies;
    private String[] splitted;

     /**
     Uruchamia parser i tworzy tymczasowe listy etykiet oraz zmiennych.
     @param p sciezka dostepu do pliku programu
     */
     public Parser(Path p)
     {
        varsNum = 1;
        plik = p;
        etnums = new ArrayList<String>();
        et = new HashMap<String, Element>();
        varies = new HashMap<String, Integer>();
     }

     /**
     Wykonuje parsowanie programu.
     Kolejno wczytuje linie z pliku programu, analizuje ich zawartosc i tworzy elementy listy instrukcji.
     @param v referencja do listy zmiennych utworzonej poczatkowo w {@link Controler}.
     @return lista instrukcji programu
     @see Element
     */
     InstructionList parse(VariableList v)
    	throws IOException, LanguageError
     {
        BufferedReader reader = Files.newBufferedReader(plik, StandardCharsets.UTF_8);
        InstructionList instr = new InstructionList();
        String line = reader.readLine();
        Element elem;
        String label = "";
        int[] t;
        int cnt = 0, g = 0;
        boolean isLbl;

        varies.put("zero", 0);

        while(line!=null)
        {
            cnt++;
            g = 0;
            line = line.trim();

            if(line.length() == 0 || line.startsWith("#") )
            {
                line = reader.readLine();
                continue;
            }

            splitted = line.split("\\s+");
            isLbl = splitted[g].endsWith(":");

            if(isLbl)
            {
                label = doLabel(splitted[g], cnt);
                g++;

                if(g >= splitted.length)
                {
                    t = doArgNone();
                    elem = instr.addInstr(cnt, "NOP", t, isLbl);
                    et.put(label, elem);
                    line = reader.readLine();
                    continue;
                }
            }

            t = doInstr(g, cnt);
            elem = instr.addInstr(cnt, splitted[g], t, isLbl);

            if(elem!=null)
            {
                et.put(label, elem);
            }

            line = reader.readLine();
        }

        checkVl();
        initVars(v);
        instr.startIt();

        while(instr.it != null)
        {
            if(instr.it instanceof ElemJump)
            {
                int lenJ = instr.it.arg.length;
                String etc = etnums.get(instr.it.arg[lenJ-1]);

                if(et.containsKey(etc) )
                    instr.setLink(et.get(etc) );
                else
                    throw new LabelError(0, instr.it.counter);
            }


            instr.nextIt(false);
        }

        return instr;
    }

    private void checkVl()
    	throws LabelError
    {
        Set<String> etset = et.keySet();
        Iterator<String> sIt = etset.iterator();
        String retIt;
        int ctlbl;

        while(sIt.hasNext())
        {
            retIt = sIt.next();

            if(varies.containsKey(retIt))
            {
                ctlbl = et.get(retIt).counter;
                throw new LabelError(2, ctlbl);
            }
        }
    }

    private void initVars(VariableList v)
    {
        Set<String> vrset = varies.keySet();
        Iterator<String> sIt = vrset.iterator();
        String retIt;

        while(sIt.hasNext())
        {
            retIt = sIt.next();
            v.addVar();
        }
    }

    private String doLabel(String lbl, int cnt)
        throws LabelError
    {
        String lbName = lbl.substring(0, lbl.length()-1);

        if(!allLower(lbName) )
            throw new LabelError(3, cnt);

        if(et.containsKey(lbName) )
            throw new LabelError(1, cnt);

        return lbName;
    }

    private int[] doInstr(int indx, int cnt)
    	throws LanguageError
    {
        String op = splitted[indx];
        int[] q = new int[0];

        if(op.startsWith("#") )
            return doArgNone();

        switch(op)
        {
            case "ADD":
                if(splitted.length < indx+3)
                    throw new SymbolError(2, cnt);

                q = new int[3];
                q[0] = doArgVar(indx+1, cnt, true);
                q[1] = doArgVar(indx+2, cnt, false);
                q[2] = doArgVar(indx+3, cnt, false);
                break;

            case "ADDI":
                if(splitted.length < indx+3)
                    throw new SymbolError(2, cnt);

                q = new int[3];
                q[0] = doArgVar(indx+1, cnt, true);
                q[1] = doArgVar(indx+2, cnt, false);
                q[2] = doArgImm(indx+3, cnt);
                break;

            case "SUB":
                if(splitted.length < indx+3)
                    throw new SymbolError(2, cnt);

                q = new int[3];
                q[0] = doArgVar(indx+1, cnt, true);
                q[1] = doArgVar(indx+2, cnt, false);
                q[2] = doArgVar(indx+3, cnt, false);
                break;

            case "SUBI":
                if(splitted.length < indx+3)
                    throw new SymbolError(2, cnt);

                q = new int[3];
                q[0] = doArgVar(indx+1, cnt, true);
                q[1] = doArgVar(indx+2, cnt, false);
                q[2] = doArgImm(indx+3, cnt);
                break;
            case "MUL":
                if(splitted.length < indx+3)
                    throw new SymbolError(2, cnt);

                q = new int[3];
                q[0] = doArgVar(indx+1, cnt, true);
                q[1] = doArgVar(indx+2, cnt, false);
                q[2] = doArgVar(indx+3, cnt, false);
                break;

            case "MULI":
                if(splitted.length < indx+3)
                    throw new SymbolError(2, cnt);

                q = new int[3];
                q[0] = doArgVar(indx+1, cnt, true);
                q[1] = doArgVar(indx+2, cnt, false);
                q[2] = doArgImm(indx+3, cnt);
                break;

            case "DIV":
                if(splitted.length < indx+3)
                    throw new SymbolError(2, cnt);

                q = new int[3];
                q[0] = doArgVar(indx+1, cnt, true);
                q[1] = doArgVar(indx+2, cnt, false);
                q[2] = doArgVar(indx+3, cnt, false);
                break;

            case "DIVI":
                if(splitted.length < indx+3)
                    throw new SymbolError(2, cnt);

                q = new int[3];
                q[0] = doArgVar(indx+1, cnt, true);
                q[1] = doArgVar(indx+2, cnt, false);
                q[2] = doArgImm(indx+3, cnt);
                break;

            case "SHLT":
                if(splitted.length < indx+3)
                    throw new SymbolError(2, cnt);

                q = new int[3];
                q[0] = doArgVar(indx+1, cnt, true);
                q[1] = doArgVar(indx+2, cnt, false);
                q[2] = doArgImm(indx+3, cnt);
                break;

            case "SHRT":
                if(splitted.length < indx+3)
                    throw new SymbolError(2, cnt);

                q = new int[3];
                q[0] = doArgVar(indx+1, cnt, true);
                q[1] = doArgVar(indx+2, cnt, false);
                q[2] = doArgImm(indx+3, cnt);
                break;

            case "SHRS":
                if(splitted.length < indx+3)
                    throw new SymbolError(2, cnt);

                q = new int[3];
                q[0] = doArgVar(indx+1, cnt, true);
                q[1] = doArgVar(indx+2, cnt, false);
                q[2] = doArgImm(indx+3, cnt);
                break;

            case "AND":
                if(splitted.length < indx+3)
                    throw new SymbolError(2, cnt);

                q = new int[3];
                q[0] = doArgVar(indx+1, cnt, true);
                q[1] = doArgVar(indx+2, cnt, false);
                q[2] = doArgVar(indx+3, cnt, false);
                break;
            case "ANDI":
                if(splitted.length < indx+3)
                    throw new SymbolError(2, cnt);

                q = new int[3];
                q[0] = doArgVar(indx+1, cnt, true);
                q[1] = doArgVar(indx+2, cnt, false);
                q[2] = doArgImm(indx+3, cnt);
                break;

            case "OR":
                if(splitted.length < indx+3)
                    throw new SymbolError(2, cnt);

                q = new int[3];
                q[0] = doArgVar(indx+1, cnt, true);
                q[1] = doArgVar(indx+2, cnt, false);
                q[2] = doArgVar(indx+3, cnt, false);
                break;

            case "ORI":
                if(splitted.length < indx+3)
                    throw new SymbolError(2, cnt);

                q = new int[3];
                q[0] = doArgVar(indx+1, cnt, true);
                q[1] = doArgVar(indx+2, cnt, false);
                q[2] = doArgImm(indx+3, cnt);
                break;

            case "XOR":
                if(splitted.length < indx+3)
                    throw new SymbolError(2, cnt);

                q = new int[3];
                q[0] = doArgVar(indx+1, cnt, true);
                q[1] = doArgVar(indx+2, cnt, false);
                q[2] = doArgVar(indx+3, cnt, false);
                break;

            case "XORI":
                if(splitted.length < indx+3)
                    throw new SymbolError(2, cnt);

                q = new int[3];
                q[0] = doArgVar(indx+1, cnt, true);
                q[1] = doArgVar(indx+2, cnt, false);
                q[2] = doArgImm(indx+3, cnt);
                break;
            case "NAND":
                if(splitted.length < indx+3)
                    throw new SymbolError(2, cnt);

                q = new int[3];
                q[0] = doArgVar(indx+1, cnt, true);
                q[1] = doArgVar(indx+2, cnt, false);
                q[2] = doArgVar(indx+3, cnt, false);
                break;

            case "NOR":
                if(splitted.length < indx+3)
                    throw new SymbolError(2, cnt);

                q = new int[3];
                q[0] = doArgVar(indx+1, cnt, true);
                q[1] = doArgVar(indx+2, cnt, false);
                q[2] = doArgVar(indx+3, cnt, false);
                break;

            case "JUMP":
                if(splitted.length < indx+1)
                    throw new SymbolError(2, cnt);

                q = new int[1];
                q[0] = doArgLbl(indx+1, cnt);
                break;

            case "JPEQ":
                if(splitted.length < indx+3)
                    throw new SymbolError(2, cnt);

                q = new int[3];
                q[0] = doArgVar(indx+1, cnt, false);
                q[1] = doArgVar(indx+2, cnt, false);
                q[2] = doArgLbl(indx+3, cnt);
                break;

            case "JPNE":
                if(splitted.length < indx+3)
                    throw new SymbolError(2, cnt);

                q = new int[3];
                q[0] = doArgVar(indx+1, cnt, false);
                q[1] = doArgVar(indx+2, cnt, false);
                q[2] = doArgLbl(indx+3, cnt);
                break;
            case "JPLT":
                if(splitted.length < indx+3)
                    throw new SymbolError(2, cnt);

                q = new int[3];
                q[0] = doArgVar(indx+1, cnt, false);
                q[1] = doArgVar(indx+2, cnt, false);
                q[2] = doArgLbl(indx+3, cnt);
                break;

            case "JPGT":
                if(splitted.length < indx+3)
                    throw new SymbolError(2, cnt);

                q = new int[3];
                q[0] = doArgVar(indx+1, cnt, false);
                q[1] = doArgVar(indx+2, cnt, false);
                q[2] = doArgLbl(indx+3, cnt);
                break;

            case "LDW":
                if(splitted.length < indx+2)
                    throw new SymbolError(2, cnt);

                q = new int[2];
                q[0] = doArgVar(indx+1, cnt, true);
                q[1] = doArgVar(indx+2, cnt, true);
                break;

            case "LDB":
                if(splitted.length < indx+2)
                    throw new SymbolError(2, cnt);

                q = new int[2];
                q[0] = doArgVar(indx+1, cnt, true);
                q[1] = doArgVar(indx+2, cnt, true);
                break;

            case "STW":
                if(splitted.length < indx+2)
                    throw new SymbolError(2, cnt);

                q = new int[2];
                q[0] = doArgVar(indx+1, cnt, false);
                q[1] = doArgVar(indx+2, cnt, true);
                break;

            case "STB":
                if(splitted.length < indx+2)
                    throw new SymbolError(2, cnt);

                q = new int[2];
                q[0] = doArgVar(indx+1, cnt, false);
                q[1] = doArgVar(indx+2, cnt, true);
                break;

            case "PTLN":
                q = doArgNone();
                break;

            case "PTINT":
                if(splitted.length < indx+1)
                    throw new SymbolError(2, cnt);

                q = new int[1];
                q[0] = doArgVar(indx+1, cnt, false);
                break;

            case "PTCHR":
                if(splitted.length < indx+1)
                    throw new SymbolError(2, cnt);

                q = new int[1];
                q[0] = doArgVar(indx+1, cnt, false);
                break;

            case "RDINT":
                if(splitted.length < indx+1)
                    throw new SymbolError(2, cnt);

                q = new int[1];
                q[0] = doArgVar(indx+1, cnt, true);
                break;

            case "RDCHR":
                if(splitted.length < indx+1)
                    throw new SymbolError(2, cnt);

                q = new int[1];
                q[0] = doArgVar(indx+1, cnt, true);
                break;

            default:
                throw new SymbolError(1, cnt);
         }

        return q;
    }

    private int[] doArgNone()
    {
        int[] q = new int[3];
        q[0] = -1;
        q[1] = -1;
        q[2] = -1;
        return q;
    }

    private int doArgVar(int indx, int cnt, boolean checkZero)
    	throws SymbolError
    {
         if(splitted[indx].startsWith("#") )
            throw new SymbolError(2, cnt);

         if(!allLower(splitted[indx]) )
            throw new SymbolError(3, cnt);

        if(checkZero && splitted[indx] == "zero")
            throw new SymbolError(0, cnt);

        if(!varies.containsKey(splitted[indx]) )
        {
            varies.put(splitted[indx], varsNum);
            varsNum++;
        }

        return varies.get(splitted[indx]);
    }

    private int doArgImm(int indx, int cnt)
    	throws LanguageError
    {
        int ret = 0;

        if(splitted[indx].startsWith("#") )
            throw new SymbolError(2, cnt);

        if(splitted[indx].startsWith("0x") )
        {
            try
            {
                ret = Integer.parseInt(splitted[indx].substring(2, splitted[indx].length()), 16);
            }
            catch (NumberFormatException e)
            {
                throw new ArithmeticError(1, cnt);
            }
        }
        else
        {
            try
            {
                ret = Integer.parseInt(splitted[indx]);
            }
            catch (NumberFormatException e)
            {
                throw new ArithmeticError(1, cnt);
            }
        }

        return ret;
    }

    private int doArgLbl(int indx, int cnt)
    	throws LanguageError
    {
        if(splitted[indx].startsWith("#") )
            throw new SymbolError(2, cnt);

        if(!allLower(splitted[indx]) )
            throw new LabelError(3, cnt);

        if(etnums.indexOf(splitted[indx]) < 0)
            etnums.add(splitted[indx]);

        return etnums.indexOf(splitted[indx]);
     }

     private boolean allLower(String s)
     {
         for(int i = 0; i < s.length(); ++i)
             if(s.charAt(i) < 'a' || s.charAt(i) > 'z')
                return false;

         return true;
     }
}
