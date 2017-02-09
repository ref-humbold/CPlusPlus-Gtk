package interpret;
import java.nio.file.*;
import java.nio.charset.*;
import java.io.*;
import java.util.*;

/**
Klasa wykonujaca parsowanie programu.
Wczytuje kolejne linie programu, przetwarza je i tworzy liste instrukcji przechowywana w {@link interpret.Instructions}.
Sprawdza poprawnosc składniowa programu oraz poprawnosc zapisu nazw operacji, zmiennych i etykiet.
Rowniez wykrywa komentarze w programie.
*/
class Parser
{
 private int vars_num;
 private Path plik;
 private ArrayList <String> etnums;
 private HashMap <String, interpret.Element> et;
 private HashMap <String, Integer> varies;
 private String[] splitted;
 
 	/**
 	Uruchamia parser i tworzy tymczasowe listy etykiet oraz zmiennych.
 	@param p sciezka dostepu do pliku programu
 	*/
 	public Parser(Path p)
 	{
 	 vars_num=1;
 	 plik=p;
 	 etnums=new ArrayList <String>();
 	 et=new HashMap <String, interpret.Element>();
 	 varies=new HashMap <String, Integer>();
 	}
 	
 	/**
 	Wykonuje parsowanie programu.
 	Kolejno wczytuje linie z pliku programu, analizuje ich zawartosc i tworzy elementy listy instrukcji.
 	@param v referencja do listy zmiennych utworzonej poczatkowo w {@link interpret.Controle}.
 	@return lista instrukcji programu
 	@see interpret.Element
 	*/
 	interpret.Instructions parse(interpret.Variables v) throws IOException
 	{
	 BufferedReader reader=Files.newBufferedReader(plik, StandardCharsets.UTF_8);
	 interpret.Instructions instr=new interpret.Instructions();
	 String line=reader.readLine();
	 interpret.Element elem;
	 String label="";
 	 int[] t;
 	 int cnt=0, g=0;
 	 boolean is_lbl;
 	 
 	 varies.put("zero", 0);
 	 	
 	 	while(line!=null)
 	 	{
 	 	 cnt++;
 	 	 g=0;
 	 	 line=line.trim();
 	 	 
 	 	 	if(line.length()==0 || line.startsWith("#"))
 	 		{
			 line=reader.readLine();
			 continue;
 	 		}
 	 		
		 splitted=line.split("\\s+");
		 is_lbl=splitted[g].endsWith(":");
		 
			if(is_lbl)
			{
			 label=do_label(splitted[g], cnt);
			 g++;
			 	
			 	if(g>=splitted.length)
			 	{
			 	 t=do_arg_none();
			 	 elem=instr.add_instr(cnt, "NOP", t, is_lbl);
				 et.put(label, elem);
			 	 line=reader.readLine();
				 continue;
			 	}
			}
		 
		 t=do_instr(g, cnt);
		 elem=instr.add_instr(cnt, splitted[g], t, is_lbl);
		 
		 	if(elem!=null)
		 	{
		 	 et.put(label, elem);
		 	}
		 	
		 line=reader.readLine();
		}
	
	 check_vl();
	 init_vars(v);	  
	 instr.start_it();
	 
	 	while(instr.it!=null)
	 	{
		 	if(instr.it instanceof ElemJump)
		 	{
		 	 int len_j=instr.it.arg.length;
		 	 
		 		if(et.containsKey(etnums.get(instr.it.arg[len_j-1])))
		 		{
		 		 instr.set_link(et.get(etnums.get(instr.it.arg[len_j-1])));
		 		}
		 		else
		 		{
		 		 interpret.Errors.lbl_err(0, instr.it.counter);
		 		}
		 	}
		
		 instr.next_it(false);
		}
		
	 return instr;
	}
	
