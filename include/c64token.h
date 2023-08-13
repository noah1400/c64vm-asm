#ifndef _c64token_h_
#define _c64token_h_

#include <stdio.h>
#include <string.h>
#include <c64utils.h>

#define TEXT_LEN 1024 // max length of identifier

extern struct c64token Token;
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
};

struct c64token {
    int type;
    char *str;
    int val;
    int len;
    int line;
    int pos;
};

void c64token_putback(char c);
int c64token_chrpos(char *s, char c);
char c64token_next(void);
char c64token_skip(void);
int c64token_scanint(char c);
int c64token_scanhex(char c);
int c64token_scanident(char c, char *buf, int lim);
char c64token_scan(struct c64token *t);
int c64token_lookup(char *s);

#endif // _c64token_h_