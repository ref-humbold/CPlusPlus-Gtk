package ref_humbold.apolanguage.interpret;

import java.uitl.Iterable;
import java.util.Iterator;

import ref_humbold.apolanguage.interpret.instructions.Instruction;
import ref_humbold.apolanguage.interpret.instructions.StandardInstruction;
import ref_humbold.apolanguage.interpret.instructions.JumpInstruction;

/**
Klasa przechowujaca liste instrukcji programu.
Lista zostaje utworzona podczas parsowania.
@see Parser#parseProgram
*/
public class InstructionList
    implements Iterable <Instruction>
{
    private class InstructionIterator
        implements Iterator <Instruction>
    {
        private Instruction currentInstruction;
        
        InstructionIterator(Instruction instr)
        {
            currentInstruction = instr;
        }
        
        boolean hasNext()
        {
            return currentInstruction == null;
        }
        
        Instruction next()
            throws NoSuchElementException
        {
            if(!hasNext())
                throw new NoSuchElementException();
            
            if(currentInstruction instanceof JumpInstruction)
            {
                JumpInstruction jumpInstr = (JumpInstruction)currentInstruction;
                boolean isJump = false;
                
                switch(jumpInstr.getName())
                {
                    case "JUMP":
                        isJump = true;
                        break;

                    case "JPEQ":
                        arg0 = variableMap.getValue( jumpInstr.getArg(0) );
                        arg1 = variableMap.getValue( jumpInstr.getArg(1) );
                        isJump = arg0 == arg1;
                        break;

                    case "JPNE":
                        arg0 = variableMap.getValue( jumpInstr.getArg(0) );
                        arg1 = variableMap.getValue( jumpInstr.getArg(1) );
                        isJump = arg0 != arg1;
                        break;

                    case "JPLT":
                        arg0 = variableMap.getValue( jumpInstr.getArg(0) );
                        arg1 = variableMap.getValue( jumpInstr.getArg(1) );
                        isJump = arg0 < arg1;
                        break;

                    case "JPGT":
                        arg0 = variableMap.getValue( jumpInstr.getArg(0) );
                        arg1 = variableMap.getValue( jumpInstr.getArg(1) );
                        isJump = arg0 > arg1;
                        break;
                }
                
                currentInstruction = isJump ? jumpInstr.linkedInstruction() : jumpInstr.nextInstruction;
            }
            else
                currentInstruction = currentInstruction.nextInstruction;
            
            return currentInstruction;
        }
    }
 
    private Instruction listBegin;
    private Instruction listEnd;
 
     /** Tworzy nowa pusta liste rozkazow. */
    public InstructionList()
    {
        listBegin = new StandardInstruction(-1, "NONE", null);
        listEnd = listBegin;
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
        if( instructionName.startsWith("J") )
            listEnd.nextInstruction = new JumpInstruction(lineNumber, instructionName, instructionArgs);
        else
            listEnd.nextInstruction =  new StandardInstruction(lineNumber, instructionName, instructionArgs);
        
        listEnd = listEnd.nextInstruction;
     
        return listEnd;
    }
}

