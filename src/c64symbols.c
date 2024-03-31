#include <c64asm_symbols.h>

SymbolTable *symbol_table = NULL;

unsigned int hash(const char *str)
{
    unsigned int hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash % SYMBOL_TABLE_SIZE;
}

void symbol_table_init()
{
    symbol_table = malloc(sizeof(SymbolTable));
    memset(symbol_table->table, 0, sizeof(symbol_table->table));
}

void symbol_table_add(SymbolTable *table, SymbolType type, const char *name, uint64_t address)
{
    Symbol *symbol = malloc(sizeof(Symbol));
    symbol->name = strdup(name);
    symbol->type = type;
    symbol->address = address;
    symbol->next = NULL;

    unsigned int index = hash(name);

    symbol->next = table->table[index];
    table->table[index] = symbol;
}

Symbol *symbol_table_find(SymbolTable *table, const char *name)
{
    unsigned int index = hash(name);
    Symbol *symbol = table->table[index];

    while (symbol) {
        if (strcmp(symbol->name, name) == 0) {
            return symbol;
        }
        symbol = symbol->next;
    }

    return NULL;
}

void symbol_table_free(SymbolTable *table)
{
    for (int i = 0; i < SYMBOL_TABLE_SIZE; i++) {
        Symbol *symbol = table->table[i];
        while (symbol) {
            Symbol *next = symbol->next;
            free(symbol->name);
            free(symbol);
            symbol = next;
        }
    }
    free(table);
}

void symbol_table_print(SymbolTable *table)
{
    printf("Symbol table:\n");
    for (int i = 0; i < SYMBOL_TABLE_SIZE; i++) {
        Symbol *symbol = table->table[i];
        while (symbol) {
            printf("%s: %lu\n", symbol->name, symbol->address);
            symbol = symbol->next;
        }
    }
}