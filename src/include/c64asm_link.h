#ifndef c64asm_link_h
#define c64asm_link_h
#include <c64asm_ast.h>
#include <c64asm_decl.h>
#include <c64asm_symbols.h>




extern c64linker_t *global_linker;


c64linker_t *c64linker_create();
void c64linker_free(c64linker_t *linker);

c64link_OBJ_t *c64linker_create_object(char *filename);
void c64linker_add_object(c64linker_t *linker, c64link_OBJ_t *obj);
void c64linker_free_object(c64link_OBJ_t *obj);

void c64linker_link(c64linker_t *linker);


#endif // c64vm_link_h