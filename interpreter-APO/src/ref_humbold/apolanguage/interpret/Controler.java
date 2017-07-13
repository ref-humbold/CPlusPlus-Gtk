package ref_humbold.apolanguage.interpret;

import java.nio.file.Path;

import ref_humbold.apolanguage.errors.ArithmeticError;
import ref_humbold.apolanguage.errors.LanguageError;
import ref_humbold.apolanguage.instructions.InstructionFactory;

/**
 * Klasa kontrolujaca przebieg pracy interpretera. Odpowiada za rozpoczecie parsowania oraz poprawne
 * wykonanie interpretacji.
 */
public class Controler
{
    private Parser parser;
    private VariableSet variables;
    private Memory memory;
    private IOConnector connector;
    private InstructionList instructions;

    /**
     * Rozpoczyna prace interpretera i inicjalizuje jego skladniki.
     * @param memorySize rozmiar pamieci do alokacji
     * @param path sciezka dostepu do pliku programu
     */
    public Controler(int memorySize, Path path)
    {
        this.parser = new Parser(path);
        this.variables = new VariableSet();
        this.memory = new Memory(memorySize);
        this.connector = IOConnector.getInstance();
        this.instructions = null;
        InstructionFactory.memory = this.memory;
    }

    /**
     * Dokonuje parsowania programu. Uruchamia parser ({@link Parser}) tworzący listę instrukcji.
     */
    public void parse()
        throws Exception
    {
        System.out.print("parsing>> ");
        instructions = parser.parse(variables);
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
        instructions.startIt();
        variables.setValue(0, 0);

        while(instructions.it != null)
        {
            String currentName = instructions.it.getName();
            int lineCounter = instructions.it.getLineNumber();
            int arg0, arg1, arg2;

            switch(currentName)
            {
                case "ADD":
                    arg1 = variables.getValue(instructions.it.getArg(1));
                    arg2 = variables.getValue(instructions.it.getArg(2));
                    variables.setValue(instructions.it.getArg(0), arg1 + arg2);
                    instructions.nextIt(false);
                    break;

                case "ADDI":
                    arg1 = variables.getValue(instructions.it.getArg(1));
                    arg2 = instructions.it.getArg(2);
                    variables.setValue(instructions.it.getArg(0), arg1 + arg2);
                    instructions.nextIt(false);
                    break;

                case "SUB":
                    arg1 = variables.getValue(instructions.it.getArg(1));
                    arg2 = variables.getValue(instructions.it.getArg(2));
                    variables.setValue(instructions.it.getArg(0), arg1 - arg2);
                    instructions.nextIt(false);
                    break;

                case "SUBI":
                    arg1 = variables.getValue(instructions.it.getArg(1));
                    arg2 = instructions.it.getArg(2);
                    variables.setValue(instructions.it.getArg(0), arg1 - arg2);
                    instructions.nextIt(false);
                    break;

                case "MUL":
                    arg1 = variables.getValue(instructions.it.getArg(1));
                    arg2 = variables.getValue(instructions.it.getArg(2));
                    variables.setValue(instructions.it.getArg(0), arg1 * arg2);
                    instructions.nextIt(false);
                    break;

                case "MULI":
                    arg1 = variables.getValue(instructions.it.getArg(1));
                    arg2 = instructions.it.getArg(2);
                    variables.setValue(instructions.it.getArg(0), arg1 * arg2);
                    instructions.nextIt(false);
                    break;

                case "DIV":
                    arg1 = variables.getValue(instructions.it.getArg(1));
                    arg2 = variables.getValue(instructions.it.getArg(2));

                    if(arg2 == 0)
                        throw new ArithmeticError(ArithmeticError.ZERO_DIVISION, lineCounter);

                    variables.setValue(instructions.it.getArg(0), arg1 / arg2);
                    instructions.nextIt(false);
                    break;

                case "DIVI":
                    arg1 = variables.getValue(instructions.it.getArg(1));
                    arg2 = instructions.it.getArg(2);

                    if(arg2 == 0)
                        throw new ArithmeticError(ArithmeticError.ZERO_DIVISION, lineCounter);

                    variables.setValue(instructions.it.getArg(0), arg1 / arg2);
                    instructions.nextIt(false);
                    break;

                case "SHLT":
                    arg1 = variables.getValue(instructions.it.getArg(1));
                    arg2 = instructions.it.getArg(2);
                    variables.setValue(instructions.it.getArg(0), arg1 << arg2);
                    instructions.nextIt(false);
                    break;

                case "SHRT":
                    arg1 = variables.getValue(instructions.it.getArg(1));
                    arg2 = instructions.it.getArg(2);
                    variables.setValue(instructions.it.getArg(0), arg1 >>> arg2);
                    instructions.nextIt(false);
                    break;

                case "SHRS":
                    arg1 = variables.getValue(instructions.it.getArg(1));
                    arg2 = instructions.it.getArg(2);
                    variables.setValue(instructions.it.getArg(0), arg1 >> arg2);
                    instructions.nextIt(false);
                    break;

                case "AND":
                    arg1 = variables.getValue(instructions.it.getArg(1));
                    arg2 = variables.getValue(instructions.it.getArg(2));
                    variables.setValue(instructions.it.getArg(0), arg1 & arg2);
                    instructions.nextIt(false);
                    break;

                case "ANDI":
                    arg1 = variables.getValue(instructions.it.getArg(1));
                    arg2 = instructions.it.getArg(2);
                    variables.setValue(instructions.it.getArg(0), arg1 & arg2);
                    instructions.nextIt(false);
                    break;

                case "OR":
                    arg1 = variables.getValue(instructions.it.getArg(1));
                    arg2 = variables.getValue(instructions.it.getArg(2));
                    variables.setValue(instructions.it.getArg(0), arg1 | arg2);
                    instructions.nextIt(false);
                    break;

                case "ORI":
                    arg1 = variables.getValue(instructions.it.getArg(1));
                    arg2 = instructions.it.getArg(2);
                    variables.setValue(instructions.it.getArg(0), arg1 | arg2);
                    instructions.nextIt(false);
                    break;

                case "XOR":
                    arg1 = variables.getValue(instructions.it.getArg(1));
                    arg2 = variables.getValue(instructions.it.getArg(2));
                    variables.setValue(instructions.it.getArg(0), arg1 ^ arg2);
                    instructions.nextIt(false);
                    break;

                case "XORI":
                    arg1 = variables.getValue(instructions.it.getArg(1));
                    arg2 = instructions.it.getArg(2);
                    variables.setValue(instructions.it.getArg(0), arg1 ^ arg2);
                    instructions.nextIt(false);
                    break;

                case "NAND":
                    arg1 = variables.getValue(instructions.it.getArg(1));
                    arg2 = variables.getValue(instructions.it.getArg(2));
                    variables.setValue(instructions.it.getArg(0), ~(arg1 & arg2));
                    instructions.nextIt(false);
                    break;

                case "NOR":
                    arg1 = variables.getValue(instructions.it.getArg(1));
                    arg2 = variables.getValue(instructions.it.getArg(2));
                    variables.setValue(instructions.it.getArg(0), ~(arg1 | arg2));
                    instructions.nextIt(false);
                    break;

                case "JUMP":
                    instructions.nextIt(true);
                    break;

                case "JPEQ":
                    arg0 = variables.getValue(instructions.it.getArg(0));
                    arg1 = variables.getValue(instructions.it.getArg(1));
                    instructions.nextIt(arg0 == arg1);
                    break;

                case "JPNE":
                    arg0 = variables.getValue(instructions.it.getArg(0));
                    arg1 = variables.getValue(instructions.it.getArg(1));
                    instructions.nextIt(arg0 != arg1);
                    break;

                case "JPLT":
                    arg0 = variables.getValue(instructions.it.getArg(0));
                    arg1 = variables.getValue(instructions.it.getArg(1));
                    instructions.nextIt(arg0 < arg1);
                    break;

                case "JPGT":
                    arg0 = variables.getValue(instructions.it.getArg(0));
                    arg1 = variables.getValue(instructions.it.getArg(1));
                    instructions.nextIt(arg0 > arg1);
                    break;

                case "LDW":
                    arg1 = variables.getValue(instructions.it.getArg(1));
                    variables.setValue(instructions.it.getArg(0),
                                       memory.loadWord(arg1, lineCounter));
                    instructions.nextIt(false);
                    break;

                case "LDB":
                    arg1 = variables.getValue(instructions.it.getArg(1));
                    variables.setValue(instructions.it.getArg(0),
                                       memory.loadByte(arg1, lineCounter));
                    instructions.nextIt(false);
                    break;

                case "STW":
                    arg0 = variables.getValue(instructions.it.getArg(0));
                    arg1 = variables.getValue(instructions.it.getArg(1));
                    memory.storeWord(arg1, arg0, lineCounter);
                    instructions.nextIt(false);
                    break;

                case "STB":
                    arg0 = variables.getValue(instructions.it.getArg(0));
                    arg1 = variables.getValue(instructions.it.getArg(1));
                    memory.storeByte(arg1, arg0, lineCounter);
                    instructions.nextIt(false);
                    break;

                case "PTLN":
                    connector.printLine();
                    instructions.nextIt(false);
                    break;

                case "PTINT":
                    arg0 = variables.getValue(instructions.it.getArg(0));
                    connector.printInt(arg0);
                    instructions.nextIt(false);
                    break;

                case "PTCHR":
                    arg0 = variables.getValue(instructions.it.getArg(0));
                    connector.printChar(arg0);
                    instructions.nextIt(false);
                    break;

                case "RDINT":
                    variables.setValue(instructions.it.getArg(0), connector.readInt());
                    instructions.nextIt(false);
                    break;

                case "RDCHR":
                    variables.setValue(instructions.it.getArg(0), connector.readChar());
                    instructions.nextIt(false);
                    break;

                case "NOP":
                    instructions.nextIt(false);
                    break;
            }
        }
    }
}
