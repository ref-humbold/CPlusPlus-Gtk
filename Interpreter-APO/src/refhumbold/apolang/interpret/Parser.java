package refhumbold.apolang.interpret;

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.*;
import java.util.regex.Pattern;

import refhumbold.apolang.errors.LabelException;
import refhumbold.apolang.errors.LanguageException;
import refhumbold.apolang.errors.SymbolException;
import refhumbold.apolang.instructions.Instruction;
import refhumbold.apolang.instructions.InstructionName;
import refhumbold.apolang.instructions.Instructions;
import refhumbold.apolang.instructions.NOPInstruction;

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
    private List<List<String>> numberedLines = new ArrayList<>();
    private LabelSet labelSet = new LabelSet();

    /**
     * Uruchamia parser i tworzy tymczasowe listy etykiet oraz zmiennych.
     * @param path sciezka dostepu do pliku programu
     */
    public Parser(Path path)
        throws IOException
    {
        this(Files.newBufferedReader(path, StandardCharsets.UTF_8));
    }

    public Parser(BufferedReader reader)
        throws IOException
    {
        readLines(reader);
    }

    /**
     * Wykonuje parsowanie programu. Kolejno wczytuje linie z pliku programu, analizuje ich
     * zawartosc i tworzy elementy listy instrukcji.
     * @return lista instrukcji programu
     * @see InstructionList
     * @see Instruction
     */
    public InstructionList parse(BufferedReader reader)
        throws LanguageException
    {
        InstructionList instructions = new InstructionList();

        for(List<String> line : numberedLines)
        {
            Instruction instruction = parseLine(line);

            instructions.add(instruction);
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
    public VariableSet initVariables(BufferedReader reader)
        throws LanguageException
    {
        VariableSet variables = new VariableSet();
        Set<String> labels = new HashSet<>();

        variables.setValue("zero", 0);

        for(List<String> line : numberedLines)
        {
            String label = extractLabel(line);
            int index = 2;

            if(!label.equals(""))
            {
                index = 3;
                labels.add(label + "@" + Integer.toString(getLineNumber(line)));
            }

            if(line.size() > index)
            {
                if(!isAllLowerCase(line.get(index)))
                    throw new SymbolException(SymbolException.INVALID_CHARACTERS);

                InstructionName name = Instructions.convertToName(line.get(index - 1));

                if(Instructions.isValueSet(name) && !variables.contains(line.get(index)))
                    variables.setValue(line.get(index));
            }
        }

        for(String label : labels)
        {
            String[] labelSplit = label.split("@");
            int lineNumber = Integer.parseInt(labelSplit[1]);

            if(variables.contains(labelSplit[0]))
                throw new LabelException(LabelException.SAME_VARIABLE_NAME, lineNumber);
        }

        return variables;
    }

    private int getLineNumber(List<String> line)
    {
        return Integer.parseInt(line.get(0));
    }

    private void readLines(BufferedReader reader)
        throws IOException
    {
        Integer lineNumber = 0;
        String line = reader.readLine();

        while(line != null)
        {
            ++lineNumber;
            line = line.trim().split(COMMENT_SIGN, 2)[0];

            if(!line.equals(""))
            {
                String[] splitLine = (lineNumber.toString() + " " + line).split("\\s+");

                numberedLines.add(Arrays.asList(splitLine));
            }

            line = reader.readLine();
        }
    }

    private Instruction parseLine(List<String> line)
        throws LabelException
    {
        //TODO write parser for single line
        Instruction instruction = new NOPInstruction(getLineNumber(line));
        String label = extractLabel(line);

        if(!label.equals(""))
        {
            if(labelSet.contains(label))
                throw new LabelException(LabelException.DUPLICATED, getLineNumber(line));

            labelSet.setInstruction(label, instruction);
        }

        return instruction;
    }

    private void setLinksForJumps()
    {
        //TODO write setting links for jumps
    }

    private String extractLabel(List<String> line)
    {
        return hasLabel(line) ? line.get(1).substring(0, line.get(1).length() - 1) : "";
    }

    private boolean hasLabel(List<String> line)
    {
        return line.get(1).endsWith(LABEL_END_SIGN);
    }

    private boolean isAllLowerCase(String s)
    {
        return Pattern.matches("[a-z]+", s);
    }
}
