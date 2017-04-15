package ref_humbold.apolanguage.interpret;

import java.io.*;
import ref_humbold.apolanguage.errors.LanguageError;

/**
Klasa odpowiadajaca za interakcje programu z uzytkownikiem.
Wykonuje operacje wejscia / wyjscia zadane w programie asemblerowym.
*/
class IOConnector
{
    private static BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in), 1);

    /** Wyswietla na ekranie znak konca linii. */
    void printLine()
    {
        System.out.println();
    }

    /**
    Wyswietla liczbe na standardowe wyjscie.
    @param a liczba do wyswietlenia
    */
    void printInt(int a)
    {
        System.out.print(a);
    }

    /**
    Wyswietla znak na standardowe wyjscie.
    @param a kod znaku do wyswietlenia
    */
    void printChar(int a)
    {
        System.out.print((char) a);
    }

    /**
    Wczytuje liczbe w systemie dziesietnym lub szesnastkowym ze standardowego wejecia.
    @return wczytana liczba
    */
    int readInt()
    	throws LanguageError
    {
        String stread = new String();
        System.out.print("input>> ");

        try
        {
            stread = stdin.readLine();
        }
        catch (Exception e)
        {
            throw new LanguageError("IOException while reading");
        }

        return Integer.parseInt(stread);
    }

    /**
    Wczytuje znak ze standardowego wejscia.
    @return kod wczytanego znaku
    */
    int readChar()
        	throws LanguageError
    {
        String stread = new String();
        System.out.print("input>> ");

        try
        {
            stread = stdin.readLine();
        }
        catch (Exception e)
        {
            throw new LanguageError("IOException while reading");
        }

        return (int)stread.charAt(0);
    }
}
