#include <c64asm_ast.h>

ASTNode *ast_head = NULL;

ASTNode *ast_create_node(NodeType type)
{
    ASTNode *node = malloc(sizeof(ASTNode));

    if (!node) {
        fprintf(stderr, "Failed to allocate memory for AST node\n");
        exit(1);
    }

    node->type = type;
    node->next = NULL;
    return node;
}

ASTNode *ast_create_label_def_node(char *label)
{
    ASTNode *node = ast_create_node(NODE_LABEL_DEF);
    node->data.label = strdup(label);
    return node;
}

ASTNode *ast_create_label_ref_node(char *label)
{
    ASTNode *node = ast_create_node(NODE_LABEL_REF);
    node->data.label = strdup(label);
    return node;
}

ASTNode *ast_create_instruction_node(char *mnemonic, uint16_t opcode, ASTNode *op1, ASTNode *op2)
{
    ASTNode *node = ast_create_node(NODE_INSTRUCTION);
    node->data.instruction.mnemonic = strdup(mnemonic);
    node->data.instruction.opcode = opcode;
    node->data.instruction.operands[0] = op1;
    node->data.instruction.operands[1] = op2;
    return node;
}

ASTNode *ast_create_immediate_node(uint64_t immediate)
{
    ASTNode *node = ast_create_node(NODE_IMMEDIATE);
    node->data.immediate = immediate;
    return node;
}

ASTNode *ast_create_register_node(uint8_t reg)
{
    ASTNode *node = ast_create_node(NODE_REGISTER);
    node->data.reg = reg;
    return node;
}

ASTNode *ast_create_comment_node(char *comment)
{
    ASTNode *node = ast_create_node(NODE_COMMENT);
    node->data.comment = strdup(comment);
    return node;
}

void ast_append_node(ASTNode **head, ASTNode *node)
{
    if (!*head) {
        *head = node;
        return;
    }

    ASTNode *current = *head;
    while (current->next) {
        current = current->next;
    }

    current->next = node;
}

void ast_free(ASTNode *head)
{
    ASTNode *current = head;
    while (current) {
        ASTNode *next = current->next;
        switch (current->type) {
            case NODE_LABEL_DEF:
            case NODE_LABEL_REF:
                free(current->data.label);
                break;
            case NODE_INSTRUCTION:
                free(current->data.instruction.mnemonic);
                ast_free(current->data.instruction.operands[0]);
                ast_free(current->data.instruction.operands[1]);
                break;
            case NODE_COMMENT:
                free(current->data.comment);
                break;
            default:
                break;
        }
        free(current);
        current = next;
    }
}