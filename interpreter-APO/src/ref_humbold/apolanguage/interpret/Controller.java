package ref_humbold.apolanguage.interpret;

import java.nio.file.Path;

import ref_humbold.apolanguage.errors.LanguageError;
import ref_humbold.apolanguage.instructions.Instruction;
import ref_humbold.apolanguage.instructions.InstructionFactory;

/**
 * Klasa kontrolujaca przebieg pracy interpretera. Odpowiada za rozpoczecie parsowania oraz poprawne
 * wykonanie interpretacji.
 */
public class Controller
{
    //TODO replace OldParser with Parser
    private OldParser oldParser;
    private VariableSet variables;
    private InstructionList instructions;

    /**
     * Rozpoczyna prace interpretera i inicjalizuje jego skladniki.
     * @param memorySize rozmiar pamieci do alokacji
     * @param path sciezka dostepu do pliku programu
     */
    public Controller(int memorySize, Path path)
    {
        this.oldParser = new OldParser(path);
        this.variables = new VariableSet();
        this.instructions = null;

        InstructionFactory.memory = new Memory(memorySize);
    }

    /**
     * Dokonuje parsowania programu. Uruchamia parser {@link OldParser} tworzacy liste
     * instrukcji.
     */
    public void parse()
        throws Exception
    {
        System.out.print("parsing>> ");
        instructions = oldParser.parse(variables);
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
        for(Instruction instr : instructions)
            instr.execute(variables);
    }
}

