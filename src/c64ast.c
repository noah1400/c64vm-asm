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
    node->data.label = strdup(comment);
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

static void ast_print_node(ASTNode *node) {
    if (!node) return;

    switch (node->type) {
        case NODE_LABEL_DEF:
            printf("Label Definition: %s\n", node->data.label);
            break;
        case NODE_LABEL_REF:
            printf("Label Reference: %s\n", node->data.label);
            break;
        case NODE_INSTRUCTION:
            printf("Instruction: %s, Opcode: 0x%04x\n", node->data.instruction.mnemonic, node->data.instruction.opcode);
            if (node->data.instruction.operands[0]) {
                printf("  Operand 1: ");
                ast_print_node(node->data.instruction.operands[0]);
            }
            if (node->data.instruction.operands[1]) {
                printf("  Operand 2: ");
                ast_print_node(node->data.instruction.operands[1]);
            }
            break;
        case NODE_IMMEDIATE:
            printf("Immediate: %llu\n", node->data.immediate);
            break;
        case NODE_REGISTER:
            printf("Register: R%u\n", node->data.reg);
            break;
        case NODE_COMMENT:
            printf("Comment: %s\n", node->data.label);
            break;
        default:
            printf("Unknown node type\n");
    }
}

void ast_print(ASTNode *head) {
    ASTNode *current = head;
    while (current) {
        ast_print_node(current);
        current = current->next;
    }
}

static void ast_free_node(ASTNode *node) {
    if (!node) return;

    switch (node->type) {
        case NODE_LABEL_DEF:
        case NODE_LABEL_REF:
        case NODE_COMMENT:
            free(node->data.label); // `label` and `comment` use the same union member
            break;
        case NODE_INSTRUCTION:
            free(node->data.instruction.mnemonic);
            ast_free_node(node->data.instruction.operands[0]);
            ast_free_node(node->data.instruction.operands[1]);
            break;
        // NODE_IMMEDIATE and NODE_REGISTER have no allocated memory
        case NODE_IMMEDIATE:
        case NODE_REGISTER:
            break;
        default:
            printf("Unknown node type %d in free function\n", node->type);
    }
}

void ast_free(ASTNode *head) {
    while (head) {
        ASTNode *temp = head;
        head = head->next;
        ast_free_node(temp);
        free(temp);
        temp = NULL;
    }
}