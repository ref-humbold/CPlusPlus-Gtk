package ref_humbold.apolanguage.interpret;

import java.io.BufferedReader;
import java.io.InputStreamReader;

import ref_humbold.apolanguage.errors.LanguageException;

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
     * Wyswietla liczbe na standardowe wyjscie.
     * @param number liczba
     */
    public void printInt(int number)
    {
        System.out.print(number);
    }

    /**
     * Wyswietla znak na standardowe wyjscie.
     * @param code kod znaku
     */
    public void printChar(int code)
    {
        System.out.print((char)code);
    }

    /**
     * Wczytuje liczbe w systemie dziesietnym lub szesnastkowym ze standardowego wejscia.
     * @return wczytana liczba
     */
    public int readInt()
        throws LanguageException
    {
        String read;
        System.out.print("input>> ");

        try
        {
            read = stdin.readLine();
        }
        catch(Exception e)
        {
            throw new LanguageException("IOException while reading", e);
        }

        return Integer.parseInt(read);
    }

    /**
     * Wczytuje znak ze standardowego wejscia.
     * @return kod wczytanego znaku
     */
    public int readChar()
        throws LanguageException
    {
        String read;
        System.out.print("input>> ");

        try
        {
            read = stdin.readLine();
        }
        catch(Exception e)
        {
            throw new LanguageException("IOException while reading", e);
        }

        return read.charAt(0);
    }
}
