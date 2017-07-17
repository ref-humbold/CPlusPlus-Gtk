package ref_humbold.apolanguage.interpret;

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;

import ref_humbold.apolanguage.errors.LanguageError;
import ref_humbold.apolanguage.instructions.Instruction;
import ref_humbold.apolanguage.instructions.InstructionName;

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

    /**
     * Uruchamia parser i tworzy tymczasowe listy etykiet oraz zmiennych.
     * @param path sciezka dostepu do pliku programu
     */
    public Parser(Path path)
    {
        filepath = path;
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
        InstructionList instructions = new InstructionList();
        BufferedReader reader = Files.newBufferedReader(filepath, StandardCharsets.UTF_8);
        String line = reader.readLine();
        int lineNumber = 1;

        while(line != null)
        {
            String[] splittedLine = split(removeComment(line));

            if(splittedLine.length == 0)
                continue;

            Instruction instruction = hasLabel(splittedLine) ? parseLineWithLabel(splittedLine)
                                                             : parseLineWithoutLabel(splittedLine);

            instructions.add(instruction);
        }

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
        VariableSet variables = new VariableSet();
        BufferedReader reader = Files.newBufferedReader(filepath, StandardCharsets.UTF_8);
        String line = reader.readLine();

        variables.setValue("zero", 0);

        while(line != null)
        {
            String[] splittedLine = split(removeComment(line));
            int index = hasLabel(splittedLine) ? 2 : 1;

            if(splittedLine.length > index && isAllLowerCase(splittedLine[index]))
            {
                InstructionName name = Instruction.convertToName(splittedLine[index - 1]);

                if(Instruction.setsValue(name) && !variables.contains(splittedLine[index]))
                    variables.setValue(splittedLine[index]);
            }

            line = reader.readLine();
        }

        return variables;
    }

    private Instruction parseLineWithoutLabel(String[] splittedLine)
    {
        //TODO write parser for single line without label
        return null;
    }

    private Instruction parseLineWithLabel(String[] splittedLine)
    {
        //TODO write parser for single line with label
        return null;
    }

    private String removeComment(String line)
    {
        return line.split(COMMENT_SIGN, 2)[0];
    }

    private String[] split(String line)
    {
        return line.split("\\s+");
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
}
