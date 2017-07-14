package ref_humbold.apolanguage.interpret;

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;

import ref_humbold.apolanguage.errors.ArithmeticError;
import ref_humbold.apolanguage.errors.LabelError;
import ref_humbold.apolanguage.errors.LanguageError;
import ref_humbold.apolanguage.errors.SymbolError;
import ref_humbold.apolanguage.instructions.Instruction;
import ref_humbold.apolanguage.instructions.InstructionFactory;
import ref_humbold.apolanguage.instructions.JumpInstruction;

/**
 * Klasa wykonujaca parsowanie programu. Wczytuje kolejne linie programu, przetwarza je i tworzy
 * liste instrukcji przechowywana w {@link InstructionList}. Sprawdza poprawnosc skladniowa programu
 * oraz poprawnosc zapisu nazw operacji, zmiennych i etykiet. Rowniez wykrywa komentarze w
 * programie.
 */
public class Parser
{
    private Path filepath;
    private List<String> labels = new ArrayList<>();
    private Map<String, Instruction> labeledInstructions = new HashMap<>();
    private String[] splitted;
    private VariableSet variables = new VariableSet();

    /**
     * Uruchamia parser i tworzy tymczasowe listy etykiet oraz zmiennych.
     * @param path sciezka dostepu do pliku programu
     */
    public Parser(Path path)
    {
        filepath = path;
    }

    /**
     * Inicjalizuje zmienne znalezione w programie. Kolejno wczytuje linie z pliku programu,
     * analizuje ich zawartosc i zapisuje zmienne w zbiorze.
     * @return zbiór zmiennych programu
     * @see VariableSet
     */
    VariableSet initVariables()
        throws IOException
    {
        VariableSet variables = new VariableSet();

        BufferedReader reader = Files.newBufferedReader(filepath, StandardCharsets.UTF_8);

        return variables;
    }

    /**
     * Wykonuje parsowanie programu. Kolejno wczytuje linie z pliku programu, analizuje ich
     * zawartosc i tworzy elementy listy instrukcji.
     * @param v lista zmiennych
     * @return lista instrukcji programu
     * @see Instruction
     */
    InstructionList parse(VariableSet v)
        throws IOException, LanguageError
    {
        BufferedReader reader = Files.newBufferedReader(filepath, StandardCharsets.UTF_8);
        InstructionList instr = new InstructionList();
        String line = reader.readLine();
        Instruction elem;
        String label = "";
        int[] t;
        int cnt = 0, g = 0;
        boolean isLbl;

        variables.setValue("zero", 0);

        while(line != null)
        {
            cnt++;
            g = 0;
            line = line.trim();

            if(line.length() == 0 || line.startsWith("#"))
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
                    elem = instr.addInstruction(InstructionFactory.create(cnt, "NOP", t), isLbl);
                    labeledInstructions.put(label, elem);
                    line = reader.readLine();
                    continue;
                }
            }

            t = doInstr(g, cnt);
            elem = instr.addInstruction(InstructionFactory.create(cnt, splitted[g], t), isLbl);

            if(elem != null)
                labeledInstructions.put(label, elem);

