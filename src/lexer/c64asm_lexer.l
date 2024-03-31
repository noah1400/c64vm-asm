%{
#include "y.tab.h"
int line_no = 1;
%}

/* Token definitions  */
LDI "LDI"
ST "ST"

PUSH "PUSH"
POP "POP"

LABEL ":"[a-zA-Z_][a-zA-Z0-9_]*

NUMBER  \$[0-9]+
HEX     #[0-9a-fA-F]+
REGISTER [rR][0-9]+
COMMENT ";"[^\n]*
EOL \n

%%

{LDI} { return LDI; }
{ST} { return ST; }

{PUSH} { return PUSH; }
{POP} { return POP; }

{LABEL} { yylval.str = strdup(yytext+1); return LABEL; }

{NUMBER} { yylval.num = atoi(yytext+1); return NUMBER; }
{HEX} { yylval.num = strtol(yytext+1, NULL, 16); return NUMBER; }
{REGISTER} { yylval.num = atoi(yytext+1); return REGISTER; }
{COMMENT} { yylval.str = strdup(yytext); return COMMENT;}

{EOL} { line_no++; return EOL; }

[ \t]+ { /* ignore whitespace */ }

. { return yytext[0]; }

%%