	private void check_vl()
	{
	 Set <String> etset=et.keySet();
	 Iterator <String> s_it=etset.iterator();
	 String ret_it;
	 int ctlbl;
	 
		while(s_it.hasNext())
		{
		 ret_it=s_it.next();
		 
			if(varies.containsKey(ret_it))
			{
			 ctlbl=et.get(ret_it).counter;
			 interpret.Errors.lbl_err(2, ctlbl);
			}
		}
	 	
 	}
	
	private void init_vars(interpret.Variables v)
	{
	 Set <String> vrset=varies.keySet();
	 Iterator <String> s_it=vrset.iterator();
	 String ret_it;
	 
		while(s_it.hasNext())
		{
		 ret_it=s_it.next();
		 v.add_var();
		}
	}
 	
 	private String do_label(String lbl, int cnt)
 	{ 		
 	 String lb_name=lbl.substring(0, lbl.length()-1);
 	 
 		if(!all_lower(lbl))
 		{
 		 interpret.Errors.lbl_err(3, cnt);
 		}
 		
 		if(et.containsKey(lb_name))
 		{
 		 interpret.Errors.lbl_err(1, cnt);
 		}
 		
 	 return lb_name;
 	}
 	
 	private int[] do_instr(int indx, int cnt)
 	{
 	 String op=splitted[indx];
 	 int[] q=new int[0];
 	 
 		if(op.startsWith("#"))
 		{
 		 return do_arg_none();
 		}
 		
 		switch(op)
		{
		 case "ADD":
		 		if(splitted.length<indx+3)
		 		{
		 		 interpret.Errors.sym_err(2, cnt);
		 		}
		 		
		 	q=new int[3];
			q[0]=do_arg_var(indx+1, cnt, true);
			q[1]=do_arg_var(indx+2, cnt, false);
			q[2]=do_arg_var(indx+3, cnt, false);
		 	break;
		 case "ADDI":
		 		if(splitted.length<indx+3)
		 		{
		 		 interpret.Errors.sym_err(2, cnt);
		 		}
		 		
		 	q=new int[3];
			q[0]=do_arg_var(indx+1, cnt, true);
			q[1]=do_arg_var(indx+2, cnt, false);
			q[2]=do_arg_imm(indx+3, cnt);
		 	break;
		 case "SUB":
		 		if(splitted.length<indx+3)
		 		{
		 		 interpret.Errors.sym_err(2, cnt);
		 		}
		 		
		 	q=new int[3];
			q[0]=do_arg_var(indx+1, cnt, true);
			q[1]=do_arg_var(indx+2, cnt, false);
			q[2]=do_arg_var(indx+3, cnt, false);
		 	break;
		 case "SUBI":
		 		if(splitted.length<indx+3)
		 		{
		 		 interpret.Errors.sym_err(2, cnt);
		 		}
		 		
		 	q=new int[3];
			q[0]=do_arg_var(indx+1, cnt, true);
			q[1]=do_arg_var(indx+2, cnt, false);
			q[2]=do_arg_imm(indx+3, cnt);
		 	break;
		 case "MUL":
		 		if(splitted.length<indx+3)
		 		{
		 		 interpret.Errors.sym_err(2, cnt);
		 		}
		 		
		 	q=new int[3];
			q[0]=do_arg_var(indx+1, cnt, true);
			q[1]=do_arg_var(indx+2, cnt, false);
			q[2]=do_arg_var(indx+3, cnt, false);
		 	break;
		 case "MULI":
		 		if(splitted.length<indx+3)
		 		{
		 		 interpret.Errors.sym_err(2, cnt);
		 		}
		 		
		 	q=new int[3];
			q[0]=do_arg_var(indx+1, cnt, true);
			q[1]=do_arg_var(indx+2, cnt, false);
			q[2]=do_arg_imm(indx+3, cnt);
		 	break;
		 case "DIV":
		 		if(splitted.length<indx+3)
		 		{
		 		 interpret.Errors.sym_err(2, cnt);
		 		}
		 		
		 	q=new int[3];
			q[0]=do_arg_var(indx+1, cnt, true);
			q[1]=do_arg_var(indx+2, cnt, false);
			q[2]=do_arg_var(indx+3, cnt, false);
		 case "DIVI":
		 		if(splitted.length<indx+3)
		 		{
		 		 interpret.Errors.sym_err(2, cnt);
		 		}
		 		
		 	q=new int[3];
			q[0]=do_arg_var(indx+1, cnt, true);
			q[1]=do_arg_var(indx+2, cnt, false);
			q[2]=do_arg_imm(indx+3, cnt);
		 	break;
		 case "SHLT":
		 		if(splitted.length<indx+3)
		 		{
		 		 interpret.Errors.sym_err(2, cnt);
		 		}
		 		
		 	q=new int[3];
			q[0]=do_arg_var(indx+1, cnt, true);
			q[1]=do_arg_var(indx+2, cnt, false);
			q[2]=do_arg_imm(indx+3, cnt);
		 	break;
		 case "SHRT":
		 		if(splitted.length<indx+3)
		 		{
		 		 interpret.Errors.sym_err(2, cnt);
		 		}
		 		
		 	q=new int[3];
			q[0]=do_arg_var(indx+1, cnt, true);
			q[1]=do_arg_var(indx+2, cnt, false);
			q[2]=do_arg_imm(indx+3, cnt);
		 	break;
		 case "SHRS":
		 		if(splitted.length<indx+3)
		 		{
		 		 interpret.Errors.sym_err(2, cnt);
		 		}
		 		
		 	q=new int[3];
			q[0]=do_arg_var(indx+1, cnt, true);
			q[1]=do_arg_var(indx+2, cnt, false);
			q[2]=do_arg_imm(indx+3, cnt);
		 	break;			 
		 case "AND":
		 		if(splitted.length<indx+3)
		 		{
		 		 interpret.Errors.sym_err(2, cnt);
		 		}
		 		
		 	q=new int[3];
			q[0]=do_arg_var(indx+1, cnt, true);
			q[1]=do_arg_var(indx+2, cnt, false);
			q[2]=do_arg_var(indx+3, cnt, false);
		 	break;
		 case "ANDI":
		 		if(splitted.length<indx+3)
		 		{
		 		 interpret.Errors.sym_err(2, cnt);
		 		}
		 		
		 	q=new int[3];
			q[0]=do_arg_var(indx+1, cnt, true);
			q[1]=do_arg_var(indx+2, cnt, false);
			q[2]=do_arg_imm(indx+3, cnt);
		 	break;
		 case "OR":
		 		if(splitted.length<indx+3)
		 		{
		 		 interpret.Errors.sym_err(2, cnt);
		 		}
		 		
		 	q=new int[3];
			q[0]=do_arg_var(indx+1, cnt, true);
			q[1]=do_arg_var(indx+2, cnt, false);
			q[2]=do_arg_var(indx+3, cnt, false);
		 	break;
		 case "ORI":
		 		if(splitted.length<indx+3)
		 		{
		 		 interpret.Errors.sym_err(2, cnt);
		 		}
		 		
		 	q=new int[3];
			q[0]=do_arg_var(indx+1, cnt, true);
			q[1]=do_arg_var(indx+2, cnt, false);
			q[2]=do_arg_imm(indx+3, cnt);
		 	break;
		 case "XOR":
		 		if(splitted.length<indx+3)
		 		{
		 		 interpret.Errors.sym_err(2, cnt);
		 		}
		 		
		 	q=new int[3];
			q[0]=do_arg_var(indx+1, cnt, true);
			q[1]=do_arg_var(indx+2, cnt, false);
			q[2]=do_arg_var(indx+3, cnt, false);
		 	break;
		 case "XORI":
		 		if(splitted.length<indx+3)
		 		{
		 		 interpret.Errors.sym_err(2, cnt);
		 		}
		 		
		 	q=new int[3];
			q[0]=do_arg_var(indx+1, cnt, true);
			q[1]=do_arg_var(indx+2, cnt, false);
			q[2]=do_arg_imm(indx+3, cnt);
		 	break;
		 case "NAND":
		 		if(splitted.length<indx+3)
		 		{
		 		 interpret.Errors.sym_err(2, cnt);
		 		}
		 		
		 	q=new int[3];
			q[0]=do_arg_var(indx+1, cnt, true);
			q[1]=do_arg_var(indx+2, cnt, false);
			q[2]=do_arg_var(indx+3, cnt, false);
		 	break;
		 case "NOR":
		 		if(splitted.length<indx+3)
		 		{
		 		 interpret.Errors.sym_err(2, cnt);
		 		}
		 		
		 	q=new int[3];
			q[0]=do_arg_var(indx+1, cnt, true);
			q[1]=do_arg_var(indx+2, cnt, false);
			q[2]=do_arg_var(indx+3, cnt, false);
		 	break;
		 case "JUMP":
		 		if(splitted.length<indx+1)
		 		{
		 		 interpret.Errors.sym_err(2, cnt);
		 		}
		 		
		 	q=new int[1];
			q[0]=do_arg_lbl(indx+1, cnt);
		 	break;
		 case "JPEQ":
		 		if(splitted.length<indx+3)
		 		{
		 		 interpret.Errors.sym_err(2, cnt);
		 		}
		 		
		 	q=new int[3];
			q[0]=do_arg_var(indx+1, cnt, false);
			q[1]=do_arg_var(indx+2, cnt, false);
			q[2]=do_arg_lbl(indx+3, cnt);
		 	break;
		 case "JPNE":
		 		if(splitted.length<indx+3)
		 		{
		 		 interpret.Errors.sym_err(2, cnt);
		 		}
		 		
		 	q=new int[3];
			q[0]=do_arg_var(indx+1, cnt, false);
			q[1]=do_arg_var(indx+2, cnt, false);
			q[2]=do_arg_lbl(indx+3, cnt);
		 	break;
		 case "JPLT":
		 		if(splitted.length<indx+3)
		 		{
		 		 interpret.Errors.sym_err(2, cnt);
		 		}
		 		
		 	q=new int[3];
			q[0]=do_arg_var(indx+1, cnt, false);
			q[1]=do_arg_var(indx+2, cnt, false);
			q[2]=do_arg_lbl(indx+3, cnt);
		 	break;
		 case "JPGT":
		 		if(splitted.length<indx+3)
		 		{
		 		 interpret.Errors.sym_err(2, cnt);
		 		}
		 		
		 	q=new int[3];
			q[0]=do_arg_var(indx+1, cnt, false);
			q[1]=do_arg_var(indx+2, cnt, false);
			q[2]=do_arg_lbl(indx+3, cnt);
		 	break;
		 case "LDW":
		 		if(splitted.length<indx+2)
		 		{
		 		 interpret.Errors.sym_err(2, cnt);
		 		}
		 		
		 	q=new int[2];
			q[0]=do_arg_var(indx+1, cnt, true);
			q[1]=do_arg_var(indx+2, cnt, true);
		 	break;
		 case "LDB":
		 		if(splitted.length<indx+2)
		 		{
		 		 interpret.Errors.sym_err(2, cnt);
		 		}
		 		
		 	q=new int[2];
			q[0]=do_arg_var(indx+1, cnt, true);
			q[1]=do_arg_var(indx+2, cnt, true);
		 	break;
		 case "STW":
		 		if(splitted.length<indx+2)
		 		{
		 		 interpret.Errors.sym_err(2, cnt);
		 		}
		 		
		 	q=new int[2];
			q[0]=do_arg_var(indx+1, cnt, false);
			q[1]=do_arg_var(indx+2, cnt, true);
		 	break;
		 case "STB":
		 		if(splitted.length<indx+2)
		 		{
		 		 interpret.Errors.sym_err(2, cnt);
		 		}
		 		
		 	q=new int[2];
			q[0]=do_arg_var(indx+1, cnt, false);
			q[1]=do_arg_var(indx+2, cnt, true);
		 	break;
		 case "PTLN":
		 	q=do_arg_none();
		 	break;
		 case "PTINT":
		 		if(splitted.length<indx+1)
		 		{
		 		 interpret.Errors.sym_err(2, cnt);
		 		}
		 		
		 	q=new int[1];
			q[0]=do_arg_var(indx+1, cnt, false);
		 	break;
		 case "PTCHR":
		 		if(splitted.length<indx+1)
		 		{
		 		 interpret.Errors.sym_err(2, cnt);
		 		}
		 		
		 	q=new int[1];
			q[0]=do_arg_var(indx+1, cnt, false);
		 	break;
		 case "RDINT":
		 		if(splitted.length<indx+1)
		 		{
		 		 interpret.Errors.sym_err(2, cnt);
		 		}
		 		
		 	q=new int[1];
			q[0]=do_arg_var(indx+1, cnt, true);
		 	break;
		 case "RDCHR":
		 		if(splitted.length<indx+1)
		 		{
		 		 interpret.Errors.sym_err(2, cnt);
		 		}
		 		
		 	q=new int[1];
			q[0]=do_arg_var(indx+1, cnt, true);
		 	break;
		 default:
		 	interpret.Errors.sym_err(1, cnt);
 		}
 		
 	 return q;
 	}
 	
