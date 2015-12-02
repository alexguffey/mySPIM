#include "spimcore.h"


/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{

}

/* instruction fetch */
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


/* instruction partition */
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



/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{
	switch(op) {
		case 0: //ALU does addition or "don't care"
			controls->RegDst = 1;
			controls->Jump = 0;
			controls->Branch = 0;
			controls->MemRead = 0;
			controls->MemtoReg = 0;
			controls->ALUOp = ;
			controls->MemWrite = 0;
			controls->ALUSrc = 1;
			controls->RegWrite = 1;
			break;
			
		case 1: //ALU does subtraction
			controls->RegDst = ;
			controls->Jump = ;
			controls->Branch = ;
			controls->MemRead = ;
			controls->MemtoReg = ;
			controls->ALUOp = ;
			controls->MemWrite = ;
			controls->ALUSrc = ;
			controls->RegWrite = ;
			break;
			
		case 2: //ALU does "set less than"
			controls->RegDst = ;
			controls->Jump = ;
			controls->Branch = ;
			controls->MemRead = ;
			controls->MemtoReg = ;
			controls->ALUOp = ;
			controls->MemWrite = ;
			controls->ALUSrc = ;
			controls->RegWrite = ;
			break;
			
		case 3: //ALU does "set less than unsigned"
			controls->RegDst = ;
			controls->Jump = ;
			controls->Branch = ;
			controls->MemRead = ;
			controls->MemtoReg = ;
			controls->ALUOp = ;
			controls->MemWrite = ;
			controls->ALUSrc = ;
			controls->RegWrite = ;
			break;
			
		case 4: //ALU does "and"
			controls->RegDst = ;
			controls->Jump = ;
			controls->Branch = ;
			controls->MemRead = ;
			controls->MemtoReg = ;
			controls->ALUOp = ;
			controls->MemWrite = ;
			controls->ALUSrc = ;
			controls->RegWrite = ;
			break;
			
		case 5: //ALU does "or"
			controls->RegDst = ;
			controls->Jump = ;
			controls->Branch = ;
			controls->MemRead = ;
			controls->MemtoReg = ;
			controls->ALUOp = ;
			controls->MemWrite = ;
			controls->ALUSrc = ;
			controls->RegWrite = ;
			break;
			
		case 6:  //ALU will shift left extended value by 16 bits 
			controls->RegDst = ;
			controls->Jump = ;
			controls->Branch = ;
			controls->MemRead = ;
			controls->MemtoReg = ;
			controls->ALUOp = ;
			controls->MemWrite = ;
			controls->ALUSrc = ;
			controls->RegWrite = ;
			break;
			
		case 7: //R-type instruction
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
			
		default: //invalid instruction
			return 1;
			break;
	}
	
	return 0;
}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{

}


/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{

}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{

}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{

}


/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{

}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{

}

