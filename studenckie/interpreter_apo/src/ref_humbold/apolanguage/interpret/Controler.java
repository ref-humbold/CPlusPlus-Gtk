package ref_humbold.apolanguage.interpret;

import java.nio.file.Path;

/**
Klasa kontrolujaca przebieg pracy interpretera.
Odpowiada za rozpoczecie parsowania oraz poprawne wykonanie interpretacji.
*/
public class Controler
{
	private Parser parser;
	private VariableMap variableMap;
	private Memory memory;
	private IOConnection ioConnection;
	private InstructionList instructionList;
 
 	/**
 	Rozpoczyna prace interpretera i inicjalizuje jego skladniki.
 	@param memorySize rozmiar pamieci do alokacji
 	@param path sciezka dostepu do pliku programu
 	*/
 	public Controle(int memorySize, Path path)
	{
		parser = new Parser(path);
		variableMap = new VariableMap();
		memory = new Memory(memorySize);
		ioConnection = IOConnection.getInstance();
		instructionList = null;
		
		variableMap.set("zero", 0);
	}
	
	/**
	Dokonuje interpretacji programu.
	Na poczatku uruchamia parser ({@link Parser}) tworzacy liste instrukcji.
	Nastepnie kolejno odczytuje instrukcje z listy, pobiera zmienne, wykonuje operacje i zapisuje nowe wartosci do zmiennych.
	W razie potrzeby wywoluje dodatkowe skladniki interpretera.
	@see Memory
	@see IOConnection
	*/
	public void run()
	{
		ioConnection.printMessage("parsing>> ");
		
		try
		{
			instructionList = parser.parse(variableMap);
			ioConnection.printMessageLine("done");
		}
		catch (Exception e)
		{
			ioConnection.printMessageLine("ERROR");
			ioConnection.printException(e);
			return;
		}
		
		Iterator <Instruction> iterator = instructionList.iterator();
		
		while(iterator.hasNext())
		{
			Instruction instruction = iterator.next();
			
			String name = instruction.getName();
			int lineNumber = instruction.getLineNumber();
			int arg0, arg1, arg2;
			
			switch(name)
			{
				case "ADD":
					arg1 = variableMap.getValue( instruction.getArg(1) );
					arg2 = variableMap.getValue( instruction.getArg(2) );
					variableMap.setValue(instruction.getArg(0), arg1+arg2);
					break;

				case "ADDI":
					arg1 = variableMap.getValue( instruction.getArg(1) );
					arg2 = instruction.getArg(2);
					variableMap.setValue(instruction.getArg(0), arg1+arg2);
					break;

				case "SUB":
					arg1 = variableMap.getValue( instruction.getArg(1) );
					arg2 = variableMap.getValue( instruction.getArg(2) );
					variableMap.setValue(instruction.getArg(0), arg1-arg2);
					break;

				case "SUBI":
					arg1 = variableMap.getValue( instruction.getArg(1) );
					arg2 = instruction.getArg(2);
					variableMap.setValue(instruction.getArg(0), arg1-arg2);
					break;

				case "MUL":
					arg1 = variableMap.getValue( instruction.getArg(1) );
					arg2 = variableMap.getValue( instruction.getArg(2) );
					variableMap.setValue(instruction.getArg(0), arg1*arg2);
					break;

				case "MULI":
					arg1 = variableMap.getValue( instruction.getArg(1) );
					arg2 = instruction.getArg(2);
					variableMap.setValue(instruction.getArg(0), arg1*arg2);
					break;

				case "DIV":
					arg1 = variableMap.getValue( instruction.getArg(1) );
					arg2 = variableMap.getValue( instruction.getArg(2) );
					
					if(arg2 == 0)
						Errors.throwArithmeticError(0, lineNumber);
					
					variableMap.setValue(instruction.getArg(0), arg1/arg2);
					break;

				case "DIVI":
					arg1 = variableMap.getValue( instruction.getArg(1) );
					arg2 = instruction.getArg(2);
						
					if(arg2 == 0)
						Errors.throwArithmeticError(0, lineNumber);
					
					variableMap.setValue(instruction.getArg(0), arg1/arg2);
					break;

				case "SHLT":
					arg1 = variableMap.getValue( instruction.getArg(1) );
					arg2 = instruction.getArg(2);
					variableMap.setValue(instruction.getArg(0), arg1<<arg2);
					break;

				case "SHRT":
					arg1 = variableMap.getValue( instruction.getArg(1) );
					arg2 = instruction.getArg(2);
					variableMap.setValue(instruction.getArg(0), arg1>>>arg2);
					break;

				case "SHRS":
					arg1 = variableMap.getValue( instruction.getArg(1) );
					arg2 = instruction.getArg(2);
					variableMap.setValue(instruction.getArg(0), arg1>>arg2);
					break;

				case "AND":
					arg1 = variableMap.getValue( instruction.getArg(1) );
					arg2 = variableMap.getValue( instruction.getArg(2) );
					variableMap.setValue(instruction.getArg(0), arg1&arg2);
					break;

				case "ANDI":
					arg1 = variableMap.getValue( instruction.getArg(1) );
					arg2 = instruction.getArg(2);
					variableMap.setValue(instruction.getArg(0), arg1&arg2);
					break;

				case "OR":
					arg1 = variableMap.getValue( instruction.getArg(1) );
					arg2 = variableMap.getValue( instruction.getArg(2) );
					variableMap.setValue(instruction.getArg(0), arg1|arg2);
					break;

				case "ORI":
					arg1 = variableMap.getValue( instruction.getArg(1) );
					arg2 = instruction.getArg(2);
					variableMap.setValue(instruction.getArg(0), arg1|arg2);
					break;

				case "XOR":
					arg1 = variableMap.getValue( instruction.getArg(1) );
					arg2 = variableMap.getValue( instruction.getArg(2) );
					variableMap.setValue(instruction.getArg(0), arg1^arg2);
					break;

				case "XORI":
					arg1 = variableMap.getValue( instruction.getArg(1) );
					arg2 = instruction.getArg(2);
					variableMap.setValue(instruction.getArg(0), arg1^arg2);
					break;

				case "NAND":
					arg1 = variableMap.getValue( instruction.getArg(1) );
					arg2 = variableMap.getValue( instruction.getArg(2) );
					variableMap.setValue( instruction.getArg(0), ~(arg1&arg2) );
					break;

				case "NOR":
					arg1 = variableMap.getValue( instruction.getArg(1) );
					arg2 = variableMap.getValue( instruction.getArg(2) );
					variableMap.setValue( instruction.getArg(0), ~(arg1|arg2) );
					break;

				case "LDW":
					arg1 = variableMap.getValue( instruction.getArg(1) );
					variableMap.setValue( instruction.getArg(0), memory.loadWord(arg1, lineNumber) );
					break;

				case "LDB":
					arg1 = variableMap.getValue( instruction.getArg(1) );
					variableMap.setValue( instruction.getArg(0), memory.loadByte(arg1, lineNumber) );
					break;

				case "STW":
					arg0 = variableMap.getValue( instruction.getArg(0) );
					arg1 = variableMap.getValue( instruction.getArg(1) );
					memory.storeWord(arg1, arg0, lineNumber);
					break;

				case "STB":
					arg0 = variableMap.getValue( instruction.getArg(0) );
					arg1 = variableMap.getValue( instruction.getArg(1) );
					memory.storeByte(arg1, arg0, lineNumber);
					break;

				case "PTLN":
					ioConnection.printLine();
					break;

				case "PTINT":
					arg0 = variableMap.getValue( instruction.getArg(0) );
					ioConnection.printInt(arg0);
					break;

				case "PTCHR":
					arg0 = variableMap.getValue( instruction.getArg(0) );
					ioConnection.printChar(arg0);
					break;

				case "RDINT":
					variableMap.setValue( instruction.getArg(0), ioConnection.readInt(lineNumber) );
					break;

				case "RDCHR":
					variableMap.setValue(instruction.getArg(0), ioConnection.readChar());
					break;

				default:
					break;
			}
		}
	}
}

