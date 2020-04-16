#include "spimcore.h"
// **IMPORTANT**	I've added your names next to the functions that you are responsible for.
//			Once you finish a function, please add a comment saying you're done at the top
//			to keep us updated. Thanks.

//			Reminder: Once the code compiles, delete all unnecessary comments.


/* ALU */
/* 10 Points */

// Al//
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

/**KEVIN - DONE**/

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

//**KEVIN - DONE**//

//	Breaks down the instruction using bitwise AND masking and shifting.
//	To partition the opcode, we shift the 32 bit number 26 times to the right to get only the first 6 digits.
//	To partition the other parts of the instructions, shift the code in a similar manner to the bits desired
//	and then use bitwise AND for however many digits we want to mask.
//	For example, to retrieve r1, we are concerned with bits 25-21, so we would shift right 21 times first
//	and mask the left bits.
//	Using the 0x prefix, we can denote binary numbers in hexadecimal to keep the code cleaner.

void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{
	*op = instruction >> 26;		//	bits 31-26
	*r1 = instruction >> 21 &0x1F;		//	bits 25-21
	*r2 = instruction >> 16 &0x1F;		//	bits 20-16
	*r3 = instruction >> 11	&0x1F;		//	bits 15-11
	
	//	The following don't require a shift since they approach the highest order bits.
	
	*funct = instruction 0x3F;		//	bits 5-0
	*offset = instruction & 0xFFFF;		//	bits 15-0
	*jsec = instruction & 0x3FFFFFF;	//	bits 25-0
}

/* instruction decode */
/* 15 Points */

// KEV - DONE //

	//	Depending on the instruction type (determined by the op), enable, disable, or dc the corresponding signal.

int instruction_decode(unsigned op,struct_controls *controls)
{
	//	Set the following in the manner described: 1 = enable, 0 = disable, 2 = dc
	//	MemRead: 	operation reads from memory
	//	MemWrite: 	operations writes to memory
	//	RegWrite:	operation writes to register
	
	//	RegDst:		Signal is 0 if storing in r2, 1 if storing in r3 (r-type inst)
	//	Jump:		Jump instruction
	//	Branch:		Branch instruction
	//	MemtoReg:	Memory info is stored in regsiter
	//	ALUSrc:		0 if r2 register is the source (r-type), 1 if source is the sign-extended value
	//	ALUOp:		0 = add/dc, 1 = sub, 2 = slt, 3 = sltu, 4 = and, 5 = or, 6 = sll, 7 = r-type
	
	//	R-type instructions
	if(op == 0)
	{
		controls->RegDst = '1';
		controls->Jump = '0';
		controls->Branch = '0';
		controls->MemRead = '0';
		controls->MemtoReg = '0';
		controls->ALUOp = '7';
		controls ->MemWrite = '0';
		controls->ALUSrc = '0';
		controls ->RegWrite = '1';
		return 0;
	}
	
	//	J-type instructions 
	else if(op == 2)
	{
		controls->RegDst = '2';
		controls->Jump = '1';
		controls->Branch = '0';
		controls->MemRead = '0';
		controls->MemtoReg = '0';
		controls->ALUOp = '0';
		controls ->MemWrite = '0';
		controls->ALUSrc = '1';
		controls ->RegWrite = '0';
		return 0;
	}
	
	//	Beq instruction
	else if(op == 4)
	{
		controls->RegDst = '2';
		controls->Jump = '0';
		controls->Branch = '1';
		controls->MemRead = '0';
		controls->MemtoReg = '0';
		controls->ALUOp = '1';
		controls ->MemWrite = '0';
		controls->ALUSrc = '0';
		controls ->RegWrite = '0';
		return 0;
	}
	
	//	addi instruction
	else if(op == 8)
	{
		controls->RegDst = '0';
		controls->Jump = '0';
		controls->Branch = '0';
		controls->MemRead = '0';
		controls->MemtoReg = '0';
		controls->ALUOp = '0';
		controls ->MemWrite = '0';
		controls->ALUSrc = '1';
		controls ->RegWrite = '1';
		return 0;
	}
	
	//	slti instruction
	else if(op == 10)
	{
		controls->RegDst = '0';
		controls->Jump = '0';
		controls->Branch = '0';
		controls->MemRead = '0';
		controls->MemtoReg = '0';
		controls->ALUOp = '2';
		controls ->MemWrite = '0';
		controls->ALUSrc = '1';
		controls ->RegWrite = '1';
		return 0;
	}
	
	//	sltiu instruction
	else if(op == 11)
	{
		controls->RegDst = '0';
		controls->Jump = '0';
		controls->Branch = '2';
		controls->MemRead = '0';
		controls->MemtoReg = '0';
		controls->ALUOp = '3';
		controls ->MemWrite = '0';
		controls->ALUSrc = '1';
		controls ->RegWrite = '1';
		return 0;
	}
	
	//	lui instruction
	else if(op == 15)
	{
		controls->RegDst = '0';
		controls->Jump = '0';
		controls->Branch = '0';
		controls->MemRead = '0';
		controls->MemtoReg = '0';
		controls->ALUOp = '6';
		controls ->MemWrite = '0';
		controls->ALUSrc = '1';
		controls ->RegWrite = '1';
		return 0;
	}
	
	//	lw instruction
	else if(op == 35)
	{
		controls->RegDst = '0';
		controls->Jump = '0';
		controls->Branch = '0';
		controls->MemRead = '1';
		controls->MemtoReg = '1';
		controls->ALUOp = '0';
		controls ->MemWrite = '0';
		controls->ALUSrc = '1';
		controls ->RegWrite = '1';
		return 0;
	}
	
	//	sw instruction
	else if(op == 43)
	{
		controls->RegDst = '2';
		controls->Jump = '0';
		controls->Branch = '0';
		controls->MemRead = '0';
		controls->MemtoReg = '0';
		controls->ALUOp = '0';
		controls ->MemWrite = '1';
		controls->ALUSrc = '1';
		controls ->RegWrite = '0';
		return 0;
	}
	
	//	illegal instruction, halt condition.
	else
	{
		return 1;
	}
}

/* Read Register */
/* 5 Points */

// Kev - DONE //

//	Read the registers addressed by r1 and r2 from Reg, 
//	and write the read values to data1 and data2 respectively.

void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{
	*data1 = Reg[r1];
	*data2 = Reg[r2];
}

// Al //
/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{
    // Shifting to the sign bit (requires a shift of 15)
    // If that significant bit is 1 which is negative then we,
    // Ihen we expand to 32 bits, all the new bits being being 1's
    if((offset >> 15) == 1)
        *extended_value = offset | 0xffff0000;

    // else if it's not negative we just keep the 16 bits the other 16 bits will stay zero
    else
        *extended_value = offset & 0x0000ffff;
}

// Dimitri //
/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{

}

// Dimitri //
/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{

}

// Dimitri//
/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{

}

// Al //
/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{
	// Update program counter to the next word
   	*PC += 4;

    	// If Branch equal 1 and Zero equal 1, offset the program counter by shifting it left by 2 bits
    	if(Zero == 1 && Branch == 1)
        *PC += extended_value << 2;

    	// If Jump equal 1, use upper four bits, shift left by 2 bit, you'll get left with one word or 32 bits
    	if(Jump == 1)
        *PC = (jsec << 2) | (*PC & 0xf0000000);
}

