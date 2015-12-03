#include "spimcore.h"


/* Hassan: ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{
  if(ALUControl==0)
    *ALUresult=A+B;
  if(ALUControl==1)
    *ALUresult=A-B;
  if(ALUControl==2)
    if((signed)A<(signed)B)
      *ALUresult=1;
    else
      *ALUresult=0;
  if(ALUControl==3)
    if(A<B)
      *ALUresult=1;
    else
      *ALUresult=0;
  if(ALUControl==4)
    *ALUresult = A&B;
  if(ALUControl==5)
    *ALUresult = A|B;
  if(ALUControl==6)
    *ALUresult=B<<16;

  if(ALUControl==7)
    *ALUresult=~A;
  if(*ALUresult==0)
    Zero=1;
  else
    Zero=0;
}

/* Trevor: instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
    //Move PC forward
	PC = PC >> 2;

	//Proper PC will always be evenly divisible by 4
	if(PC % 4 == 0) {
		*instruction = Mem[PC];
		return 0;
	}
	//Out of whack Program Counter
	else {
		return 1;
	}
}


/* Trevor: instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{

    //need masks of different sizes
	//5-bits
	unsigned rtypePart = 0x1f;
	//6-bits
	unsigned functPart = 0x0000003f;
	//16-bits
	unsigned offsetPart = 0x0000ffff;
	//26-bits
	unsigned jsecPart = 0x03ffffff;

	//shift values down, apply masks
	//bits[31-26]
	*op = (instruction >> 26) & functPart;
	//bits[25-21]
	*r1 = (instruction >> 21) & rtypePart;
	//bits[20-16]
	*r2 = (instruction >> 16) & rtypePart;
	//bits[15-11]
	*r3 = (instruction >> 11) & rtypePart;
	//bits[5-0]
	*func = instruction & rtypePart;

	//bits[15-0] for I-type
	*offset = instruction & offsetPart;

	//bits[25-0] for J-type
	*jsec = instruction & jsecPart;

}



/* Trevor: instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{

    switch(op) {
		case 0:   // r-type
        controls->RegDst = 1;
        controls->Jump = 0;
        controls->Branch = 0;
        controls->MemRead = 0;
        controls->MemtoReg = 0;
        controls->ALUOp = 7;
        controls->MemWrite = 0;
        controls->ALUSrc = 0;
        controls->RegWrite = 1;
        break;
    case 2:  // jump
        controls->RegDst = 0;
        controls->Jump = 1;
        controls->Branch = 0;
        controls->MemRead = 0;
        controls->MemtoReg = 0;
        controls->ALUOp = 0;
        controls->MemWrite = 0;
        controls->ALUSrc = 0;
        controls->RegWrite = 0;
        break;
    case 4:  // beq
        controls->RegDst = 2;
        controls->Jump = 0;
        controls->Branch = 1;
        controls->MemRead = 0;
        controls->MemtoReg = 2;
        controls->ALUOp = 1;
        controls->MemWrite = 0;
        controls->ALUSrc = 1;
        controls->RegWrite = 0;
        break;
    case 8:   // addi
        controls->RegDst = 0;
        controls->Jump = 0;
        controls->Branch = 0;
        controls->MemRead = 0;
        controls->MemtoReg = 0;
        controls->ALUOp = 0;
        controls->MemWrite = 0;
        controls->ALUSrc = 1;
        controls->RegWrite = 1;
        break;
    case 10:  // slti
        controls->RegDst = 0;
        controls->Jump = 0;
        controls->Branch = 0;
        controls->MemRead = 0;
        controls->MemtoReg = 0;
        controls->ALUOp = 2;
        controls->MemWrite = 0;
        controls->ALUSrc = 1;
        controls->RegWrite = 0;
        break;
    case 11:  // sltiu
        controls->RegDst = 0;
        controls->Jump = 0;
        controls->Branch = 0;
        controls->MemRead = 0;
        controls->MemtoReg = 0;
        controls->ALUOp = 3;
        controls->MemWrite = 0;
        controls->ALUSrc = 1;
        controls->RegWrite = 0;
        break;
    case 15:  // lui
        controls->RegDst = 0;
        controls->Jump = 0;
        controls->Branch = 0;
        controls->MemRead = 0;
        controls->MemtoReg = 0;
        controls->ALUOp = 6;
        controls->MemWrite = 0;
        controls->ALUSrc = 1;
        controls->RegWrite = 1;
        break;
    case 35:  // lw
        controls->RegDst = 0;
        controls->Jump = 0;
        controls->Branch = 0;
        controls->MemRead = 1;
        controls->MemtoReg = 1;
        controls->ALUOp = 0;
        controls->MemWrite = 0;
        controls->ALUSrc = 1;
        controls->RegWrite = 1;
        break;
    case 43:  // sw
        controls->RegDst = 2;
        controls->Jump = 0;
        controls->Branch = 0;
        controls->MemRead = 0;
        controls->MemtoReg = 2;
        controls->ALUOp = 0;
        controls->MemWrite = 1;
        controls->ALUSrc = 1;
        controls->RegWrite = 0;
        break;
    default: //invalid instruction
        return 1;
        break;
	}

	return 0;
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
  unsigned temp = offset>>15;
  if(temp==1)
    *extended_value=(0xFFFF0000)|offset;
  else
    *extended_value=offset;
}

/* Hassan: ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{
  if(ALUsrc==1)
    data2=extended_value;
  //Not R-type 0-6
  if((ALUOp==0)||(ALUOp==1)||(ALUOp==2)||(ALUOp==3)||(ALUOp==4)||(ALUOp==5)||(ALUOp==6))
    ALU(data1,data2,ALUOp,ALUresult,Zero);
    //R-type
  else if(ALUOp==7)
  {
    if(funct==32)
      ALU(data1,data2,0,ALUresult,Zero);
    else if(funct==34)
      ALU(data1,data2,1,ALUresult,Zero);
    else if(funct==42)
      ALU(data1,data2,2,ALUresult,Zero);
    else if(funct==43)
      ALU(data1,data2,3,ALUresult,Zero);
    else if(funct==36)
      ALU(data1,data2,4,ALUreult,Zero);
    else if(funct==37)
      ALU(data1,data2,5,ALUresult,Zero);
    else if(fucnt==6)
      ALU(data1,data2,6,ALUresult,Zero);
    else if(funct==39)
      ALU(data1,data2,7,ALUresult,Zero);
    else
      return 1;
  }
  else
    return 1;
  return 0;
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

