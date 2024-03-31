%{
#include "y.tab.h"
int line_no = 1;
%}

/* Token definitions  */
LDI "LDI"
ST "ST"

PUSH "PUSH"
POP "POP"

JMP "JMP"

NUMBER  \$[0-9]+
HEX     #[0-9a-fA-F]+
REGISTER [rR][0-9]+
COMMENT ";"[^\n]*
EOL \n

LABEL_REF [a-zA-Z_][a-zA-Z0-9_]*
LABEL_DEF ":"[a-zA-Z_][a-zA-Z0-9_]*

%%

{LDI} { return LDI; }
{ST} { return ST; }

{PUSH} { return PUSH; }
{POP} { return POP; }

{JMP} { return JMP; }


{NUMBER} { yylval.num = atoi(yytext+1); return NUMBER; }
{HEX} { yylval.num = strtol(yytext+1, NULL, 16); return NUMBER; }
{REGISTER} { yylval.num = atoi(yytext+1); return REGISTER; }
{COMMENT} { yylval.str = strdup(yytext); return COMMENT;}

{LABEL_DEF} { yylval.str = strdup(yytext+1); return LABEL_DEF; }
{LABEL_REF} { yylval.str = strdup(yytext); return LABEL_REF; }

{EOL} { line_no++; return EOL; }

[ \t]+ { /* ignore whitespace */ }

. { return yytext[0]; }

%%