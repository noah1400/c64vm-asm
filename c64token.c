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
#include <c64token.h>

struct c64token *c64token_copy(struct c64token *t)
{
	struct c64token *newToken;

	newToken = (struct c64token *)malloc(sizeof(struct c64token));
	if (newToken == NULL)
	{
		c64utils_fatal("failed to maloc() in c64token_createToken()");
	}
	newToken->type = t->type;
	strcpy(newToken->str, t->str);
	newToken->val = t->val;
	newToken->len = t->len;
	newToken->line = t->line;
	newToken->pos = t->pos;
	return (newToken);
}

void c64token_putback(char c)
{
	Putback = c;
	Pos--;
}

int c64token_chrpos(char *s, char c)
{
	char *p;

	p = strchr(s, c);
	return (p ? p - s : -1);
}

char c64token_next(void)
{
	char c;

	if (Putback)
	{
		c = Putback;
		Putback = '\0';
		return (c);
	}
	c = fgetc(Infile);
	if (c == '\n')
	{
		Line++;
		Pos = 1;
	}
	else
	{
		Pos++;
	}
	return (c);
}

char c64token_skip(void)
{
	char c;

	c = c64token_next();
	while (' ' == c || '\t' == c || '\n' == c || '\r' == c || '\f' == c)
	{
		c = c64token_next();
	}
	return (c);
}

size_t c64token_scanint(char c)
{
	size_t val;
	int k;
	char f;

	val = 0;
	f = 0;
	while ((k = c64token_chrpos("0123456789", c)) >= 0)
	{
		val = val * 10 + k;
		c = c64token_next();
		f = 1;
	}
	if (!f)
	{
		c64utils_fatal("integer expected");
	}
	c64token_putback(c);
	return (val);
}

size_t c64token_scanhex(char c)
{
	size_t val;
	int k;
	char f;

	val = 0;
	f = 0;
	while ((k = c64token_chrpos("0123456789ABCDEF", c64utils_toupper(c))) >= 0)
	{
		val = val * 16 + k;
		c = c64token_next();
		f = 1;
	}
	if (!f)
	{
		c64utils_fatal("hexadecimal number expected");
	}
	c64token_putback(c);
	return (val);
}

int c64token_scanident(char c, char *buf, int lim)
{
	int i;

	i = 0;
	while (isalpha(c) || isdigit(c) || '_' == c)
	{
		if (lim - 1 == i)
		{
			c64utils_fatal("identifier too long");
		}
		else if (i < lim - 1)
		{
			buf[i++] = c;
		}
		c = c64token_next();
	}
	if (i == 0)
	{
		c64utils_fatal("identifier expected");
	}
	c64token_putback(c);
	buf[i] = '\0';
	return (i);
}

char c64token_scan(struct c64token *t)
{
	char c, type;
	c = c64token_skip();
	switch (c)
	{
	case EOF:
		t->type = T_EOF;
		t->line = Line;
		t->pos = Pos;
		strcpy(t->str, "EOF");
		t->len = 3;
		t->val = 0;
		break;
	case ';':
		// comment
		while (c64token_next() != '\n')
		{
			;
		}
		return (c64token_scan(t));
	case '!':
		c = c64token_next();
		c64token_scanident(c, Text, TEXT_LEN);
		strcpy(t->str, Text);
		t->line = Line;
		t->pos = Pos;
		t->len = strlen(Text);
		t->type = T_VAR;
		t->val = 0;
		break;
	case ':':
		c = c64token_next();
		c64token_scanident(c, Text, TEXT_LEN);
		strcpy(t->str, Text);
		t->line = Line;
		t->pos = Pos;
		t->len = strlen(Text);
		t->type = T_LABEL;
		t->val = 0;
		break;
	case ',':
		t->type = T_COMMA;
		t->line = Line;
		t->pos = Pos;
		strcpy(t->str, ",");
		t->len = 1;
		t->val = 0;
		break;
	case '{':
		t->type = T_LBRACE;
		t->line = Line;
		t->pos = Pos;
		strcpy(t->str, "{");
		t->len = 1;
		t->val = 0;
		break;
	case '}':
		t->type = T_RBRACE;
		t->line = Line;
		t->pos = Pos;
		strcpy(t->str, "}");
		t->len = 1;
		t->val = 0;
		break;
	case '$':
		t->type = T_IMM;
		t->line = Line;
		t->pos = Pos;
		strcpy(t->str, "$");
		t->len = 1;
		t->val = c64token_scanhex(c64token_next());
		break;
	case '#':
		t->type = T_IMM;
		t->line = Line;
		t->pos = Pos;
		strcpy(t->str, "#");
		t->len = 1;
		t->val = c64token_scanint(c64token_next());
		break;
	default:
		if (isalpha(c) || '_' == c)
		{
			c64token_scanident(c, Text, TEXT_LEN);
			strcpy(t->str, Text);
			t->line = Line;
			t->pos = Pos;
			t->len = strlen(Text);
			type = c64token_lookup(Text);
			if (type)
			{
				t->type = type;
				t->val = type == T_INST ? c64token_mapInstruction(Text) : c64token_mapRegister(Text);
			}
			else
			{
				t->type = T_IDENT;
				t->val = 0;
			}
			break;
		}
		c64utils_fatalc("unknown character", c);
	}
	return (1);
}

