#include "spimcore.h"
// check again

/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{
// 1.Implement the operations on input parameters A and B according to ALUControl.
// 2. Output the result (Z) to ALUresult.

	//  Using switches to control which ALU control gets executed
	switch ((int) ALUControl)
	{
    // 000: Z = A + B "Addition"
	case 000:
		*ALUresult = A + B;
		break;

    // 001: Z = A - B "Subtraction"
	case 001:
		*ALUresult = A - B;
		break;

    // 010: if A < B, Z = 1; otherwise, Z = 0 (For signed integers) "Less than"
	case 010:
		if ((signed)A < (signed)B)
			*ALUresult = 1;
		else
            *ALUresult = 0;
		break;

    // 011: if A < B, Z = 1; otherwise, Z = 0 (For unsigned integers) "Less than"
	case 011:
		if (A < B)
			*ALUresult = 1;
		else
			*ALUresult = 0;
		break;

    // 100: Z = A AND B "bitwise AND"
	case 100:
		*ALUresult = A & B;
		break;

    // 101: Z = A OR B "bitwise OR"
	case 101:
		*ALUresult = A | B;
		break;

    // 110: Shift left B by 16 bits
	case 110:
        *ALUresult = B << 16;
		break;

    // 111: Z = NOT A (bitwise)
	case 111:
		*ALUresult = ~A;
		break;
	}

    // 3. Assign Zero to 1 if the result is zero; otherwise, assign 0.
	if (*ALUresult == 0)
		*Zero = 1;
	else
		*Zero = 0;

}

/* instruction fetch */
/* 10 Points */

//  Pre-processor directives: This function takes in PC from Mem and stores it in instruction.
//  Post-processor directives: function returns 1 if halt condition is met. Otherwise, return 0.
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
  //  Check if PC is word-aligned (divisible by 4) or beyond the scope of the memory of 64 kB.
  if(PC%4 != 0 || PC > 65536)
  {
    return 1;
  }
  else
  {
    //  Get the instruction from Mem
    *instruction = Mem[PC>>2];
    return 0;
  }
    
}


/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{

}



/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{

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

