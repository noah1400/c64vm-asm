#ifndef c64asm_symbols_h
#define c64asm_symbols_h

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <c64asm_decl.h>
// #include <c64asm_link.h>
#include <c64asm_symbols.h>



extern SymbolTable *current_table;

SymbolTable *symbol_table_init(char *filename);
void symbol_table_add(SymbolTable *table, SymbolType type, const char *name, uint64_t address);
Symbol *symbol_table_find(SymbolTable *table, const char *name, SymbolType type);
Symbol *symbol_table_find_any_type(SymbolTable *table, const char *name);
void symbol_table_free(SymbolTable *table);

void symbol_table_add_def_directive(SymbolTable *table, const char *name);
void symbol_table_add_ref_directive(SymbolTable *table, const char *name);
Symbol *symbol_table_find_def_directive(SymbolTable *table, const char *name);
Symbol *symbol_table_find_ref_directive(SymbolTable *table, const char *name);

void symbol_table_resolve_def_directives(SymbolTable *table);
void symbol_table_resolve_ref_directives(c64linker_t *linker); // resolve references to global symbols in all object files

void symbol_table_resolve_global_defs(c64linker_t *linker);

unsigned int hash(const char *str);

Symbol *symbol_copy(Symbol *symbol);

void symbol_table_print(SymbolTable *table);

#endif // c64asm_symbols_h