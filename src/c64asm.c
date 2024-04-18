#include "lex.yy.c"
#include <c64asm_symbols.h>
#include <c64asm_ast.h>
#include <c64asm_gen.h>
#include <c64asm_link.h>

SymbolTable *current_table = NULL;
ASTNode *current_ast = NULL;
c64linker_t *global_linker = NULL;

char *current_filename = NULL;

int main(int argc, char **argv)
{

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

#if YYDEBUG
    yydebug = 1;
#endif

    global_linker = c64linker_create();

    for (int i = 1; i < argc; i++)
    {
        printf("Parsing %s\n\n", argv[i]);
        current_filename = argv[i];
        yyin = fopen(argv[i], "r");
        if (!yyin)
        {
            perror(argv[i]);
            return 1;
        }

        c64link_OBJ_t *obj = c64linker_create_object(argv[i]);

        obj->symtab = symbol_table_init(argv[i]);
        current_table = obj->symtab;

        int parse_result = yyparse();
        fclose(yyin);

        if (parse_result || error_count > 0)
        {
            fprintf(stderr, "Parse failed\n");
            return 1;
        }

        obj->ast = current_ast;
        current_ast = NULL;

        symbol_table_print(obj->symtab);

        c64linker_add_object(global_linker, obj);
    }
    c64linker_link(global_linker);
    ast_print(current_ast);
    // c64gen_gen(current_ast, "out.bin", current_table);
    c64gen_gen(global_linker->objs);
    c64linker_free(global_linker);
    return 0;
}

void yyerror(char *s)
{
    if (strcmp(s, "syntax error") == 0)
    {
        fprintf(stderr, "Error on line %d in file %s: Unknown Symbol '%s'\n", line_no, current_filename, yytext);
    }
    else
    {
        fprintf(stderr, "Error on line %d in file: %s\n", line_no, current_filename, s);
    }
    if (current_line)
    {
        fprintf(stderr, "%d:    %s\n\n", line_no, current_line);
        free(current_line);
        current_line = NULL;
    }
}