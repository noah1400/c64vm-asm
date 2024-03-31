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
%token <num> LDI 
%token <num> ST
%token <num> PUSH
%token <num> POP
%token <num> EOL
%token <num> JMP
%token <str> COMMENT

%token <str> LABEL_DEF
%token <str> LABEL_REF

%type <num> immediate
%type <str> opt_comment

%%

c64asm: 
    | c64asm line opt_comment EOL
    | c64asm error EOL { printf("Error on line %d\n", line_no); }
    ;

line: 
    | instruction
    | LABEL_DEF { printf(":%s\n", $1);}
    ;

opt_comment:  { $$ = ""; } 
    | COMMENT { $$ = $1; }
    ;

instruction: LDI REGISTER ',' immediate { printf("0x%04lx r%d, %d\n", OP_LDI, $2, $4); }
    | ST REGISTER ',' immediate { printf("0x%04lx r%d, %d\n", OP_ST, $2, $4); }
    | PUSH REGISTER { printf("PUSH r%d\n", $2); }
    | POP REGISTER { printf("POP r%d\n", $2); }
    | JMP LABEL_REF { printf("JMP %s\n", $2); }
    ;

immediate: NUMBER { $$ = $1; }
    | HEX { $$ = $1; }
    ;

%%
