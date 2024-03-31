#include "lex.yy.c"

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    #if YYDEBUG
        yydebug = 1;
    #endif

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