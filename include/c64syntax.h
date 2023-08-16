/*
Copyright (c) 2023 Noah Scholz

This file is part of the c64asm project.

c64asm is free software: you can redistribute it and/or modify
it under the terms of the MIT License. See the LICENSE file.

c64asm is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

You should have received a copy of the MIT License
along with c64asm. If not, see <https://mit-license.org/>.
*/
#ifndef _c64syntax_h_
# define _c64syntax_h_

// instructions
// Order is important !
enum
{
	I_LDI,
	I_LDBI,
	I_LDWI,
	I_LDDI,
	I_LDM,
	I_LDBM,
	I_LDWM,
	I_LDDM,
	I_ST,
	I_STB,
	I_STW,
	I_STD,
	I_TF,
	I_ADDI,
	I_SUBI,
	I_MULI,
	I_DIVI,
	I_MODI,
	I_MULIS,
	I_DIVIS,
	I_ADD,
	I_SUB,
	I_MUL,
	I_DIV,
	I_MOD,
	I_MULS,
	I_DIVS,
	I_ANDI,
	I_ORI,
	I_XORI,
	I_NOTI,
	I_SHLI,
	I_SHRI,
	I_RORI,
	I_ROLI,
	I_AND,
	I_OR,
	I_XOR,
	I_NOT,
	I_SHL,
	I_SHR,
	I_ROR,
	I_ROL,
	I_CMP,
	I_CMPI,
	I_JMP,
	I_JEQ,
	I_JNE,
	I_JGT,
	I_JLT,
	I_JGE,
	I_JLE,
	I_BRA,
	I_BEQ,
	I_BNE,
	I_BGT,
	I_BLT,
	I_BGE,
	I_BLE,
	I_JMPR,
	I_JEQR,
	I_JNER,
	I_JGTR,
	I_JLTR,
	I_JGER,
	I_JLER,
	I_BRAR,
	I_BEQR,
	I_BNER,
	I_BGTR,
	I_BLTR,
	I_BGER,
	I_BLER,
	I_RET,
	I_PUSH,
	I_PUSHI,
	I_POP,
	I_CALL,
	I_CALLR,
	I_RTC,
	I_CLC,
	I_SEC,
	I_CLZ,
	I_SEZ,
	I_CLN,
	I_SEN,
	I_CLV,
	I_SEV,
	I_CLI,
	I_SEI,
	I_INT,
	I_RTI,
	I_NOP,
	I_HLT
};

// addressing modes
enum
{
	SING_REG, // single register
	SING_IMM, // single immediate
	REG_IMM,  // register and immediate
	REG_REG,  // register and register
	IMM_SYM,  // immediate and symbol
	NONE,     // no operands
};

// operand types
enum
{
	OP_REG,
	OP_IMM,
	OP_SYM,
	OP_NONE
};

struct							c64symbol
{
	char						*name;
	int							value;
	struct c64symbol			*next;
};

struct							c64operand
{
	int							type;
	int							value;
};

struct							c64instruction
{
	int							type;
	int							mode;
	int							opcode;
};

struct							instruction_list
{
	struct c64instruction		*instruction;
	struct c64instruction_list	*next;
};

int	c64syntax_getOpcode(int type); // in table
int	c64syntax_getMode(int type);   // in table

void							c64syntax_addSymbol(struct c64symbol *anchor,
									char *name, int value);

#endif // _c64syntax_h_