            line = reader.readLine();
        }

        checkVl();
        instr.startIt();

        while(instr.it != null)
        {
            if(instr.it instanceof JumpInstruction)
            {
                int lenJ = instr.it.getArgsNumber();
                String etc = labels.get(instr.it.getArg(lenJ - 1));

                if(labeledInstructions.containsKey(etc))
                    ((JumpInstruction)instr.it).setLink(labeledInstructions.get(etc));
                else
                    throw new LabelError(LabelError.LABEL_NOT_FOUND, instr.it.getLineNumber());
            }

            instr.nextIt(false);
        }

        v = variables;

        return instr;
    }

    private void checkVl()
        throws LabelError
    {
        Set<String> etset = labeledInstructions.keySet();
        Iterator<String> sIt = etset.iterator();
        String retIt;
        int ctlbl;

        while(sIt.hasNext())
        {
            retIt = sIt.next();

            if(variables.contains(retIt))
            {
                ctlbl = labeledInstructions.get(retIt).getLineNumber();
                throw new LabelError(LabelError.DUPLICATED, ctlbl);
            }
        }
    }

    private String doLabel(String lbl, int cnt)
        throws LabelError
    {
        String lbName = lbl.substring(0, lbl.length() - 1);

        if(!allLower(lbName))
            throw new LabelError(LabelError.INVALID_CHARACTERS, cnt);

        if(labeledInstructions.containsKey(lbName))
            throw new LabelError(LabelError.DUPLICATED, cnt);

        return lbName;
    }

    private int[] doInstr(int indx, int cnt)
        throws LanguageError
    {
        String op = splitted[indx];
        int[] q = new int[0];

        if(op.startsWith("#"))
            return doArgNone();

        switch(op)
        {
            case "ADD":
                if(splitted.length < indx + 3)
                    throw new SymbolError(SymbolError.TOO_FEW_ARGUMENTS, cnt);

                q = new int[3];
                q[0] = doArgVar(indx + 1, cnt, true);
                q[1] = doArgVar(indx + 2, cnt, false);
                q[2] = doArgVar(indx + 3, cnt, false);
                break;

            case "ADDI":
                if(splitted.length < indx + 3)
                    throw new SymbolError(SymbolError.TOO_FEW_ARGUMENTS, cnt);

                q = new int[3];
                q[0] = doArgVar(indx + 1, cnt, true);
                q[1] = doArgVar(indx + 2, cnt, false);
                q[2] = doArgImm(indx + 3, cnt);
                break;

            case "SUB":
                if(splitted.length < indx + 3)
                    throw new SymbolError(SymbolError.TOO_FEW_ARGUMENTS, cnt);

                q = new int[3];
                q[0] = doArgVar(indx + 1, cnt, true);
                q[1] = doArgVar(indx + 2, cnt, false);
                q[2] = doArgVar(indx + 3, cnt, false);
                break;

            case "SUBI":
                if(splitted.length < indx + 3)
                    throw new SymbolError(SymbolError.TOO_FEW_ARGUMENTS, cnt);

                q = new int[3];
                q[0] = doArgVar(indx + 1, cnt, true);
                q[1] = doArgVar(indx + 2, cnt, false);
                q[2] = doArgImm(indx + 3, cnt);
                break;
            case "MUL":
                if(splitted.length < indx + 3)
                    throw new SymbolError(SymbolError.TOO_FEW_ARGUMENTS, cnt);

                q = new int[3];
                q[0] = doArgVar(indx + 1, cnt, true);
                q[1] = doArgVar(indx + 2, cnt, false);
                q[2] = doArgVar(indx + 3, cnt, false);
                break;

            case "MULI":
                if(splitted.length < indx + 3)
                    throw new SymbolError(SymbolError.TOO_FEW_ARGUMENTS, cnt);

                q = new int[3];
                q[0] = doArgVar(indx + 1, cnt, true);
                q[1] = doArgVar(indx + 2, cnt, false);
                q[2] = doArgImm(indx + 3, cnt);
                break;

            case "DIV":
                if(splitted.length < indx + 3)
                    throw new SymbolError(SymbolError.TOO_FEW_ARGUMENTS, cnt);

                q = new int[3];
                q[0] = doArgVar(indx + 1, cnt, true);
                q[1] = doArgVar(indx + 2, cnt, false);
                q[2] = doArgVar(indx + 3, cnt, false);
                break;

            case "DIVI":
                if(splitted.length < indx + 3)
                    throw new SymbolError(SymbolError.TOO_FEW_ARGUMENTS, cnt);

                q = new int[3];
                q[0] = doArgVar(indx + 1, cnt, true);
                q[1] = doArgVar(indx + 2, cnt, false);
                q[2] = doArgImm(indx + 3, cnt);
                break;

            case "SHLT":
                if(splitted.length < indx + 3)
                    throw new SymbolError(SymbolError.TOO_FEW_ARGUMENTS, cnt);

                q = new int[3];
                q[0] = doArgVar(indx + 1, cnt, true);
                q[1] = doArgVar(indx + 2, cnt, false);
                q[2] = doArgImm(indx + 3, cnt);
                break;

            case "SHRT":
                if(splitted.length < indx + 3)
                    throw new SymbolError(SymbolError.TOO_FEW_ARGUMENTS, cnt);

                q = new int[3];
                q[0] = doArgVar(indx + 1, cnt, true);
                q[1] = doArgVar(indx + 2, cnt, false);
                q[2] = doArgImm(indx + 3, cnt);
                break;

            case "SHRS":
                if(splitted.length < indx + 3)
                    throw new SymbolError(SymbolError.TOO_FEW_ARGUMENTS, cnt);

                q = new int[3];
                q[0] = doArgVar(indx + 1, cnt, true);
                q[1] = doArgVar(indx + 2, cnt, false);
                q[2] = doArgImm(indx + 3, cnt);
                break;

            case "AND":
                if(splitted.length < indx + 3)
                    throw new SymbolError(SymbolError.TOO_FEW_ARGUMENTS, cnt);

                q = new int[3];
                q[0] = doArgVar(indx + 1, cnt, true);
                q[1] = doArgVar(indx + 2, cnt, false);
                q[2] = doArgVar(indx + 3, cnt, false);
                break;
            case "ANDI":
                if(splitted.length < indx + 3)
                    throw new SymbolError(SymbolError.TOO_FEW_ARGUMENTS, cnt);

                q = new int[3];
                q[0] = doArgVar(indx + 1, cnt, true);
                q[1] = doArgVar(indx + 2, cnt, false);
                q[2] = doArgImm(indx + 3, cnt);
                break;

            case "OR":
                if(splitted.length < indx + 3)
                    throw new SymbolError(SymbolError.TOO_FEW_ARGUMENTS, cnt);

                q = new int[3];
                q[0] = doArgVar(indx + 1, cnt, true);
                q[1] = doArgVar(indx + 2, cnt, false);
                q[2] = doArgVar(indx + 3, cnt, false);
                break;

            case "ORI":
                if(splitted.length < indx + 3)
                    throw new SymbolError(SymbolError.TOO_FEW_ARGUMENTS, cnt);

                q = new int[3];
                q[0] = doArgVar(indx + 1, cnt, true);
                q[1] = doArgVar(indx + 2, cnt, false);
                q[2] = doArgImm(indx + 3, cnt);
                break;

            case "XOR":
                if(splitted.length < indx + 3)
                    throw new SymbolError(SymbolError.TOO_FEW_ARGUMENTS, cnt);

                q = new int[3];
                q[0] = doArgVar(indx + 1, cnt, true);
                q[1] = doArgVar(indx + 2, cnt, false);
                q[2] = doArgVar(indx + 3, cnt, false);
                break;

            case "XORI":
                if(splitted.length < indx + 3)
                    throw new SymbolError(SymbolError.TOO_FEW_ARGUMENTS, cnt);

                q = new int[3];
                q[0] = doArgVar(indx + 1, cnt, true);
                q[1] = doArgVar(indx + 2, cnt, false);
                q[2] = doArgImm(indx + 3, cnt);
                break;
            case "NAND":
                if(splitted.length < indx + 3)
                    throw new SymbolError(SymbolError.TOO_FEW_ARGUMENTS, cnt);

                q = new int[3];
                q[0] = doArgVar(indx + 1, cnt, true);
                q[1] = doArgVar(indx + 2, cnt, false);
                q[2] = doArgVar(indx + 3, cnt, false);
                break;

            case "NOR":
                if(splitted.length < indx + 3)
                    throw new SymbolError(SymbolError.TOO_FEW_ARGUMENTS, cnt);

                q = new int[3];
                q[0] = doArgVar(indx + 1, cnt, true);
                q[1] = doArgVar(indx + 2, cnt, false);
                q[2] = doArgVar(indx + 3, cnt, false);
                break;

            case "JUMP":
                if(splitted.length < indx + 1)
                    throw new SymbolError(SymbolError.TOO_FEW_ARGUMENTS, cnt);

                q = new int[1];
                q[0] = doArgLbl(indx + 1, cnt);
                break;

            case "JPEQ":
                if(splitted.length < indx + 3)
                    throw new SymbolError(SymbolError.TOO_FEW_ARGUMENTS, cnt);

                q = new int[3];
                q[0] = doArgVar(indx + 1, cnt, false);
                q[1] = doArgVar(indx + 2, cnt, false);
                q[2] = doArgLbl(indx + 3, cnt);
                break;

            case "JPNE":
                if(splitted.length < indx + 3)
                    throw new SymbolError(SymbolError.TOO_FEW_ARGUMENTS, cnt);

                q = new int[3];
                q[0] = doArgVar(indx + 1, cnt, false);
                q[1] = doArgVar(indx + 2, cnt, false);
                q[2] = doArgLbl(indx + 3, cnt);
                break;
            case "JPLT":
                if(splitted.length < indx + 3)
                    throw new SymbolError(SymbolError.TOO_FEW_ARGUMENTS, cnt);

                q = new int[3];
                q[0] = doArgVar(indx + 1, cnt, false);
                q[1] = doArgVar(indx + 2, cnt, false);
                q[2] = doArgLbl(indx + 3, cnt);
                break;

            case "JPGT":
                if(splitted.length < indx + 3)
                    throw new SymbolError(SymbolError.TOO_FEW_ARGUMENTS, cnt);

                q = new int[3];
                q[0] = doArgVar(indx + 1, cnt, false);
                q[1] = doArgVar(indx + 2, cnt, false);
                q[2] = doArgLbl(indx + 3, cnt);
                break;

            case "LDW":
                if(splitted.length < indx + 2)
                    throw new SymbolError(SymbolError.TOO_FEW_ARGUMENTS, cnt);

                q = new int[2];
                q[0] = doArgVar(indx + 1, cnt, true);
                q[1] = doArgVar(indx + 2, cnt, true);
                break;

            case "LDB":
                if(splitted.length < indx + 2)
                    throw new SymbolError(SymbolError.TOO_FEW_ARGUMENTS, cnt);

                q = new int[2];
                q[0] = doArgVar(indx + 1, cnt, true);
                q[1] = doArgVar(indx + 2, cnt, true);
                break;

            case "STW":
                if(splitted.length < indx + 2)
                    throw new SymbolError(SymbolError.TOO_FEW_ARGUMENTS, cnt);

                q = new int[2];
                q[0] = doArgVar(indx + 1, cnt, false);
                q[1] = doArgVar(indx + 2, cnt, true);
                break;

            case "STB":
                if(splitted.length < indx + 2)
                    throw new SymbolError(SymbolError.TOO_FEW_ARGUMENTS, cnt);

                q = new int[2];
                q[0] = doArgVar(indx + 1, cnt, false);
                q[1] = doArgVar(indx + 2, cnt, true);
                break;

            case "PTLN":
                q = doArgNone();
                break;

            case "PTINT":
                if(splitted.length < indx + 1)
                    throw new SymbolError(SymbolError.TOO_FEW_ARGUMENTS, cnt);

                q = new int[1];
                q[0] = doArgVar(indx + 1, cnt, false);
                break;

            case "PTCHR":
                if(splitted.length < indx + 1)
                    throw new SymbolError(SymbolError.TOO_FEW_ARGUMENTS, cnt);

                q = new int[1];
                q[0] = doArgVar(indx + 1, cnt, false);
                break;

            case "RDINT":
                if(splitted.length < indx + 1)
                    throw new SymbolError(SymbolError.TOO_FEW_ARGUMENTS, cnt);

                q = new int[1];
                q[0] = doArgVar(indx + 1, cnt, true);
                break;

            case "RDCHR":
                if(splitted.length < indx + 1)
                    throw new SymbolError(SymbolError.TOO_FEW_ARGUMENTS, cnt);

                q = new int[1];
                q[0] = doArgVar(indx + 1, cnt, true);
                break;

            default:
                throw new SymbolError(SymbolError.NO_SUCH_INSTRUCTION, cnt);
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
        if(splitted[indx].startsWith("#"))
            throw new SymbolError(SymbolError.TOO_FEW_ARGUMENTS, cnt);

        if(!allLower(splitted[indx]))
            throw new SymbolError(SymbolError.INVALID_CHARACTERS, cnt);

        if(checkZero && splitted[indx] == "zero")
            throw new SymbolError(SymbolError.CHANGE_ZERO, cnt);

        variables.setValue(splitted[indx]);

        return variables.getNumber(splitted[indx]);
    }

    private int doArgImm(int indx, int cnt)
        throws LanguageError
    {
        int ret = 0;

        if(splitted[indx].startsWith("#"))
            throw new SymbolError(SymbolError.TOO_FEW_ARGUMENTS, cnt);

        if(splitted[indx].startsWith("0x"))
            try
            {
                ret = Integer.parseInt(splitted[indx].substring(2, splitted[indx].length()), 16);
            }
            catch(NumberFormatException e)
            {
                throw new ArithmeticError(ArithmeticError.NOT_A_NUMBER, cnt);
            }
        else
            try
            {
                ret = Integer.parseInt(splitted[indx]);
            }
            catch(NumberFormatException e)
            {
                throw new ArithmeticError(ArithmeticError.NOT_A_NUMBER, cnt);
            }

        return ret;
    }

    private int doArgLbl(int indx, int cnt)
        throws LanguageError
    {
        if(splitted[indx].startsWith("#"))
            throw new SymbolError(SymbolError.TOO_FEW_ARGUMENTS, cnt);

        if(!allLower(splitted[indx]))
            throw new LabelError(LabelError.INVALID_CHARACTERS, cnt);

        if(labels.indexOf(splitted[indx]) < 0)
            labels.add(splitted[indx]);

        return labels.indexOf(splitted[indx]);
    }

    private boolean allLower(String s)
    {
        for(int i = 0; i < s.length(); ++i)
            if(s.charAt(i) < 'a' || s.charAt(i) > 'z')
                return false;

        return true;
    }
}
