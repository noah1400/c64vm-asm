#ifndef c64asm_symbols_h
#define c64asm_symbols_h

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define SYMBOL_TABLE_SIZE 64

#define ADDR_UNDEFINED 0xFFFFFFFFFFFFFFFF

typedef enum {
    SYMBOL_TYPE_UNKNOWN,
    SYMBOL_TYPE_LABEL,
    SYMBOL_TYPE_CONSTANT,
    SYMBOL_TYPE_VARIABLE,
} SymbolType;

typedef struct Symbol {
    SymbolType type;
    char *name;
    uint64_t address;
    struct Symbol *next;
} Symbol;

typedef struct {
    char *filename;
    Symbol *def_directives[SYMBOL_TABLE_SIZE];
    Symbol *ref_directives[SYMBOL_TABLE_SIZE];
    Symbol *table[SYMBOL_TABLE_SIZE];
} SymbolTable;

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

unsigned int hash(const char *str);

Symbol *symbol_copy(Symbol *symbol);

void symbol_table_print(SymbolTable *table);

#endif // c64asm_symbols_h