 	private int[] do_arg_none()
 	{
 	 int[] q=new int[3];
 	 q[0]=-1;
 	 q[1]=-1;
 	 q[2]=-1;
 	 return q;
 	}
 	
 	private int do_arg_var(int indx, int cnt, boolean check_zero)
 	{
 		if(splitted[indx].startsWith("#"))
 		{
 		 interpret.Errors.sym_err(2, cnt);
 		}
 		
 		if(!all_lower(splitted[indx]))
 		{
 		 interpret.Errors.sym_err(3, cnt);
 		}
 		
		if(check_zero && splitted[indx]=="zero")
		{
		 interpret.Errors.sym_err(0, cnt);
		}
		
		if(!varies.containsKey(splitted[indx]))
		{
		 varies.put(splitted[indx], vars_num);
		 vars_num++;
		}
		
	 return varies.get(splitted[indx]);
 	}
 	
 	private int do_arg_imm(int indx, int cnt)
 	{
 	 int ret=0;
 	 
 		if(splitted[indx].startsWith("#"))
 		{
 		 interpret.Errors.sym_err(2, cnt);
 		}
 		
		if(splitted[indx].startsWith("0x"))
		{
			try
			{
			 ret=Integer.parseInt(splitted[indx].substring(2, splitted[indx].length()), 16);
			}
			catch (NumberFormatException e)
			{
			 interpret.Errors.arit_err(1, cnt);
			}
		}
		else
		{
			try
			{
			 ret=Integer.parseInt(splitted[indx]);
			}
			catch (NumberFormatException e)
			{
			 interpret.Errors.arit_err(1, cnt);
			}
		}
		
	 return ret;
 	}
 	
 	private int do_arg_lbl(int indx, int cnt)
 	{
 	 	if(splitted[indx].startsWith("#"))
 		{
 		 interpret.Errors.sym_err(2, cnt);
 		}
 		
 		if(!all_lower(splitted[indx]))
 		{
 		 interpret.Errors.lbl_err(3, cnt);
 		}
 		
		if(etnums.indexOf(splitted[indx])<0)
		{
		 etnums.add(splitted[indx]);
		}
	 
	 return etnums.indexOf(splitted[indx]);
 	}
 	
 	private boolean all_lower(String s)
 	{
 		for(int i=0;i<s.length();i++)
 		{
 			if((int) s.charAt(0)<97 && (int) s.charAt(0)>122)
 			{
 			 return false;
 			}
 		}
 	
 	 return true;
 	}
}
