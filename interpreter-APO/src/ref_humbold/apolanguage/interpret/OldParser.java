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

import ref_humbold.apolanguage.errors.ArithmeticException;
import ref_humbold.apolanguage.errors.LabelException;
import ref_humbold.apolanguage.errors.LanguageException;
import ref_humbold.apolanguage.errors.SymbolException;
import ref_humbold.apolanguage.instructions.Instruction;
import ref_humbold.apolanguage.instructions.InstructionFactory;
import ref_humbold.apolanguage.instructions.InstructionName;
import ref_humbold.apolanguage.instructions.JumpInstruction;

/**
 * Klasa wykonujaca parsowanie programu. Wczytuje kolejne linie programu, przetwarza je i tworzy
 * liste instrukcji przechowywana w {@link InstructionList}. Sprawdza poprawnosc skladniowa programu
 * oraz poprawnosc zapisu nazw operacji, zmiennych i etykiet. Rowniez wykrywa komentarze w
 * programie.
 */
public class OldParser
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
    public OldParser(Path path)
    {
        filepath = path;
    }

    /**
     * Wykonuje parsowanie programu. Kolejno wczytuje linie z pliku programu, analizuje ich
     * zawartosc i tworzy elementy listy instrukcji.
     * @param v lista zmiennych
     * @return lista instrukcji programu
     * @see Instruction
     */
    InstructionList parse(VariableSet v)
        throws IOException, LanguageException
    {
        InstructionList instructionList = new InstructionList();
        BufferedReader reader = Files.newBufferedReader(filepath, StandardCharsets.UTF_8);
        String line = reader.readLine();
        Instruction elem;
        String label = "";
        int[] args;
        int count = 0, index = 0;
        boolean isLabel;

        variables.setValue("zero", 0);

        while(line != null)
        {
            ++count;
            index = 0;
            line = line.trim();

            if(line.length() == 0 || line.startsWith("#"))
            {
                line = reader.readLine();
                continue;
            }

            splitted = line.split("\\s+");
            isLabel = splitted[index].endsWith(":");

            if(isLabel)
            {
                label = doLabel(splitted[index], count);
                ++index;

                if(index >= splitted.length)
                {
                    elem = InstructionFactory.create(count, Instruction.convertToName("NOP"));
                    instructionList.add(elem);
                    labeledInstructions.put(label, elem);
                    line = reader.readLine();
                    continue;
                }
            }

            InstructionName name;

            try
            {
                name = Instruction.convertToName(splitted[index]);
            }
            catch(SymbolException e)
            {
                e.setLineNumber(count);

                throw e;
            }

            args = doInstr(index, count);
            elem = InstructionFactory.create(count, name, args);
            instructionList.add(elem);

            if(isLabel)
                labeledInstructions.put(label, elem);

            line = reader.readLine();
        }

        checkVariableAndLabelNames();

        for(Instruction instruction : instructionList)
        {
            if(instruction instanceof JumpInstruction)
            {
                int lenJ = instruction.getArgsNumber();
                String etc = labels.get(instruction.getArg(lenJ - 1));

                if(labeledInstructions.containsKey(etc))
                    ((JumpInstruction)instruction).setLink(labeledInstructions.get(etc));
                else
                    throw new LabelException(LabelException.LABEL_NOT_FOUND,
                                             instruction.getLineNumber());
            }
        }

        v = variables;

        return instructionList;
    }

    private void checkVariableAndLabelNames()
        throws LabelException
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
                throw new LabelException(LabelException.DUPLICATED, ctlbl);
            }
        }
    }

    private String doLabel(String lbl, int count)
        throws LabelException
    {
        String lbName = lbl.substring(0, lbl.length() - 1);

        if(!isLowerCase(lbName))
            throw new LabelException(LabelException.INVALID_CHARACTERS, count);

        if(labeledInstructions.containsKey(lbName))
            throw new LabelException(LabelException.DUPLICATED, count);

        return lbName;
    }

    private int[] doInstr(int index, int count)
        throws LanguageException
    {
        String op = splitted[index];
        int[] q = new int[0];

        if(op.startsWith("#"))
            return null;

        switch(op)
        {
            case "ADD":
                if(splitted.length < index + 3)
                    throw new SymbolException(SymbolException.TOO_FEW_ARGUMENTS, count);

                q = new int[3];
                q[0] = doArgVar(index + 1, count, true);
                q[1] = doArgVar(index + 2, count, false);
                q[2] = doArgVar(index + 3, count, false);
                break;

            case "ADDI":
                if(splitted.length < index + 3)
                    throw new SymbolException(SymbolException.TOO_FEW_ARGUMENTS, count);

                q = new int[3];
                q[0] = doArgVar(index + 1, count, true);
                q[1] = doArgVar(index + 2, count, false);
                q[2] = doArgImm(index + 3, count);
                break;

            case "SUB":
                if(splitted.length < index + 3)
                    throw new SymbolException(SymbolException.TOO_FEW_ARGUMENTS, count);

                q = new int[3];
                q[0] = doArgVar(index + 1, count, true);
                q[1] = doArgVar(index + 2, count, false);
                q[2] = doArgVar(index + 3, count, false);
                break;

            case "SUBI":
                if(splitted.length < index + 3)
                    throw new SymbolException(SymbolException.TOO_FEW_ARGUMENTS, count);

                q = new int[3];
                q[0] = doArgVar(index + 1, count, true);
                q[1] = doArgVar(index + 2, count, false);
                q[2] = doArgImm(index + 3, count);
                break;
            case "MUL":
                if(splitted.length < index + 3)
                    throw new SymbolException(SymbolException.TOO_FEW_ARGUMENTS, count);

                q = new int[3];
                q[0] = doArgVar(index + 1, count, true);
                q[1] = doArgVar(index + 2, count, false);
                q[2] = doArgVar(index + 3, count, false);
                break;

            case "MULI":
                if(splitted.length < index + 3)
                    throw new SymbolException(SymbolException.TOO_FEW_ARGUMENTS, count);

                q = new int[3];
                q[0] = doArgVar(index + 1, count, true);
                q[1] = doArgVar(index + 2, count, false);
                q[2] = doArgImm(index + 3, count);
                break;

            case "DIV":
                if(splitted.length < index + 3)
                    throw new SymbolException(SymbolException.TOO_FEW_ARGUMENTS, count);

                q = new int[3];
                q[0] = doArgVar(index + 1, count, true);
                q[1] = doArgVar(index + 2, count, false);
                q[2] = doArgVar(index + 3, count, false);
                break;

            case "DIVI":
                if(splitted.length < index + 3)
                    throw new SymbolException(SymbolException.TOO_FEW_ARGUMENTS, count);

                q = new int[3];
                q[0] = doArgVar(index + 1, count, true);
                q[1] = doArgVar(index + 2, count, false);
                q[2] = doArgImm(index + 3, count);
                break;

            case "SHLT":
                if(splitted.length < index + 3)
                    throw new SymbolException(SymbolException.TOO_FEW_ARGUMENTS, count);

                q = new int[3];
                q[0] = doArgVar(index + 1, count, true);
                q[1] = doArgVar(index + 2, count, false);
                q[2] = doArgImm(index + 3, count);
                break;

            case "SHRT":
                if(splitted.length < index + 3)
                    throw new SymbolException(SymbolException.TOO_FEW_ARGUMENTS, count);

                q = new int[3];
                q[0] = doArgVar(index + 1, count, true);
                q[1] = doArgVar(index + 2, count, false);
                q[2] = doArgImm(index + 3, count);
                break;

            case "SHRS":
                if(splitted.length < index + 3)
                    throw new SymbolException(SymbolException.TOO_FEW_ARGUMENTS, count);

                q = new int[3];
                q[0] = doArgVar(index + 1, count, true);
                q[1] = doArgVar(index + 2, count, false);
                q[2] = doArgImm(index + 3, count);
                break;

            case "AND":
                if(splitted.length < index + 3)
                    throw new SymbolException(SymbolException.TOO_FEW_ARGUMENTS, count);

                q = new int[3];
                q[0] = doArgVar(index + 1, count, true);
                q[1] = doArgVar(index + 2, count, false);
                q[2] = doArgVar(index + 3, count, false);
                break;
            case "ANDI":
                if(splitted.length < index + 3)
                    throw new SymbolException(SymbolException.TOO_FEW_ARGUMENTS, count);

                q = new int[3];
                q[0] = doArgVar(index + 1, count, true);
                q[1] = doArgVar(index + 2, count, false);
                q[2] = doArgImm(index + 3, count);
                break;

            case "OR":
                if(splitted.length < index + 3)
                    throw new SymbolException(SymbolException.TOO_FEW_ARGUMENTS, count);

                q = new int[3];
                q[0] = doArgVar(index + 1, count, true);
                q[1] = doArgVar(index + 2, count, false);
                q[2] = doArgVar(index + 3, count, false);
                break;

            case "ORI":
                if(splitted.length < index + 3)
                    throw new SymbolException(SymbolException.TOO_FEW_ARGUMENTS, count);

                q = new int[3];
                q[0] = doArgVar(index + 1, count, true);
                q[1] = doArgVar(index + 2, count, false);
                q[2] = doArgImm(index + 3, count);
                break;

            case "XOR":
                if(splitted.length < index + 3)
                    throw new SymbolException(SymbolException.TOO_FEW_ARGUMENTS, count);

                q = new int[3];
                q[0] = doArgVar(index + 1, count, true);
                q[1] = doArgVar(index + 2, count, false);
                q[2] = doArgVar(index + 3, count, false);
                break;

            case "XORI":
                if(splitted.length < index + 3)
                    throw new SymbolException(SymbolException.TOO_FEW_ARGUMENTS, count);

                q = new int[3];
                q[0] = doArgVar(index + 1, count, true);
                q[1] = doArgVar(index + 2, count, false);
                q[2] = doArgImm(index + 3, count);
                break;
            case "NAND":
                if(splitted.length < index + 3)
                    throw new SymbolException(SymbolException.TOO_FEW_ARGUMENTS, count);

                q = new int[3];
                q[0] = doArgVar(index + 1, count, true);
                q[1] = doArgVar(index + 2, count, false);
                q[2] = doArgVar(index + 3, count, false);
                break;

            case "NOR":
                if(splitted.length < index + 3)
                    throw new SymbolException(SymbolException.TOO_FEW_ARGUMENTS, count);

                q = new int[3];
                q[0] = doArgVar(index + 1, count, true);
                q[1] = doArgVar(index + 2, count, false);
                q[2] = doArgVar(index + 3, count, false);
                break;

            case "JUMP":
                if(splitted.length < index + 1)
                    throw new SymbolException(SymbolException.TOO_FEW_ARGUMENTS, count);

                q = new int[1];
                q[0] = doArgLbl(index + 1, count);
                break;

            case "JPEQ":
                if(splitted.length < index + 3)
                    throw new SymbolException(SymbolException.TOO_FEW_ARGUMENTS, count);

                q = new int[3];
                q[0] = doArgVar(index + 1, count, false);
                q[1] = doArgVar(index + 2, count, false);
                q[2] = doArgLbl(index + 3, count);
                break;

            case "JPNE":
                if(splitted.length < index + 3)
                    throw new SymbolException(SymbolException.TOO_FEW_ARGUMENTS, count);

                q = new int[3];
                q[0] = doArgVar(index + 1, count, false);
                q[1] = doArgVar(index + 2, count, false);
                q[2] = doArgLbl(index + 3, count);
                break;
            case "JPLT":
                if(splitted.length < index + 3)
                    throw new SymbolException(SymbolException.TOO_FEW_ARGUMENTS, count);

                q = new int[3];
                q[0] = doArgVar(index + 1, count, false);
                q[1] = doArgVar(index + 2, count, false);
                q[2] = doArgLbl(index + 3, count);
                break;

            case "JPGT":
                if(splitted.length < index + 3)
                    throw new SymbolException(SymbolException.TOO_FEW_ARGUMENTS, count);

                q = new int[3];
                q[0] = doArgVar(index + 1, count, false);
                q[1] = doArgVar(index + 2, count, false);
                q[2] = doArgLbl(index + 3, count);
                break;

            case "LDW":
                if(splitted.length < index + 2)
                    throw new SymbolException(SymbolException.TOO_FEW_ARGUMENTS, count);

                q = new int[2];
                q[0] = doArgVar(index + 1, count, true);
                q[1] = doArgVar(index + 2, count, true);
                break;

            case "LDB":
                if(splitted.length < index + 2)
                    throw new SymbolException(SymbolException.TOO_FEW_ARGUMENTS, count);

                q = new int[2];
                q[0] = doArgVar(index + 1, count, true);
                q[1] = doArgVar(index + 2, count, true);
                break;

            case "STW":
                if(splitted.length < index + 2)
                    throw new SymbolException(SymbolException.TOO_FEW_ARGUMENTS, count);

                q = new int[2];
                q[0] = doArgVar(index + 1, count, false);
                q[1] = doArgVar(index + 2, count, true);
                break;

            case "STB":
                if(splitted.length < index + 2)
                    throw new SymbolException(SymbolException.TOO_FEW_ARGUMENTS, count);

                q = new int[2];
                q[0] = doArgVar(index + 1, count, false);
                q[1] = doArgVar(index + 2, count, true);
                break;

            case "PTLN":
                q = null;
                break;

            case "PTINT":
                if(splitted.length < index + 1)
                    throw new SymbolException(SymbolException.TOO_FEW_ARGUMENTS, count);

                q = new int[1];
                q[0] = doArgVar(index + 1, count, false);
                break;

            case "PTCHR":
                if(splitted.length < index + 1)
                    throw new SymbolException(SymbolException.TOO_FEW_ARGUMENTS, count);

                q = new int[1];
                q[0] = doArgVar(index + 1, count, false);
                break;

            case "RDINT":
                if(splitted.length < index + 1)
                    throw new SymbolException(SymbolException.TOO_FEW_ARGUMENTS, count);

                q = new int[1];
                q[0] = doArgVar(index + 1, count, true);
                break;

            case "RDCHR":
                if(splitted.length < index + 1)
                    throw new SymbolException(SymbolException.TOO_FEW_ARGUMENTS, count);

                q = new int[1];
                q[0] = doArgVar(index + 1, count, true);
                break;

            default:
                throw new SymbolException(SymbolException.NO_SUCH_INSTRUCTION, count);
        }

        return q;
    }

    private int doArgVar(int index, int count, boolean checkZero)
        throws SymbolException
    {
        if(splitted[index].startsWith("#"))
            throw new SymbolException(SymbolException.TOO_FEW_ARGUMENTS, count);

        if(!isLowerCase(splitted[index]))
            throw new SymbolException(SymbolException.INVALID_CHARACTERS, count);

        if(checkZero && splitted[index].equals("zero"))
            throw new SymbolException(SymbolException.CHANGE_ZERO, count);

        variables.setValue(splitted[index]);

        return variables.getNumber(splitted[index]);
    }

    private int doArgImm(int index, int count)
        throws LanguageException
    {
        int ret = 0;

        if(splitted[index].startsWith("#"))
            throw new SymbolException(SymbolException.TOO_FEW_ARGUMENTS, count);

        if(splitted[index].startsWith("0x"))
            try
            {
                ret = Integer.parseInt(splitted[index].substring(2, splitted[index].length()), 16);
            }
            catch(NumberFormatException e)
            {
                throw new ArithmeticException(ArithmeticException.INVALID_FORMAT, count);
            }
        else
            try
            {
                ret = Integer.parseInt(splitted[index]);
            }
            catch(NumberFormatException e)
            {
                throw new ArithmeticException(ArithmeticException.INVALID_FORMAT, count);
            }

        return ret;
    }

    private int doArgLbl(int index, int count)
        throws LanguageException
    {
        if(splitted[index].startsWith("#"))
            throw new SymbolException(SymbolException.TOO_FEW_ARGUMENTS, count);

        if(!isLowerCase(splitted[index]))
            throw new LabelException(LabelException.INVALID_CHARACTERS, count);

        if(labels.indexOf(splitted[index]) < 0)
            labels.add(splitted[index]);

        return labels.indexOf(splitted[index]);
    }

    private boolean isLowerCase(String s)
    {
        for(int i = 0; i < s.length(); ++i)
            if(s.charAt(i) < 'a' || s.charAt(i) > 'z')
                return false;

        return true;
    }
}
