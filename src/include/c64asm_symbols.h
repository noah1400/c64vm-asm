#ifndef c64asm_symbols_h
#define c64asm_symbols_h

#include <stdlib.h>
#include <cstdint>

typedef enum {
    SYMBOL_TYPE_LABEL,
    SYMBOL_TYPE_CONSTANT,
    SYMBOL_TYPE_VARIABLE
} SymbolType;

typedef struct {
    SymbolType type;
    const char *name;
    uint64_t address;
} Symbol;

typedef struct {
    Symbol **symbols;
    int count;
    int capacity;
} SymbolTable;

SymbolTable *symbol_table_create();
void symbol_table_destroy(SymbolTable *table);
Symbol *symbol_table_add(SymbolTable *table, SymbolType type, const char *name, uint64_t address);
Symbol *symbol_table_find(SymbolTable *table, const char *name);


#endif // c64asm_symbols_h