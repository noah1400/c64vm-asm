%{
#include "y.tab.h"
#include <stdlib.h>
#include <stdint.h>
int line_no = 1;
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

{REF}    { return REF; }
{DEF}    { return DEF; }

{LDI}    { return LDI; }
{ST}     { return ST; }
{PUSH}   { return PUSH; }
{POP}    { return POP; }
{JMP}    { return JMP; }

{LDBI}   { return LDBI; }
{LDWI}   { return LDWI; }
{LDDI}   { return LDDI; }
{LDM}    { return LDM; }
{LDBM}   { return LDBM; }
{LDWM}   { return LDWM; }
{LDDM}   { return LDDM; }
{STB}    { return STB; }
{STW}    { return STW; }
{STD}    { return STD; }
{TF}     { return TF; }

{ADDI}   { return ADDI; }
{SUBI}   { return SUBI; }
{MULI}   { return MULI; }
{DIVI}   { return DIVI; }
{MODI}   { return MODI; }
{MULIS}  { return MULIS; }
{DIVIS}  { return DIVIS; }

{ADD}    { return ADD; }
{SUB}    { return SUB; }
{MUL}    { return MUL; }
{DIV}    { return DIV; }
{MOD}    { return MOD; }
{MULS}   { return MULS; }
{DIVS}   { return DIVS; }

{ANDI}   { return ANDI; }
{ORI}    { return ORI; }
{XORI}   { return XORI; }
{NOTI}   { return NOTI; }
{SHLI}   { return SHLI; }
{SHRI}   { return SHRI; }
{RORI}   { return RORI; }
{ROLI}   { return ROLI; }

{AND}    { return AND; }
{OR}     { return OR; }
{XOR}    { return XOR; }
{NOT}    { return NOT; }
{SHL}    { return SHL; }
{SHR}    { return SHR; }
{ROR}    { return ROR; }
{ROL}    { return ROL; }

{CMP}    { return CMP; }
{CMPI}   { return CMPI; }

{JEQ}    { return JEQ; }
{JNE}    { return JNE; }
{JGT}    { return JGT; }
{JLT}    { return JLT; }
{JGE}    { return JGE; }
{JLE}    { return JLE; }

{BRAR}   { return BRAR; }
{BEQR}   { return BEQR; }
{BNER}   { return BNER; }
{BGTR}   { return BGTR; }
{BLTR}   { return BLTR; }
{BGER}   { return BGER; }
{BLER}   { return BLER; }

{RET}    { return RET; }

{PUSHI}  { return PUSHI; }

{CALL}   { return CALL; }
{CALLR}  { return CALLR; }
{RTC}    { return RTC; }

{CLC}    { return CLC; }
{SEC}    { return SEC; }
{CLZ}    { return CLZ; }
{SEZ}    { return SEZ; }
{CLN}    { return CLN; }
{SEN}    { return SEN; }
{CLV}    { return CLV; }
{SEV}    { return SEV; }
{CLI}    { return CLI; }
{SEI}    { return SEI; }

{INT}    { return INT; }
{RTI}    { return RTI; }

{NOP}    { return NOP; }
{HLT}    { return HLT; }

{NUMBER} { yylval.imm = strtoull(yytext+1, NULL, 10); return NUMBER; }
{HEX} { yylval.imm = strtoull(yytext+1, NULL, 16); return NUMBER; }
{REGISTER} { yylval.byte = (uint8_t)strtoul(yytext+1, NULL, 10); return REGISTER; }
{COMMENT} { yylval.str = strdup(yytext); return COMMENT;}

{LABEL_DEF} { yylval.str = strdup(yytext+1); return LABEL_DEF; }
{LABEL_REF} { yylval.str = strdup(yytext); return LABEL_REF; }

{EOL} { line_no++; return EOL; }

[ \t]+ { /* ignore whitespace */ }

. { return yytext[0]; }

%%
