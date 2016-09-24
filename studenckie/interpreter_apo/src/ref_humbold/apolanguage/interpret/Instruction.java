package ref_humbold.apolanguage.interpret;

/**
Klasa abstrakcyjna przechowujaca pojedyncza instrukcje w liscie rozkazow.
*/
abstract class Instruction
{
	/** Numer wiersza programu. */
	private int lineNumber;
 
	/** Nazwa operacji. */
	private String name;
 
	/** Argumenty operacji. */
	private int[] args;
 
	/** Nastepny element listy. */
	Element nextInstruction;
 
 	/**
 	Tworzy element odpowiadajacy jednej instrukcji w programie.
 	@param lineNumber numer wiersza
 	@param name nazwa operacji
 	@param args wektor argumentów
 	*/
	public Instruction(int lineNumber, String name, int[] args)
	{
		this.lineNumber = lineNumber;
		this.name = name;
		this.args = args;
		this.nextInstruction = null;
	}
}

