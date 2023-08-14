/*
Copyright (c) 2023 Noah Scholz

This file is part of the c64asm project.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
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