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
#include "c64syntax.h"

int	c64syntax_isInstruction(struct c64tokenlist *list)
{
	return (list->token->type == T_INST);
}

int	c64syntax_isRegister(struct c64tokenlist *list)
{
	return (list->token->type == T_REG);
}

int	c64syntax_isImmediate(struct c64tokenlist *list)
{
	return (list->token->type == T_IMM);
}

int	c64syntax_isLabel(struct c64tokenlist *list)
{
	return (list->token->type == T_LABEL);
}

int	c64syntax_isLabelRef(struct c64tokenlist *list)
{
	return (list->token->type == T_IDENT);
}

int	c64syntax_isComma(struct c64tokenlist *list)
{
	return (list->token->type == T_COMMA);
}

int	c64syntax_isColon(struct c64tokenlist *list)
{
	return (list->token->type == T_COLON);
}

int	c64syntax_isLBrace(struct c64tokenlist *list)
{
	return (list->token->type == T_LBRACE);
}

int	c64syntax_isRBrace(struct c64tokenlist *list)
{
	return (list->token->type == T_RBRACE);
}

int	c64syntax_isVar(struct c64tokenlist *list)
{
	return (list->token->type == T_VAR);
}

struct c64tokenlist	*c64syntax_nextToken(struct c64tokenlist *list)
{
	Token = *(list->next->token);
	Line = list->next->token->line;
	Pos = list->next->token->pos;
	return (list->next);
}



int	c64syntax_getMode(int type)
{
	switch (type)
	{
	case I_RET:
	case I_CLC:
	case I_SEC:
	case I_CLZ:
	case I_SEZ:
	case I_CLN:
	case I_SEN:
	case I_CLV:
	case I_SEV:
	case I_CLI:
	case I_SEI:
	case I_RTI:
	case I_RTC:
	case I_NOP:
	case I_HLT:
		return (M_NONE);
	case I_JMPR:
	case I_JEQR:
	case I_JNER:
	case I_JGTR:
	case I_JGER:
	case I_JLTR:
	case I_JLER:
	case I_BRAR:
	case I_BEQR:
	case I_BNER:
	case I_BGTR:
	case I_BLTR:
	case I_BGER:
	case I_BLER:
	case I_PUSH:
	case I_POP:
	case I_CALLR:
		return (M_SING_REG);
	case I_JMP:
	case I_JEQ:
	case I_JNE:
	case I_JGT:
	case I_JGE:
	case I_JLT:
	case I_JLE:
	case I_BRA:
	case I_BEQ:
	case I_BNE:
	case I_BGT:
	case I_BGE:
	case I_BLT:
	case I_BLE:
	case I_CALL:
		return (M_SING_IMM | M_SYM);
	case I_LDI:
	case I_LDBI:
	case I_LDWI:
	case I_LDDI:
	case I_LDM:
	case I_LDBM:
	case I_LDWM:
	case I_LDDM:
	case I_ST:
	case I_STB:
	case I_STW:
	case I_STD:
	case I_ADDI:
	case I_SUBI:
	case I_MULI:
	case I_DIVI:
	case I_MODI:
	case I_MULIS:
	case I_DIVIS:
	case I_ANDI:
	case I_ORI:
	case I_XORI:
	case I_NOTI:
	case I_SHLI:
	case I_SHRI:
	case I_RORI:
	case I_ROLI:
	case I_CMPI:
		return (M_REG_IMM);
	case I_TF:
	case I_ADD:
	case I_SUB:
	case I_MUL:
	case I_DIV:
	case I_MOD:
	case I_MULS:
	case I_DIVS:
	case I_AND:
	case I_OR:
	case I_XOR:
	case I_NOT:
	case I_SHL:
	case I_SHR:
	case I_ROR:
	case I_ROL:
	case I_CMP:
		return (M_REG_REG);
	case I_INT:
	case I_PUSHI:
		return (M_SING_IMM);
	default:
		c64utils_fatald("c64syntax_getMode: invalid instruction type", type);
		return (-1);
	}
}