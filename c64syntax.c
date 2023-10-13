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

int	c64syntax_oneOf(int n, ...)
{
	int		i;
	int		s;
	va_list	args;

	va_start(args, n);
	for (i = 0; i < n; i++)
	{
		s = va_arg(args, int);
		if (s)
		{
			va_end(args);
			return (1);
		}
	}
	va_end(args);
	return (0);
}

int	c64syntax_require(int v)
{
	return (v);
}

int	c64syntax_not(int v)
{
	return (!v);
}

int	c64syntax_noneOf(int n, ...)
{
	int		i;
	int		s;
	va_list	args;

	va_start(args, n);
	for (i = 0; i < n; i++)
	{
		s = va_arg(args, int);
		if (s)
		{
			va_end(args);
			return (0);
		}
	}
	va_end(args);
	return (1);
}

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

struct c64tokenlist	*c64syntax_matchInstruction(struct c64tokenlist *list)
{
	if (!c64syntax_isInstruction(list))
		c64utils_fatals("c64syntax_matchInstruction: expected instruction got",
			c64token_typestr(list->token->type));
	return (c64syntax_nextToken(list));
}

struct c64tokenlist	*c64syntax_matchRegister(struct c64tokenlist *list)
{
	if (!c64syntax_isRegister(list))
		c64utils_fatals("c64syntax_matchRegister: expected register got",
			c64token_typestr(list->token->type));
	return (c64syntax_nextToken(list));
}

struct c64tokenlist	*c64syntax_matchImmediate(struct c64tokenlist *list)
{
	if (!c64syntax_isImmediate(list))
		c64utils_fatals("c64syntax_matchImmediate: expected immediate got",
			c64token_typestr(list->token->type));
	return (c64syntax_nextToken(list));
}

struct c64tokenlist	*c64syntax_matchLabel(struct c64tokenlist *list)
{
	if (!c64syntax_isLabel(list))
		c64utils_fatals("c64syntax_matchLabel: expected label got",
			c64token_typestr(list->token->type));
	return (c64syntax_nextToken(list));
}

struct c64tokenlist	*c64syntax_matchLabelRef(struct c64tokenlist *list)
{
	if (!c64syntax_isLabelRef(list))
		c64utils_fatals("c64syntax_matchLabelRef: expected label reference got",
			c64token_typestr(list->token->type));
	return (c64syntax_nextToken(list));
}

struct c64tokenlist	*c64syntax_matchComma(struct c64tokenlist *list)
{
	if (!c64syntax_isComma(list))
		c64utils_fatals("c64syntax_matchComma: expected comma got",
			c64token_typestr(list->token->type));
	return (c64syntax_nextToken(list));
}

struct c64tokenlist	*c64syntax_matchColon(struct c64tokenlist *list)
{
	if (!c64syntax_isColon(list))
		c64utils_fatals("c64syntax_matchColon: expected colon got",
			c64token_typestr(list->token->type));
	return (c64syntax_nextToken(list));
}

struct c64tokenlist	*c64syntax_matchLBrace(struct c64tokenlist *list)
{
	if (!c64syntax_isLBrace(list))
		c64utils_fatals("c64syntax_matchLBrace: expected left brace got",
			c64token_typestr(list->token->type));
	return (c64syntax_nextToken(list));
}

struct c64tokenlist	*c64syntax_matchRBrace(struct c64tokenlist *list)
{
	if (!c64syntax_isRBrace(list))
		c64utils_fatals("c64syntax_matchRBrace: expected right brace got",
			c64token_typestr(list->token->type));
	return (c64syntax_nextToken(list));
}

struct c64tokenlist	*c64syntax_matchVar(struct c64tokenlist *list)
{
	if (!c64syntax_isVar(list))
		c64utils_fatals("c64syntax_matchVar: expected var got",
			c64token_typestr(list->token->type));
	return (c64syntax_nextToken(list));
}

struct c64tokenlist	*c64syntax_nextToken(struct c64tokenlist *list)
{
	Token = *(list->next->token);
	Line = list->next->token->line;
	Pos = list->next->token->pos;
	return (list->next);
}

struct c64instruction	*c64syntax_parseMode(struct c64tokenlist *list,
		int mode)
{
	// At this point,
	// the current token is the first token after the instruction so the first token of the operands
	if (mode & M_NONE)
		return (c64syntax_matchNONE(list));
	if (mode & M_SING_REG)
		return (c64syntax_matchSING_REG(list));
	if (mode & M_SING_IMM && mode & M_SYM)
		return (c64syntax_matchSING_IMM_SYM(list));
	if (mode & M_SING_IMM)
		return (c64syntax_matchSING_IMM(list));
	if (mode & M_REG_IMM)
		return (c64syntax_matchREG_IMM(list));
	if (mode & M_REG_REG)
		return (c64syntax_matchREG_REG(list));
	if (mode & M_SYM)
		return (c64syntax_matchSYM(list));
	fatal("c64syntax_parseMode: invalid addressing mode %d", mode);
	return (NULL);
}

