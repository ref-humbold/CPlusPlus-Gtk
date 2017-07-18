package ref_humbold.apolanguage.interpret;

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.HashSet;
import java.util.Set;

import ref_humbold.apolanguage.errors.LabelError;
import ref_humbold.apolanguage.errors.LanguageError;
import ref_humbold.apolanguage.errors.SymbolError;
import ref_humbold.apolanguage.instructions.Instruction;
import ref_humbold.apolanguage.instructions.InstructionName;
import ref_humbold.apolanguage.instructions.NOPInstruction;

/**
 * Klasa wykonujaca parsowanie programu. Wczytuje kolejne linie programu, przetwarza je i tworzy
 * liste instrukcji przechowywana w {@link InstructionList}. Sprawdza poprawnosc skladniowa programu
 * oraz poprawnosc zapisu nazw operacji, zmiennych i etykiet. Rowniez wykrywa komentarze w
 * programie.
 */
public class Parser
{
    private static final String COMMENT_SIGN = "#";
    private static final String LABEL_END_SIGN = ":";
    private Path filepath;
    private LabelSet labelSet;

    /**
     * Uruchamia parser i tworzy tymczasowe listy etykiet oraz zmiennych.
     * @param path sciezka dostepu do pliku programu
     */
    public Parser(Path path)
    {
        this.filepath = path;
        this.labelSet = new LabelSet();
    }

    /**
     * Wykonuje parsowanie programu. Kolejno wczytuje linie z pliku programu, analizuje ich
     * zawartosc i tworzy elementy listy instrukcji.
     * @return lista instrukcji programu
     * @see InstructionList
     * @see Instruction
     */
    public InstructionList parse()
        throws IOException, LanguageError
    {
        return parse(Files.newBufferedReader(filepath, StandardCharsets.UTF_8));
    }

    InstructionList parse(BufferedReader reader)
        throws IOException, LanguageError
    {
        InstructionList instructions = new InstructionList();
        String line = reader.readLine();
        int lineNumber = 0;

        while(line != null)
        {
            ++lineNumber;
            line = removeComment(line.trim());

            if(line.equals(""))
            {
                line = reader.readLine();
                continue;
            }

            String[] splittedLine = split(line);

            Instruction instruction = parseLine(splittedLine, lineNumber);

            instructions.add(instruction);
            line = reader.readLine();
        }

        setLinksForJumps();

        return instructions;
    }

    /**
     * Wykonuje inicjowanie zmiennych w programie. Kolejno wczytuje linie z pliku programu,
     * analizuje ich zawartosc i rezerwuje miejsce na zmienne.
     * @return zbiór zmiennych programu
     * @see VariableSet
     */
    public VariableSet initVariables()
        throws IOException, LanguageError
    {
        return initVariables(Files.newBufferedReader(filepath, StandardCharsets.UTF_8));
    }

    VariableSet initVariables(BufferedReader reader)
        throws IOException, LanguageError
    {
        VariableSet variables = new VariableSet();
        Set<String> labels = new HashSet<>();
        String line = reader.readLine();
        int lineNumber = 0;

        variables.setValue("zero", 0);

        while(line != null)
        {
            ++lineNumber;
            line = removeComment(line.trim());

            if(line.equals(""))
            {
                line = reader.readLine();
                continue;
            }

            String[] splittedLine = split(line);
            String label = exractLabel(splittedLine);
            int index = 1;

            if(!label.equals(""))
            {
                index = 2;
                labels.add(label + "@" + Integer.toString(lineNumber));
            }

            if(splittedLine.length > index)
            {
                if(!isAllLowerCase(splittedLine[index]))
                    throw new SymbolError(SymbolError.INVALID_CHARACTERS);

                InstructionName name = Instruction.convertToName(splittedLine[index - 1]);

                if(isValueSet(name) && !variables.contains(splittedLine[index]))
                    variables.setValue(splittedLine[index]);
            }

            line = reader.readLine();
        }

        for(String label : labels)
        {
            String[] labelSplitted = label.split("@");

            lineNumber = Integer.parseInt(labelSplitted[1]);

            if(variables.contains(labelSplitted[0]))
                throw new LabelError(LabelError.SAME_VARIABLE_NAME, lineNumber);
        }

        return variables;
    }

    private Instruction parseLine(String[] splittedLine, int lineNumber)
        throws LabelError
    {
        //TODO write parser for single line
        Instruction instruction = new NOPInstruction(lineNumber);
        String label = exractLabel(splittedLine);

        if(!label.equals(""))
        {
            if(labelSet.contains(label))
                throw new LabelError(LabelError.DUPLICATED, lineNumber);

            labelSet.setInstruction(label, instruction);
        }

        return instruction;
    }

    private void setLinksForJumps()
        throws LabelError
    {
        //TODO write setting links for jumps
    }

    private String removeComment(String line)
    {
        return line.split(COMMENT_SIGN, 2)[0];
    }

    private String[] split(String line)
    {
        return line.split("\\s+");
    }

    private String exractLabel(String[] splittedLine)
    {
        return hasLabel(splittedLine) ? splittedLine[0].substring(0, splittedLine[0].length() - 1)
                                      : "";
    }

    private boolean hasLabel(String[] splittedLine)
    {
        return splittedLine[0].endsWith(LABEL_END_SIGN);
    }

    private boolean isAllLowerCase(String s)
    {
        for(int i = 0; i < s.length(); ++i)
            if(s.charAt(i) < 'a' || s.charAt(i) > 'z')
                return false;

        return true;
    }

    private boolean isValueSet(InstructionName name)
        throws SymbolError
    {
        switch(name)
        {
            case ADD:
            case ADDI:
            case SUB:
            case SUBI:
            case MUL:
            case MULI:
            case DIV:
            case DIVI:
            case SHLT:
            case SHRT:
            case SHRS:
            case AND:
            case ANDI:
            case OR:
            case ORI:
            case XOR:
            case XORI:
            case NAND:
            case NOR:
            case RDINT:
            case RDCHR:
            case LDW:
            case LDB:
                return true;

            case JUMP:
            case JPEQ:
            case JPLT:
            case JPGT:
            case STW:
            case STB:
            case PTLN:
            case PTINT:
            case PTCHR:
            case NOP:
                return false;
        }

        throw new SymbolError(SymbolError.NO_SUCH_INSTRUCTION);
    }

    private int getArgsNumber(InstructionName name)
        throws SymbolError
    {
        switch(name)
        {
            case PTLN:
            case NOP:
                return 0;

            case LDW:
            case LDB:
            case PTINT:
            case PTCHR:
            case RDINT:
            case RDCHR:
                return 1;

            case STW:
            case STB:
                return 2;

            case JUMP:
            case JPEQ:
            case JPLT:
            case JPGT:
            case ADD:
            case ADDI:
            case SUB:
            case SUBI:
            case MUL:
            case MULI:
            case DIV:
            case DIVI:
            case SHLT:
            case SHRT:
            case SHRS:
            case AND:
            case ANDI:
            case OR:
            case ORI:
            case XOR:
            case XORI:
            case NAND:
            case NOR:
                return 3;
        }

        throw new SymbolError(SymbolError.NO_SUCH_INSTRUCTION);
    }
}
