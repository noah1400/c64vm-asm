#ifndef c64asm_symbols_h
#define c64asm_symbols_h

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define SYMBOL_TABLE_SIZE 64

typedef enum {
    SYMBOL_TYPE_LABEL,
    SYMBOL_TYPE_CONSTANT,
    SYMBOL_TYPE_VARIABLE
} SymbolType;

typedef struct Symbol {
    SymbolType type;
    char *name;
    uint64_t address;
    struct Symbol *next;
} Symbol;

typedef struct {
    Symbol *table[SYMBOL_TABLE_SIZE];
} SymbolTable;


extern SymbolTable *symbol_table;

void symbol_table_init();
void symbol_table_add(SymbolTable *table, SymbolType type, const char *name, uint64_t address);
Symbol *symbol_table_find(SymbolTable *table, const char *name);
void symbol_table_free(SymbolTable *table);
unsigned int hash(const char *str);

void symbol_table_print(SymbolTable *table);

#endif // c64asm_symbols_h