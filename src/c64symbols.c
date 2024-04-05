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

SymbolTable *symbol_table_init(char *filename)
{
    symbol_table = malloc(sizeof(SymbolTable));
    for (int i = 0; i < SYMBOL_TABLE_SIZE; i++) {
        symbol_table->table[i] = NULL;
        symbol_table->def_directives[i] = NULL;
        symbol_table->ref_directives[i] = NULL;
    }
    symbol_table->filename = strdup(filename);
    return symbol_table;
}

void symbol_table_add(SymbolTable *table, SymbolType type, const char *name, uint64_t address)
{
    Symbol *symbol = malloc(sizeof(Symbol));
    printf("Adding symbol %s of type %d at address %lu\n", name, type, address);
    symbol->name = strdup(name);
    symbol->type = type;
    symbol->address = address;
    symbol->next = NULL;

    unsigned int index = hash(name);

    symbol->next = table->table[index];
    table->table[index] = symbol;
}

Symbol *symbol_table_find(SymbolTable *table, const char *name, SymbolType type)
{
    printf("Searching for label %s of type %d\n", name, type);
    unsigned int index = hash(name);
    Symbol *symbol = table->table[index];

    while (symbol) {
        printf("Comparing %s of type %d with %s\n", symbol->name, symbol->type, name);
        if (strcmp(symbol->name, name) == 0 && symbol->type == type) {
            return symbol;
        }
        symbol = symbol->next;
    }

    return NULL;
}

Symbol *symbol_table_find_any_type(SymbolTable *table, const char *name)
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

void symbol_table_add_def_directive(SymbolTable *table, const char *name)
{
    Symbol *symbol = malloc(sizeof(Symbol));
    symbol->name = strdup(name);
    symbol->type = SYMBOL_TYPE_UNKNOWN;
    symbol->address = ADDR_UNDEFINED;
    symbol->next = NULL;

    unsigned int index = hash(name);

    symbol->next = table->def_directives[index];
    table->def_directives[index] = symbol;
}

void symbol_table_add_ref_directive(SymbolTable *table, const char *name)
{
    Symbol *symbol = malloc(sizeof(Symbol));
    symbol->name = strdup(name);
    symbol->type = SYMBOL_TYPE_UNKNOWN;
    symbol->address = ADDR_UNDEFINED;
    symbol->next = NULL;

    unsigned int index = hash(name);

    symbol->next = table->ref_directives[index];
    table->ref_directives[index] = symbol;
}

Symbol *symbol_table_find_def_directive(SymbolTable *table, const char *name)
{
    unsigned int index = hash(name);
    Symbol *symbol = table->def_directives[index];

    while (symbol) {
        if (strcmp(symbol->name, name) == 0) {
            return symbol;
        }
        symbol = symbol->next;
    }

    return NULL;
}

Symbol *symbol_table_find_ref_directive(SymbolTable *table, const char *name)
{
    unsigned int index = hash(name);
    Symbol *symbol = table->ref_directives[index];

    while (symbol) {
        if (strcmp(symbol->name, name) == 0) {
            return symbol;
        }
        symbol = symbol->next;
    }

    return NULL;
}

void symbol_table_resolve_def_directives(SymbolTable *table)
{
    for (int i = 0; i < SYMBOL_TABLE_SIZE; i++) {
        Symbol *symbol = table->def_directives[i];
        while (symbol) {
            Symbol *resolved = symbol_table_find_any_type(table, symbol->name);
            if (resolved) {
                printf("Resolved symbol %s to address %lu\n", symbol->name, resolved->address);
                symbol->address = resolved->address;
                symbol->type = resolved->type;
            } else {
                fprintf(stderr, "Symbol %s exported but not defined!", symbol->name);
                exit(1);
            }
            symbol = symbol->next;
        }
    }

}

void symbol_table_free(SymbolTable *table)
{
    free(table->filename);
    for (int i = 0; i < SYMBOL_TABLE_SIZE; i++) {
        Symbol *symbol = table->table[i];
        while (symbol) {
            Symbol *next = symbol->next;
            free(symbol->name);
            free(symbol);
            symbol = next;
        }
    }

    for (int i = 0; i < SYMBOL_TABLE_SIZE; i++) {
        Symbol *symbol = table->def_directives[i];
        while (symbol) {
            Symbol *next = symbol->next;
            free(symbol->name);
            free(symbol);
            symbol = next;
        }
    }

    for (int i = 0; i < SYMBOL_TABLE_SIZE; i++) {
        Symbol *symbol = table->ref_directives[i];
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
    printf("Symbol table for file %s:\n", table->filename);
    for (int i = 0; i < SYMBOL_TABLE_SIZE; i++) {
        Symbol *symbol = table->table[i];
        while (symbol) {
            printf("%s: %lu (%d)\n", symbol->name, symbol->address, symbol->type);
            symbol = symbol->next;
        }
    }
}

Symbol *symbol_copy(Symbol *symbol)
{
    Symbol *copy = malloc(sizeof(Symbol));
    copy->name = strdup(symbol->name);
    copy->type = symbol->type;
    copy->address = symbol->address;
    copy->next = NULL;
    return copy;
}