package ref_humbold.apolanguage;

import java.nio.file.Path;
import java.nio.file.Paths;

import ref_humbold.apolanguage.interpret.Controller;

/**
 * Glowna klasa, ktora pozwala na uruchomienie interpretera przez uzytkownika. Odpowiada ona za
 * pobranie programu do wykonania oraz rozpoczecie dzialania interpretera.
 * @author Rafal Kaleta
 * @version 1.1
 */
public class Interpreter
{
    /**
     * Pobiera plik i uruchamia jego interpretacje w {@link Controller}.
     * @param args pobiera parametry wejsciowe interpretera: nazwe programu z rozszerzeniem .apo
     * oraz (opcjonalnie) rozmiar pamieci do alokacji
     */
    public static void main(String args[])
    {
        int memorySize = 1;
        String address = args[0];

        if(args.length > 1)
        {
            try
            {
                memorySize = Integer.parseInt(args[1]);
            }
            catch(Exception e)
            {
                System.err.println("Memory could not be allocated.\n\tExecution stopped.");
                return;
            }
        }

        if(!address.endsWith(".apo"))
        {
            System.err.println("Wrong filename extension.\n\tExecution stopped.");
            return;
        }

        Path path = Paths.get(address);
        Controller controller = new Controller(memorySize, path);

        try
        {
            controller.parse();
        }
        catch(Exception e)
        {
            System.err.println("\nparser error>> " + e.toString() + "\n\tExecution stopped.");
            return;
        }

        try
        {
            controller.make();
        }
        catch(Exception e)
        {
            System.err.println("\ninterpreter error>> " + e.toString() + "\n\tExecution stopped.");
        }
    }
}
