package interpret;
import java.io.*;

/**
Klasa odpowiadajaca za interakcje programu z uzytkownikiem.
Wykonuje operacje wejscia / wyjscia zadane w programie asemblerowym.
*/
class IOPut
{
 private static BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in), 1);
	
	/** Wyswietla na ekranie znak konca linii. */
	void print_line()
	{
	 System.out.println();
	}
	
	/**
	Wyswietla liczbe na standardowe wyjscie.
	@param a liczba do wyswietlenia
	*/
	void print_int(int a)
	{
	 System.out.print(a);
	}
	
	/**
	Wyswietla znak na standardowe wyjscie.
	@param a kod znaku do wyswietlenia
	*/
	void print_char(int a)
	{
	 System.out.print((char) a);
	}
	
	/**
	Wczytuje liczbe w systemie dziesietnym lub szesnastkowym ze standardowego wejecia.
	@return wczytana liczba
	*/
	int read_int()
	{
	 String stread=new String();
	 System.out.print("input>> ");
	 
	 	try
	 	{
		 stread=stdin.readLine();
		}
		catch (Exception e)
		{
		 System.out.println("Exception while reading.");
		 System.exit(0);
		}
		
	 return Integer.parseInt(stread);
	}
	
	/**
	Wczytuje znak ze standardowego wejscia.
	@return kod wczytanego znaku
	*/
	int read_char()
	{
	 String stread=new String();
	 System.out.print("input>> ");
	 
	 	try
	 	{
		 stread=stdin.readLine();
		}
		catch (Exception e)
		{
		 System.out.println("Exception while reading.");
		 System.exit(0);
		}
		
	 return (int) stread.charAt(0);
	}
}
