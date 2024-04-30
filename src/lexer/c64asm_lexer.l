%{
#include "y.tab.h"
#include <stdlib.h>
#include <stdint.h>
int line_no = 1;
int error_count = 0;
char *current_line = NULL;

void addToLine(char *str) {
    if (current_line == NULL) {
        current_line = strdup(str);
    } else {
        current_line = realloc(current_line, strlen(current_line) + strlen(str) + 1);
        strcat(current_line, str);
    }
}
%}

%option noyywrap

REF     "REF"
DEF     "DEF"

/* Token definitions for existing opcodes */
LDI     "LDI"
ST      "ST"
PUSH    "PUSH"
POP     "POP"
JMP     "JMP"

LDBI    "LDBI"
LDWI    "LDWI"
LDDI    "LDDI"
LDM     "LDM"
LDBM    "LDBM"
LDWM    "LDWM"
LDDM    "LDDM"
STB     "STB"
STW     "STW"
STD     "STD"
TF      "TF"

ADDI    "ADDI"
SUBI    "SUBI"
MULI    "MULI"
DIVI    "DIVI"
MODI    "MODI"
MULIS   "MULIS"
DIVIS   "DIVIS"

ADD     "ADD"
SUB     "SUB"
MUL     "MUL"
DIV     "DIV"
MOD     "MOD"
MULS    "MULS"
DIVS    "DIVS"

ANDI    "ANDI"
ORI     "ORI"
XORI    "XORI"
NOTI    "NOTI"
SHLI    "SHLI"
SHRI    "SHRI"
RORI    "RORI"
ROLI    "ROLI"

AND     "AND"
OR      "OR"
XOR     "XOR"
NOT     "NOT"
SHL     "SHL"
SHR     "SHR"
ROR     "ROR"
ROL     "ROL"

CMP     "CMP"
CMPI    "CMPI"

JEQ     "JEQ"
JNE     "JNE"
JGT     "JGT"
JLT     "JLT"
JGE     "JGE"
JLE     "JLE"

BRA     "BRA"
BRAR    "BRAR"
BEQR    "BEQR"
BNER    "BNER"
BGTR    "BGTR"
BLTR    "BLTR"
BGER    "BGER"
BLER    "BLER"

RET     "RET"

PUSHI   "PUSHI"

CALL    "CALL"
CALLR   "CALLR"
RTC     "RTC"

CLC     "CLC"
SEC     "SEC"
CLZ     "CLZ"
SEZ     "SEZ"
CLN     "CLN"
SEN     "SEN"
CLV     "CLV"
SEV     "SEV"
CLI     "CLI"
SEI     "SEI"

INT     "INT"
RTI     "RTI"

NOP     "NOP"
HLT     "HLT"

NUMBER  \$[0-9]+
HEX     #[0-9a-fA-F]+
REGISTER [rR][0-8]
COMMENT ";"[^\n]*
EOL \n

LABEL_REF [a-zA-Z_][a-zA-Z0-9_]*
LABEL_DEF ":"[a-zA-Z_][a-zA-Z0-9_]*

%%

{REF}    { addToLine(yytext);return REF; }
{DEF}    { addToLine(yytext);return DEF; }

{LDI}    { addToLine(yytext);return LDI; }
{ST}     { addToLine(yytext);return ST; }
{PUSH}   { addToLine(yytext);return PUSH; }
{POP}    { addToLine(yytext);return POP; }
{JMP}    { addToLine(yytext);return JMP; }

{LDBI}   { addToLine(yytext);return LDBI; }
{LDWI}   { addToLine(yytext);return LDWI; }
{LDDI}   { addToLine(yytext);return LDDI; }
{LDM}    { addToLine(yytext);return LDM; }
{LDBM}   { addToLine(yytext);return LDBM; }
{LDWM}   { addToLine(yytext);return LDWM; }
{LDDM}   { addToLine(yytext);return LDDM; }
{STB}    { addToLine(yytext);return STB; }
{STW}    { addToLine(yytext);return STW; }
{STD}    { addToLine(yytext);return STD; }
{TF}     { addToLine(yytext);return TF; }

{ADDI}   { addToLine(yytext);return ADDI; }
{SUBI}   { addToLine(yytext);return SUBI; }
{MULI}   { addToLine(yytext);return MULI; }
{DIVI}   { addToLine(yytext);return DIVI; }
{MODI}   { addToLine(yytext);return MODI; }
{MULIS}  { addToLine(yytext);return MULIS; }
{DIVIS}  { addToLine(yytext);return DIVIS; }

