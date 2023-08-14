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
#ifndef _c64token_h_
#define _c64token_h_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <c64utils.h>

#define TEXT_LEN 1024 // max length of identifier
#define REGISTER_COUNT 14

extern struct c64token Token;
extern char *Registers[REGISTER_COUNT];
extern char Text[TEXT_LEN + 1]; // Last identifier read
extern char Putback;
extern int Line;
extern int Pos;
extern FILE *Infile;
extern FILE *Outfile;


enum {
    T_EOF,
    T_REG,
    T_IMM,
    T_INST,
    T_LABEL,
    T_COMMA, T_COLON,
    T_RBRACE, T_LBRACE,
    T_IDENT,
    T_VAR
};

char *c64token_typestr(int type);

struct c64token {
    int type;
    char str[100];
    size_t val;
    int len;
    int line;
    int pos;
};

void c64token_putback(char c);
int c64token_chrpos(char *s, char c);
char c64token_next(void);
char c64token_skip(void);
size_t c64token_scanint(char c);
size_t c64token_scanhex(char c);
int c64token_scanident(char c, char *buf, int lim);
char c64token_scan(struct c64token *t);
int c64token_lookup(char *s);
struct c64token *c64token_copy(struct c64token *t);

void c64token_print(struct c64token *t);

#endif // _c64token_h_