struct c64instruction	*c64syntax_matchSING_REG(struct c64tokenlist *list)
{
	struct c64instruction	*instruction;

	c64syntax_matchRegister(list);
	instruction = malloc(sizeof(struct c64instruction));
	instruction->type = list->token->type;
	instruction->mode = M_SING_REG;
	instruction->opcode = c64syntax_getOpcode(list->token->type);
	instruction->operands[0] = malloc(sizeof(struct c64operand));
	instruction->operands[0]->type = T_REG;
	instruction->operands[0]->value = c64syntax_getRegister(list->token->str);
	return (instruction);
}

struct c64instruction	*c64syntax_matchSING_IMM(struct c64tokenlist *list)
{
	struct c64instruction	*instruction;

	c64syntax_matchImmediate(list);
	instruction = malloc(sizeof(struct c64instruction));
	instruction->type = list->token->type;
	instruction->mode = M_SING_IMM;
	instruction->opcode = c64syntax_getOpcode(list->token->type);
	instruction->operands[0] = malloc(sizeof(struct c64operand));
	instruction->operands[0]->type = T_IMM;
	instruction->operands[0]->value = list->token->val;
	return (instruction);
}

struct c64instruction	*c64syntax_matchREG_IMM(struct c64tokenlist *list)
{
	struct c64instruction	*instruction;

	if (!c64syntax_isRegister(list))
		return (NULL);
	instruction = malloc(sizeof(struct c64instruction));
	instruction->type = list->token->type;
	instruction->mode = M_REG_IMM;
	instruction->opcode = c64syntax_getOpcode(list->token->type);
	instruction->operands[0] = malloc(sizeof(struct c64operand));
	instruction->operands[0]->type = T_REG;
	instruction->operands[0]->value = c64syntax_getRegister(list->token->str);
	list = c64syntax_nextToken(list);
	if (!c64syntax_isComma(list))
		return (NULL);
	list = c64syntax_nextToken(list);
	if (!c64syntax_isImmediate(list))
		return (NULL);
	instruction->operands[1] = malloc(sizeof(struct c64operand));
	instruction->operands[1]->type = T_IMM;
	instruction->operands[1]->value = list->token->val;
	return (instruction);
}

struct c64instruction	*c64syntax_matchREG_REG(struct c64tokenlist *list)
{
	struct c64instruction	*instruction;

	if (!c64syntax_isRegister(list))
		return (NULL);
	instruction = malloc(sizeof(struct c64instruction));
	instruction->type = list->token->type;
	instruction->mode = M_REG_REG;
	instruction->opcode = c64syntax_getOpcode(list->token->type);
	instruction->operands[0] = malloc(sizeof(struct c64operand));
	instruction->operands[0]->type = T_REG;
	instruction->operands[0]->value = c64syntax_getRegister(list->token->str);
	list = c64syntax_nextToken(list);
	if (!c64syntax_isComma(list))
		return (NULL);
	list = c64syntax_nextToken(list);
	if (!c64syntax_isRegister(list))
		return (NULL);
	instruction->operands[1] = malloc(sizeof(struct c64operand));
	instruction->operands[1]->type = T_REG;
	instruction->operands[1]->value = c64syntax_getRegister(list->token->str);
	return (instruction);
}

struct c64instruction	*c64syntax_matchNONE(struct c64tokenlist *list)
{
	struct c64instruction	*instruction;

	instruction = malloc(sizeof(struct c64instruction));
	instruction->type = list->token->type;
	instruction->mode = M_NONE;
	instruction->opcode = c64syntax_getOpcode(list->token->type);
	return (instruction);
}

struct c64instruction	*c64syntax_matchSYM(struct c64tokenlist *list)
{
	struct c64instruction	*instruction;

	if (!c64syntax_isLabelRef(list))
		return (NULL);
	instruction = malloc(sizeof(struct c64instruction));
	instruction->type = list->token->type;
	instruction->mode = M_SYM;
	instruction->opcode = c64syntax_getOpcode(list->token->type);
	instruction->operands[0] = malloc(sizeof(struct c64operand));
	instruction->operands[0]->type = T_LABEL;
	instruction->operands[0]->value = list->token->val;
	return (instruction);
}

struct c64instruction	*c64syntax_matchSING_IMM_SYM(struct c64tokenlist *list)
{
	struct c64instruction	*instruction;
	int						isImmediate;

	if (!c64syntax_isImmediate(list) && !c64syntax_isLabelRef(list))
		return (NULL);
	isImmediate = c64syntax_isImmediate(list);
	instruction = malloc(sizeof(struct c64instruction));
	instruction->type = list->token->type;
	instruction->mode = isImmediate ? M_SING_IMM : M_SYM;
	instruction->opcode = c64syntax_getOpcode(list->token->type);
	instruction->operands[0] = malloc(sizeof(struct c64operand));
	instruction->operands[0]->type = isImmediate ? T_IMM : T_LABEL;
	instruction->operands[0]->value = list->token->val;
	return (instruction);
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