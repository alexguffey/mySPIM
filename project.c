#include "spimcore.h"


/* Hassan: ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{
  if(ALUControl=='000')
    ALUresult=A+B;
  if(ALUControl=='001')
    ALUresult=A-B;
  if(ALUControl=='010')
  {
    if(A<B)
      ALUresult=1;
    else
      ALUresult=0;
  }
  if(ALUControl=='011')
  {
    if(A<B)
      ALUresult=1;
    else
      ALUresult=0;
  }
  if(ALUControl=='100')
  {
    if(A&&B)
      ALUresult=1;
    else
      ALUresult=0;
  }
  if(ALUControl=='101')
  {
    if(A||B)
      ALUresult=1;
    else
      ALUresult=0;
  }
  if(ALUControl=='110')
  {
    B<<16;
  }
  if(ALUControl=='111')
    ALUresult=!A;
  if(ALUresult==0)
    Zero=1;
}

/* Trevor: instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{

}


/* Trevor: instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{

}



/* Trevor: instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{

}

/* Alex: Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{

    // Read the registers addressed by r1 and r2 from Reg, and write the read values to data1 and data2 respectively.
    *data1 = Reg[r1];
    *data2 = Reg[r2];
}


/* Hassan: Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{

}

/* Hassan: ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{

}

/* Alex: Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{

    // Write data2 to memory based on index calculated from ALUresult
    if (MemWrite == 1) {
        if (ALUresult % 4 == 0) {
            Mem[ALUresult >> 2] = data2;
        } else {
            return 1;
        }
    }

    // Read memory based on index calculated from ALUresult
    if (MemRead == 1) {
        if (ALUresult % 4 == 0) {
            *memdata = Mem[ALUresult >> 2];
        } else {
            return 1;
        }
    }

    return 0;

}


/* Alex: Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{

    if (RegWrite == 1) {

        if (MemtoReg == 1) {
            if (RegDst == 0) {
                Reg[r2] = memdata;
            } else {
                Reg[r3] = memdata;
            }
        }

        if (MemtoReg == 0) {
            if (RegDst == 0) {
                Reg[r2] = ALUresult;
            } else {
                Reg[r3] = ALUresult;
            }
        }
    }

}

/* Alex: PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{

    *PC += 4;

    // If branch taken : PC + offset.  Figure out the correct offset value.
    if (Zero == 1 && Branch == 1) {
        *PC += extended_value << 2;
    }

    // Jump: Left shift bits of jsec by 2 and use upper 4 bits of PC
    if (Jump == 1) {
        *PC = (jsec << 2) | (*PC & 0xf0000000);
    }
}

