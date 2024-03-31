%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <c64asm_opcodes.h>
    extern int line_no;
%}

%union {
    char *str;
    int num;
}

%token <num> NUMBER 
%token <num> HEX
%token <num> REGISTER
%token <num> LDI 1
%token <num> ST
%token <num> PUSH
%token <num> POP
%token <num> EOL
%token <str> COMMENT

%token <str> LABEL

%type <num> immediate
%type <str> opt_comment

%%

c64asm: /* empty */
    | c64asm line opt_comment EOL
    ;

line: /* empty */
    | instruction
    | LABEL { printf(":%s\n", $1);}
    ;

opt_comment: /* empty */ { $$ = ""; } 
    | COMMENT { $$ = $1; }
    ;

instruction: LDI REGISTER ',' immediate { printf("0x%04lx r%d, %d\n", OP_LDI, $2, $4); }
    | ST REGISTER ',' immediate { printf("0x%04lx r%d, %d\n", OP_ST, $2, $4); }
    | PUSH REGISTER { printf("PUSH r%d\n", $2); }
    | POP REGISTER { printf("POP r%d\n", $2); }
    ;

immediate: NUMBER { $$ = $1; }
    | HEX { $$ = $1; }
    ;

%%
#include "lex.yy.c"

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror(argv[1]);
        return 1;
    }

    int parse_result = yyparse();
    fclose(yyin);
    
    if (parse_result) {
        fprintf(stderr, "Parse failed\n");
        return 1;
    }

    return 0;
}

void yyerror(char *s) {
    if (strcmp(s, "syntax error") == 0) {
        fprintf(stderr, "Fehler in Zeile %d: Unerwartetes Symbol '%s'\n", line_no, yytext);
    } else {
        fprintf(stderr, "Fehler in Zeile %d: %s\n", line_no, s);
    }
}