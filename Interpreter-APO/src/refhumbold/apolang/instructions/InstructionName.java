package refhumbold.apolang.instructions;

public enum InstructionName
{
    ADD, ADDI, SUB, SUBI, MUL, MULI, DIV, DIVI,

    SHLT, SHRT, SHRS, AND, ANDI, OR, ORI, XOR, XORI, NAND, NOR,

    JUMP, JPEQ, JPNE, JPLT, JPGT,

    LDW, LDB, STW, STB,

    PTLN, PTINT, PTCHR, RDINT, RDCHR,

    NOP
}
