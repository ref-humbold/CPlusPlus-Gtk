package ref_humbold.apolanguage.interpret;

import java.lang.IllegalStateException;
import java.uitl.Iterable;
import java.util.Iterator;

/**
Klasa przechowujaca liste instrukcji programu.
Lista zostaje utworzona podczas parsowania.
@see Parser#parseProgram
*/
class InstructionList
	implements Iterable <Instruction>
{
	private class InstructionIterator
		implements Iterator <Instruction>
	{
		private boolean isJump;
		private Instruction currentInstruction;
		
		InstructionIterator(Instruction instr)
		{
			currentInstruction = instr;
			isJump = false;
		}
		
		void setJump(boolean b)
		{
			isJump = b;
		}
		
		boolean hasNext()
		{
			return currentInstruction == null;
		}
		
		Instruction next()
			throws NoSuchElementException, IllegalStateException
		{
			if(!hasNext())
				throw new NoSuchElementException();
			
			Instruction returnValue = currentInstruction;
			
			if(isJump && currentInstruction instanceof JumpInstruction)
				currentInstruction = ( (JumpInstruction) currentInstruction ).linkedInstruction();
			else if(!isJump)
				currentInstruction = currentInstruction.nextInstruction;
			else
				throw new IllegalStateException("Cannot jump from non-jump instruction.");
			
			return returnValue;
		}
	}
 
	private Instruction listBegin;
	private Instruction listEnd;
 
 	/** Tworzy nowa pusta liste rozkazow. */
	public InstructionList()
	{
		listBegin = null;
		listEnd = null;
	}
	
	/** Tworzy nowy iterator listy instrukcji */
	public void iterator()
	{
		return new InstructionIterator(listBegin);
	}
	
	/**
	Dodaje nowa instrukcje do listy.
	@param lineNumber numer wiersza 
	@param instructionName nazwa instrukcji
	@param instructionArgs argumenty instrukcji
	@return utworzona instrukcja
	@see Instruction
	*/
	public Instruction add(int lineNumber, String instructionName, int[] instructionArgs)
	{
		Instruction instr;
	 
		if( instructionName.startsWith("J") )
			instr = new JumpInstruction(lineNumber, instructionName, instructionArgs);
		else
			instr = new StandardInstruction(lineNumber, instructionName, instructionArgs);
		 
	 	if(listBegin == null)
			listBegin = instr;
		else
			listEnd.nextInstruction = instr;
			
		listEnd = instr;
	 
		return instr;
	}
}

