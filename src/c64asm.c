#include "lex.yy.c"
#include <c64asm_symbols.h>
#include <c64asm_ast.h>
#include <c64asm_gen.h>
#include <c64asm_link.h>

SymbolTable *current_table = NULL;
ASTNode *current_ast = NULL;
c64linker_t *global_linker = NULL;

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

    global_linker = c64linker_create();

    c64link_OBJ_t *obj = c64linker_create_object(argv[1]);

    obj->symtab = symbol_table_init(argv[1]);
    current_table = obj->symtab;
    current_ast = obj->ast;

    int parse_result = yyparse();
    fclose(yyin);
    
    if (parse_result) {
        fprintf(stderr, "Parse failed\n");
        return 1;
    }

    obj->ast = current_ast;

    c64linker_add_object(global_linker, obj);

    symbol_table_print(current_table);
    c64linker_link(global_linker);
    ast_print(current_ast);
    // c64gen_gen(current_ast, "out.bin", current_table);
    c64linker_free(global_linker);
    return 0;
}

void yyerror(char *s) {
    if (strcmp(s, "syntax error") == 0) {
        fprintf(stderr, "Fehler in Zeile %d: Unerwartetes Symbol '%s'\n", line_no, yytext);
    } else {
        fprintf(stderr, "Fehler in Zeile %d: %s\n", line_no, s);
    }
}