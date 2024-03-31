#ifndef c64asm_ast_h
#define c64asm_ast_h

#include <stdint.h>
#include <stdlib.h>

typedef enum {
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
        char *comment; // added for optional use later
    } data;
    struct ASTNode *next;
} ASTNode;

extern ASTNode *ast_head;

ASTNode *ast_create_node(NodeType type);
ASTNode *ast_create_label_def_node(char *label);
ASTNode *ast_create_label_ref_node(char *label);
ASTNode *ast_create_instruction_node(char *mnemonic, uint16_t opcode, ASTNode *op1, ASTNode *op2);
ASTNode *ast_create_immediate_node(uint64_t immediate);
ASTNode *ast_create_register_node(uint8_t reg);
ASTNode *ast_create_comment_node(char *comment); // added for optional use later
void ast_append_node(ASTNode **head, ASTNode *node);
void ast_free(ASTNode *head);



#endif // c64asm_ast_h