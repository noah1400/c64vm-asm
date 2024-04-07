#ifndef c64asm_decl_h
#define c64asm_decl_h

#include <stdint.h>

#define SYMBOL_TABLE_SIZE 64

#define ADDR_UNDEFINED 0xFFFFFFFFFFFFFFFF

typedef enum NodeType {
    NODE_LABEL_DEF,
    NODE_LABEL_REF,
    NODE_INSTRUCTION,
    NODE_IMMEDIATE,
    NODE_REGISTER,
    NODE_COMMENT, // added for optional use later
} NodeType;

typedef struct ASTNode {
    NodeType type;
    union {
        char *label;
        struct {
            char *mnemonic;
            uint16_t opcode;
            struct ASTNode *operands[2];
        } instruction;
        uint64_t immediate;
        uint8_t reg;
    } data;
    struct ASTNode *next;
} ASTNode;

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

typedef struct SymbolTable {
    char *filename;
    Symbol *def_directives[SYMBOL_TABLE_SIZE];
    Symbol *ref_directives[SYMBOL_TABLE_SIZE];
    Symbol *table[SYMBOL_TABLE_SIZE];
} SymbolTable;

typedef struct c64link_OBJ{
    char *filename;
    SymbolTable *symtab;
    ASTNode *ast;
    uint64_t start_address;
    struct c64link_OBJ *next;
} c64link_OBJ_t;

typedef struct {
    c64link_OBJ_t *objs;
    Symbol *def_directives[SYMBOL_TABLE_SIZE];
} c64linker_t;

#endif // c64asm_decl_h