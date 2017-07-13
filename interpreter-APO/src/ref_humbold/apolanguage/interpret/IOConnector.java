package ref_humbold.apolanguage.interpret;

import java.io.BufferedReader;
import java.io.InputStreamReader;

import ref_humbold.apolanguage.errors.LanguageError;

/**
 * Klasa odpowiadajaca za interakcje programu z uzytkownikiem. Wykonuje operacje wejscia / wyjscia
 * zadane w programie asemblerowym.
 */
public class IOConnector
{
    private static BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in), 1);
    private static IOConnector instance = null;

    private IOConnector()
    {
    }

    public static IOConnector getInstance()
    {
        if(instance == null)
            instance = new IOConnector();

        return instance;
    }

    /**
     * Wyswietla na ekranie znak konca linii.
     */
    public void printLine()
    {
        System.out.println();
    }

    /**
     * Wyswietla liczbe na standardowe wyjście.
     * @param number liczba
     */
    public void printInt(int number)
    {
        System.out.print(number);
    }

    /**
     * Wyswietla znak na standardowe wyjście.
     * @param code kod znaku
     */
    public void printChar(int code)
    {
        System.out.print((char)code);
    }

    /**
     * Wczytuje liczbe w systemie dziesiętnym lub szesnastkowym ze standardowego wejścia.
     * @return wczytana liczba
     */
    public int readInt()
        throws LanguageError
    {
        String read;
        System.out.print("input>> ");

        try
        {
            read = stdin.readLine();
        }
        catch(Exception e)
        {
            throw new LanguageError("IOException while reading", e);
        }

        return Integer.parseInt(read);
    }

    /**
     * Wczytuje znak ze standardowego wejścia.
     * @return kod wczytanego znaku
     */
    public int readChar()
        throws LanguageError
    {
        String read;
        System.out.print("input>> ");

        try
        {
            read = stdin.readLine();
        }
        catch(Exception e)
        {
            throw new LanguageError("IOException while reading", e);
        }

        return read.charAt(0);
    }
}
