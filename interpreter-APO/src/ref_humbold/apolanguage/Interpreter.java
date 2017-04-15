package ref_humbold.apolanguage;

import java.nio.file.*;

import ref_humbold.apolanguage.errors.*;
import ref_humbold.apolanguage.interpret.*;

/**
Glowna klasa, ktora pozwala na uruchomienie interpretera przez uzytkownika.
Odpowiada ona za pobranie programu do wykonania oraz rozpoczecie dzialania interpretera.

@author Rafal Kaleta
@version 1.0
*/
public class Interpreter
{
    /**
    Pobiera plik i uruchamia jego interpretacje w {@link Controler}.
    @param args pobiera parametry wejsciowe interpretera: nazwe programu z rozszerzeniem .apo oraz (opcjonalnie) rozmiar pamieci do alokacji
    */
    public static void main (String args[]) throws Exception
    {
        int memLen = 1;
        String adr = args[0];

        if(args.length>1)
        {
            try
            {
                memLen = Integer.parseInt(args[1]);
            }
            catch(Exception e)
            {
                System.err.println("Memory not allocated. Execution stopped.");
                return;
            }
        }

        if(!adr.endsWith(".apo"))
        {
            System.err.println("Wrong filename extension. Execution stopped.");
            return;
        }

        Path p = Paths.get(adr);
        Controler ct = new Controler(memLen, p);

        try
        {
            ct.parse();
        }
        catch(LanguageError e)
        {
        	e.display();
            return;
        }
        catch(Exception e)
        {
            System.err.println("Exception while parsing: "+e.getMessage()+". Execution stopped.");
            return;
        }

        try
        {
            ct.make();
        }
        catch(LanguageError e)
        {
        	e.display();
        }
        catch(Exception e)
        {
            System.err.println("Exception while interpreting: "+e.getMessage()+". Execution stopped.");
        }
    }
}
