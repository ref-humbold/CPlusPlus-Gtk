package ref_humbold.apolanguage;

import ref_humbold.apolanguage.interpret.Controler;
import java.nio.file.*;
import java.nio.charset.*;
import java.io.*;

/**
Glowna klasa, ktora pozwala na uruchomienie interpretera przez uzytkownika.
Odpowiada ona za pobranie programu do wykonania oraz rozpoczecie dzialania interpretera.
@author Rafal Kaleta
@version 1.0
*/
public class Interpreter
{
    /**
    Pobiera plik i uruchamia jego interpretacje w {@link interpret.Controle}.
    @param args pobiera parametry wejsciowe interpretera: nazwe programu z rozszerzeniem .apo oraz (opcjonalnie) rozmiar pamieci do alokacji
    */
    public static void main(String args[])
    {
        int mem_len = 1;
        String adr = args[0];
     
        if(args.length>1)
        { 
            try
            {
                mem_len = Integer.parseInt( args[1] );
            }
            catch (Exception e)
            {
                System.out.println("Memory not allocated. Execution stopped.");
                return;
            }
        }
     
        if( !adr.endsWith(".apo") )
        {
            System.out.println("Wrong filename extension. Execution stopped.");
            return;
        }
     
        Path p = Paths.get(adr);
        Controler controler = new Controler(mem_len, p);
     
        try
        {
            controler.run();
        }
        catch (Exception e)
        {
            System.out.println("java.Exception while interpreting. Execution stopped.");
            return;
        }
    }
}

