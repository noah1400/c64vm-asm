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
#include <c64asm.h>
#include <c64token.h>

struct c64token	Token;
char			*Registers[REGISTER_COUNT];
char			Text[TEXT_LEN + 1];
char			Putback;
int				Line;
int				Pos;
FILE			*Infile;
FILE			*Outfile;

void	c64asm_init(void)
{
	struct c64token	t;

	t = (struct c64token){0};
	Token = t;
	Putback = '\n';
	Line = 1;
	Pos = 1;
	// Order of registers is important
	Registers[0] = "ACC";
	Registers[1] = "IP";
	Registers[2] = "SP";
	Registers[3] = "FP";
	Registers[4] = "MB";
	Registers[5] = "IM";
	Registers[6] = "R1";
	Registers[7] = "R2";
	Registers[8] = "R3";
	Registers[9] = "R4";
	Registers[10] = "R5";
	Registers[11] = "R6";
	Registers[12] = "R7";
	Registers[13] = "R8";
	Infile = NULL;
	Outfile = NULL;
}

int	main(int argc, char *argv[])
{
	c64asm_init();
	if (argc < 2)
	{
		c64utils_fatal("no input file");
	}
	if (argc < 3)
	{
		c64utils_fatal("no output file");
	}
	Infile = fopen(argv[1], "r");
	if (!Infile)
	{
		c64utils_fatal("cannot open input file");
	}
	Outfile = fopen(argv[2], "w");
	if (!Outfile)
	{
		c64utils_fatal("cannot open output file");
	}
	struct c64tokenlist *tokens = c64tokenize();
	c64tokenlist_print(tokens);

	fclose(Infile);
	fclose(Outfile);

	c64tokenlist_free(tokens);

	return (0);
}