int c64token_lookupRegister(char *s)
{
	int i;

	for (i = 0; i < REGISTER_COUNT; i++)
	{
		if (0 == strcmp(Registers[i], s))
		{
			return (T_REG);
		}
	}
	return (0);
}

int c64token_lookupInstruction(char *s)
{
	int i;

	char *instructions[94] = {"LDI", "LDBI", "LDWI", "LDDI", "LDM", "LDBM",
							  "LDWM", "LDDM", "ST", "STB", "STW", "STD", "TF", "ADDI", "SUBI", "MULI",
							  "DIVI", "MODI", "MULIS", "DIVIS", "ADD", "SUB", "MUL", "DIV", "MOD",
							  "MULS", "DIVS", "ANDI", "ORI", "XORI", "NOTI", "SHLI", "SHRI", "RORI",
							  "ROLI", "AND", "OR", "XOR", "NOT", "SHL", "SHR", "ROR", "ROL", "CMP",
							  "CMPI", "JMP", "JEQ", "JNE", "JGT", "JLT", "JGE", "JLE", "BRA", "BEQ",
							  "BNE", "BGT", "BLT", "BGE", "BLE", "JMPR", "JEQR", "JNER", "JGTR",
							  "JLTR", "JGER", "JLER", "BRAR", "BEQR", "BNER", "BGTR", "BLTR", "BGER",
							  "BLER", "RET", "PUSH", "PUSHI", "POP", "CALL", "CALLR", "RTC", "CLC",
							  "SEC", "CLZ", "SEZ", "CLN", "SEN", "CLV", "SEV", "CLI", "SEI", "INT",
							  "RTI", "NOP", "HLT"};
	for (i = 0; i < 94; i++)
	{
		if (0 == strcmp(instructions[i], s))
		{
			return (T_INST);
		}
	}
	return (0);
}

int c64token_lookup(char *s)
{
	int type;

	if ((type = c64token_lookupRegister(s)))
	{
		return (type);
	}
	else if ((type = c64token_lookupInstruction(s)))
	{
		return (type);
	}
	return (0);
}

void c64token_print(struct c64token *t)
{
	printf("%s (%d) at %d:%d: %s", c64token_typestr(t->type), t->type, t->line,
		   t->pos, t->str);
	if (T_IMM == t->type)
	{
		printf(" ($%016llX)", t->val);
	}
	else
	{
		printf(" (%lld)", t->val);
	}
	printf("\n");
}

int c64token_mapInstruction(char *s)
{
	// Order is important !
	char *instructions[94] = {"LDI", "LDBI", "LDWI", "LDDI", "LDM", "LDBM",
							  "LDWM", "LDDM", "ST", "STB", "STW", "STD", "TF", "ADDI", "SUBI", "MULI",
							  "DIVI", "MODI", "MULIS", "DIVIS", "ADD", "SUB", "MUL", "DIV", "MOD",
							  "MULS", "DIVS", "ANDI", "ORI", "XORI", "NOTI", "SHLI", "SHRI", "RORI",
							  "ROLI", "AND", "OR", "XOR", "NOT", "SHL", "SHR", "ROR", "ROL", "CMP",
							  "CMPI", "JMP", "JEQ", "JNE", "JGT", "JLT", "JGE", "JLE", "BRA", "BEQ",
							  "BNE", "BGT", "BLT", "BGE", "BLE", "JMPR", "JEQR", "JNER", "JGTR",
							  "JLTR", "JGER", "JLER", "BRAR", "BEQR", "BNER", "BGTR", "BLTR", "BGER",
							  "BLER", "RET", "PUSH", "PUSHI", "POP", "CALL", "CALLR", "RTC", "CLC",
							  "SEC", "CLZ", "SEZ", "CLN", "SEN", "CLV", "SEV", "CLI", "SEI", "INT",
							  "RTI", "NOP", "HLT"};
	for (int i = 0; i < 94; i++)
	{
		if (0 == strcmp(instructions[i], s))
		{
			return (i);
		}
	}
	return (0);
}

int c64token_mapRegister(char *s)
{
	int i;

	for (i = 0; i < REGISTER_COUNT; i++)
	{
		if (0 == strcmp(Registers[i], s))
		{
			return (i);
		}
	}
	return (0);
}

char *c64token_typestr(int type)
{
	switch (type)
	{
	case T_EOF:
		return ("T_EOF");
	case T_COLON:
		return ("T_COLON");
	case T_COMMA:
		return ("T_COMMA");
	case T_LBRACE:
		return ("T_LBRACE");
	case T_RBRACE:
		return ("T_RBRACE");
	case T_IMM:
		return ("T_IMM");
	case T_REG:
		return ("T_REG");
	case T_IDENT:
		return ("T_IDENT");
	case T_INST:
		return ("T_INST");
	case T_LABEL:
		return ("T_LABEL");
	case T_VAR:
		return ("T_VAR");
	default:
		return ("T_UNKNOWN");
	}
}