{ADD}    { addToLine(yytext);return ADD; }
{SUB}    { addToLine(yytext);return SUB; }
{MUL}    { addToLine(yytext);return MUL; }
{DIV}    { addToLine(yytext);return DIV; }
{MOD}    { addToLine(yytext);return MOD; }
{MULS}   { addToLine(yytext);return MULS; }
{DIVS}   { addToLine(yytext);return DIVS; }

{ANDI}   { addToLine(yytext);return ANDI; }
{ORI}    { addToLine(yytext);return ORI; }
{XORI}   { addToLine(yytext);return XORI; }
{NOTI}   { addToLine(yytext);return NOTI; }
{SHLI}   { addToLine(yytext);return SHLI; }
{SHRI}   { addToLine(yytext);return SHRI; }
{RORI}   { addToLine(yytext);return RORI; }
{ROLI}   { addToLine(yytext);return ROLI; }

{AND}    { addToLine(yytext);return AND; }
{OR}     { addToLine(yytext);return OR; }
{XOR}    { addToLine(yytext);return XOR; }
{NOT}    { addToLine(yytext);return NOT; }
{SHL}    { addToLine(yytext);return SHL; }
{SHR}    { addToLine(yytext);return SHR; }
{ROR}    { addToLine(yytext);return ROR; }
{ROL}    { addToLine(yytext);return ROL; }

{CMP}    { addToLine(yytext);return CMP; }
{CMPI}   { addToLine(yytext);return CMPI; }

{JEQ}    { addToLine(yytext);return JEQ; }
{JNE}    { addToLine(yytext);return JNE; }
{JGT}    { addToLine(yytext);return JGT; }
{JLT}    { addToLine(yytext);return JLT; }
{JGE}    { addToLine(yytext);return JGE; }
{JLE}    { addToLine(yytext);return JLE; }

{BRA}    { addToLine(yytext);return BRA; }
{BRAR}   { addToLine(yytext);return BRAR; }
{BEQR}   { addToLine(yytext);return BEQR; }
{BNER}   { addToLine(yytext);return BNER; }
{BGTR}   { addToLine(yytext);return BGTR; }
{BLTR}   { addToLine(yytext);return BLTR; }
{BGER}   { addToLine(yytext);return BGER; }
{BLER}   { addToLine(yytext);return BLER; }

{RET}    { addToLine(yytext);return RET; }

{PUSHI}  { addToLine(yytext);return PUSHI; }

{CALL}   { addToLine(yytext);return CALL; }
{CALLR}  { addToLine(yytext);return CALLR; }
{RTC}    { addToLine(yytext);return RTC; }

{CLC}    { addToLine(yytext);return CLC; }
{SEC}    { addToLine(yytext);return SEC; }
{CLZ}    { addToLine(yytext);return CLZ; }
{SEZ}    { addToLine(yytext);return SEZ; }
{CLN}    { addToLine(yytext);return CLN; }
{SEN}    { addToLine(yytext);return SEN; }
{CLV}    { addToLine(yytext);return CLV; }
{SEV}    { addToLine(yytext);return SEV; }
{CLI}    { addToLine(yytext);return CLI; }
{SEI}    { addToLine(yytext);return SEI; }

{INT}    { addToLine(yytext);return INT; }
{RTI}    { addToLine(yytext);return RTI; }

{NOP}    { addToLine(yytext);return NOP; }
{HLT}    { addToLine(yytext);return HLT; }

{NUMBER} { addToLine(yytext);yylval.imm = strtoull(yytext+1, NULL, 10); return NUMBER; }
{HEX} { addToLine(yytext);yylval.imm = strtoull(yytext+1, NULL, 16); return NUMBER; }
{REGISTER} { addToLine(yytext);yylval.byte = (uint8_t)strtoul(yytext+1, NULL, 10); return REGISTER; }
{COMMENT} { addToLine(yytext);yylval.str = strdup(yytext); return COMMENT;}

{LABEL_DEF} { addToLine(yytext);yylval.str = strdup(yytext+1); return LABEL_DEF; }
{LABEL_REF} { addToLine(yytext);yylval.str = strdup(yytext); return LABEL_REF; }

{EOL} { 
    line_no++;
    if (current_line){
    yylval.str = strdup(current_line);
    free(current_line);
    current_line = NULL;
    }else{
        yylval.str = strdup("");
    }
    return EOL; 
}

[ \t]+ { addToLine(yytext); }

. { return yytext[0]; }

%%
