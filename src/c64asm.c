#include "lex.yy.c"
#include <c64asm_symbols.h>
#include <c64asm_ast.h>
#include <c64asm_gen.h>

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

    symbol_table_init();

    int parse_result = yyparse();
    fclose(yyin);
    
    if (parse_result) {
        fprintf(stderr, "Parse failed\n");
        return 1;
    }

    symbol_table_print(symbol_table);
    ast_print(ast_head);
    c64gen_gen(ast_head, "out.bin");
    symbol_table_free(symbol_table);
    ast_free(ast_head);

    return 0;
}

void yyerror(char *s) {
    if (strcmp(s, "syntax error") == 0) {
        fprintf(stderr, "Fehler in Zeile %d: Unerwartetes Symbol '%s'\n", line_no, yytext);
    } else {
        fprintf(stderr, "Fehler in Zeile %d: %s\n", line_no, s);
    }
}