package interpret;
import java.nio.file.*;
import java.nio.charset.*;
import java.io.*;
import java.util.*;

/**
Klasa kontrolujaca przebieg pracy interpretera.
Odpowiada za rozpoczecie parsowania oraz poprawne wykonanie interpretacji.
*/
public class Controle
{
 private interpret.Parser prs;
 private interpret.Variables vrs;
 private interpret.Memory mry;
 private interpret.IOPut iop;
 private interpret.Instructions instr;
 
 	/**
 	Rozpoczyna pracę interpretera i inicjalizuje jego skladniki.
 	@param mem_len rozmiar pamieci do alokacji
 	@param p sciezka dostepu do pliku programu
 	*/
 	public Controle(int mem_len, Path p)
	{
	 prs=new interpret.Parser(p);
	 vrs=new interpret.Variables();
	 mry=new interpret.Memory(mem_len);
	 iop=new interpret.IOPut();
	 instr=null;
	}
	
	/**
	Dokonuje interpretacji programu.
	Na poczatku uruchamia parser ({@link interpret.Parser}) tworzacy liste instrukcji.
	Nastepnie kolejno odczytuje instrukcje z listy, pobiera zmienne, wykonuje operacje i zapisuje nowe wartosci do zmiennych.
	W razie potrzeby wywoluje dodatkowe skladniki interpretera.
	@see interpret.Memory
	@see interpret.IOPut
	*/
	public void make() throws Exception
	{
		System.out.print("parsing>> ");
	 
	 	try
	 	{
		 instr=prs.parse(vrs);
		}
		catch (Exception e)
		{
		 System.out.println("java.Exception while parsing. Execution stopped.");
	 	 return;
		}
	
	 System.out.println("done");
	 instr.start_it();
	 vrs.set_value(0, 0);
	 
		while(instr.it!=null)
		{
		 String cur_instr=instr.it.name;
		 int pc=instr.it.counter;
		 int arg0, arg1, arg2;
		 
			switch(cur_instr)
			{
			 case "ADD":
			 	arg1=vrs.get_value(instr.it.arg[1]);
			 	arg2=vrs.get_value(instr.it.arg[2]);
			 	vrs.set_value(instr.it.arg[0], arg1+arg2);
			 	instr.next_it(false);
			 	break;
			 case "ADDI":
			 	arg1=vrs.get_value(instr.it.arg[1]);
			 	arg2=instr.it.arg[2];
			 	vrs.set_value(instr.it.arg[0], arg1+arg2);
			 	instr.next_it(false);
			 	break;
			 case "SUB":
			 	arg1=vrs.get_value(instr.it.arg[1]);
			 	arg2=vrs.get_value(instr.it.arg[2]);
			 	vrs.set_value(instr.it.arg[0], arg1-arg2);
			 	instr.next_it(false);
			 	break;
			 case "SUBI":
			 	arg1=vrs.get_value(instr.it.arg[1]);
			 	arg2=instr.it.arg[2];
			 	vrs.set_value(instr.it.arg[0], arg1-arg2);
			 	instr.next_it(false);
			 	break;
			 case "MUL":
			 	arg1=vrs.get_value(instr.it.arg[1]);
			 	arg2=vrs.get_value(instr.it.arg[2]);
			 	vrs.set_value(instr.it.arg[0], arg1*arg2);
			 	instr.next_it(false);
			 	break;
			 case "MULI":
			 	arg1=vrs.get_value(instr.it.arg[1]);
			 	arg2=instr.it.arg[2];
			 	vrs.set_value(instr.it.arg[0], arg1*arg2);
			 	instr.next_it(false);
			 	break;
			 case "DIV":
			 	arg1=vrs.get_value(instr.it.arg[1]);
			 	arg2=vrs.get_value(instr.it.arg[2]);
			 	
			 		if(arg2==0)
			 		{
			 		 interpret.Errors.arit_err(0, pc);
			 		}
			 	
			 	vrs.set_value(instr.it.arg[0], arg1/arg2);
			 	instr.next_it(false);
			 	break;
			 case "DIVI":
			 	arg1=vrs.get_value(instr.it.arg[1]);
			 	arg2=instr.it.arg[2];
			 		
			 		if(arg2==0)
			 		{
			 		 interpret.Errors.arit_err(0, pc);
			 		}
			 	
			 	vrs.set_value(instr.it.arg[0], arg1/arg2);
			 	instr.next_it(false);
			 	break;
			 case "SHLT":
			 	arg1=vrs.get_value(instr.it.arg[1]);
			 	arg2=instr.it.arg[2];
			 	vrs.set_value(instr.it.arg[0], (arg1<<arg2));
			 	instr.next_it(false);
			 	break;
			 case "SHRT":
			 	arg1=vrs.get_value(instr.it.arg[1]);
			 	arg2=instr.it.arg[2];
			 	vrs.set_value(instr.it.arg[0], (arg1>>>arg2));
			 	instr.next_it(false);
			 	break;
			 case "SHRS":
			 	arg1=vrs.get_value(instr.it.arg[1]);
			 	arg2=instr.it.arg[2];
			 	vrs.set_value(instr.it.arg[0], (arg1>>arg2));
			 	instr.next_it(false);
			 	break;
			 case "AND":
			 	arg1=vrs.get_value(instr.it.arg[1]);
			 	arg2=vrs.get_value(instr.it.arg[2]);
			 	vrs.set_value(instr.it.arg[0], arg1&arg2);
			 	instr.next_it(false);
			 	break;
			 case "ANDI":
			 	arg1=vrs.get_value(instr.it.arg[1]);
			 	arg2=instr.it.arg[2];
			 	vrs.set_value(instr.it.arg[0], arg1&arg2);
			 	instr.next_it(false);
			 	break;
			 case "OR":
			 	arg1=vrs.get_value(instr.it.arg[1]);
			 	arg2=vrs.get_value(instr.it.arg[2]);
			 	vrs.set_value(instr.it.arg[0], arg1|arg2);
			 	instr.next_it(false);
			 	break;
			 case "ORI":
			 	arg1=vrs.get_value(instr.it.arg[1]);
			 	arg2=instr.it.arg[2];
			 	vrs.set_value(instr.it.arg[0], arg1|arg2);
			 	instr.next_it(false);
			 	break;
			 case "XOR":
			 	arg1=vrs.get_value(instr.it.arg[1]);
			 	arg2=vrs.get_value(instr.it.arg[2]);
			 	vrs.set_value(instr.it.arg[0], arg1^arg2);
			 	instr.next_it(false);
			 	break;
			 case "XORI":
			 	arg1=vrs.get_value(instr.it.arg[1]);
			 	arg2=instr.it.arg[2];
			 	vrs.set_value(instr.it.arg[0], arg1^arg2);
			 	instr.next_it(false);
			 	break;
			 case "NAND":
			 	arg1=vrs.get_value(instr.it.arg[1]);
			 	arg2=vrs.get_value(instr.it.arg[2]);
			 	vrs.set_value(instr.it.arg[0], ~(arg1&arg2));
			 	instr.next_it(false);
			 	break;
			 case "NOR":
			 	arg1=vrs.get_value(instr.it.arg[1]);
			 	arg2=vrs.get_value(instr.it.arg[2]);
			 	vrs.set_value(instr.it.arg[0], ~(arg1|arg2));
			 	instr.next_it(false);
			 	break;
			 case "JUMP":
			 	instr.next_it(true);
			 	break;
			 case "JPEQ":
			 	arg0=vrs.get_value(instr.it.arg[0]);
			 	arg1=vrs.get_value(instr.it.arg[1]);
			 	instr.next_it(arg0==arg1);
			 	break;
			 case "JPNE":
			 	arg0=vrs.get_value(instr.it.arg[0]);
			 	arg1=vrs.get_value(instr.it.arg[1]);
			 	instr.next_it(arg0!=arg1);
			 	break;
			 case "JPLT":
			 	arg0=vrs.get_value(instr.it.arg[0]);
			 	arg1=vrs.get_value(instr.it.arg[1]);
			 	instr.next_it(arg0<arg1);
			 	break;
			 case "JPGT":
			 	arg0=vrs.get_value(instr.it.arg[0]);
			 	arg1=vrs.get_value(instr.it.arg[1]);
			 	instr.next_it(arg0>arg1);
			 	break;
			 case "LDW":
			 	arg1=vrs.get_value(instr.it.arg[1]);
			 	vrs.set_value(instr.it.arg[0], mry.load_word(arg1, pc));
			 	instr.next_it(false);
			 	break;
			 case "LDB":
			 	arg1=vrs.get_value(instr.it.arg[1]);
			 	vrs.set_value(instr.it.arg[0], mry.load_byte(arg1, pc));
			 	instr.next_it(false);
			 	break;
			 case "STW":
			 	arg0=vrs.get_value(instr.it.arg[0]);
			 	arg1=vrs.get_value(instr.it.arg[1]);
			 	mry.store_word(arg1, arg0, pc);
			 	instr.next_it(false);
			 	break;
			 case "STB":
			 	arg0=vrs.get_value(instr.it.arg[0]);
			 	arg1=vrs.get_value(instr.it.arg[1]);
			 	mry.store_byte(arg1, arg0, pc);
			 	instr.next_it(false);
			 	break;
			 case "PTLN":
			 	iop.print_line();
			 	instr.next_it(false);
			 	break;
			 case "PTINT":
			 	arg0=vrs.get_value(instr.it.arg[0]);
			 	iop.print_int(arg0);
			 	instr.next_it(false);
			 	break;
			 case "PTCHR":
			 	arg0=vrs.get_value(instr.it.arg[0]);
			 	iop.print_char(arg0);
			 	instr.next_it(false);
			 	break;
			 case "RDINT":
			 	vrs.set_value(instr.it.arg[0], iop.read_int());
			 	instr.next_it(false);
			 	break;
			 case "RDCHR":
			 	vrs.set_value(instr.it.arg[0], iop.read_char());
			 	instr.next_it(false);
			 	break;
			 case "NOP":
			 	instr.next_it(false);
			 	break;
			}
		}
	}
}
