#include <c64asm_gen.h>

void c64gen_write_node(ASTNode *node, FILE *f, uint64_t *ip);

void c64gen_write64(FILE *f, uint64_t value, uint64_t *ip)
{
    
    for (unsigned int i = 0; i < sizeof(value); i++)
    {
        uint8_t byte = (uint8_t)(value >> (8 * (sizeof(uint64_t) - i - 1)) & 0xFF);
        fwrite(&byte, sizeof(byte), 1, f);
    }

    // Update the instruction pointer
    *ip += sizeof(value);
}

void c64gen_write32(FILE *f, uint32_t value, uint64_t *ip)
{
    
    for (unsigned int i = 0; i < sizeof(value); i++)
    {
        uint8_t byte = (uint8_t)(value >> (8 * (sizeof(uint32_t) - i - 1)) & 0xFF);
        fwrite(&byte, sizeof(byte), 1, f);
    }

    // Update the instruction pointer
    *ip += sizeof(value);
}

void c64gen_write16(FILE *f, uint16_t value, uint64_t *ip)
{
    
    for (unsigned int i = 0; i < sizeof(value); i++)
    {
        uint8_t byte = (uint8_t)(value >> (8 * (sizeof(uint16_t) - i - 1)) & 0xFF);
        fwrite(&byte, sizeof(byte), 1, f);
    }

    // Update the instruction pointer
    *ip += sizeof(value);
}

void c64gen_write8(FILE *f, uint8_t value, uint64_t *ip)
{
    // Write the value to the file
    fwrite(&value, sizeof(value), 1, f);

    // Update the instruction pointer
    *ip += sizeof(value);
}

void c64gen_write_instruction(ASTNode *instruction, FILE *f, uint64_t *ip)
{
    uint16_t opcode = instruction->data.instruction.opcode;
    c64gen_write16(f, opcode, ip);
    ASTNode *op1 = instruction->data.instruction.operands[0];
    ASTNode *op2 = instruction->data.instruction.operands[1];
    if (op1)
    {
        c64gen_write_node(op1,f, ip);
    }
    if (op2)
    {
        c64gen_write_node(op2,f, ip);
    }
}

void c64gen_write_register(ASTNode *reg,FILE *f, uint64_t *ip)
{
    uint8_t reg_num = reg->data.reg;
    c64gen_write8(f, reg_num, ip);
}

void c64gen_write_node(ASTNode *node, FILE *f, uint64_t *ip)
{
    switch (node->type)
    {
    case NODE_LABEL_DEF:
        printf("GEN: Label Definition: %s\n", node->data.label);
        Symbol *label = symbol_table_find(symbol_table, node->data.label);
        if (!label)
        {
            fprintf(stderr, "Undefined label %s\n", node->data.label);
            exit(1);
        }
        label->address = *ip;
        break;
    case NODE_LABEL_REF:
        printf("GEN: Label Reference: %s\n", node->data.label);
        Symbol *ref = symbol_table_find(symbol_table, node->data.label);
            if (!ref)
            {
                fprintf(stderr, "Undefined label %s\n", node->data.label);
                exit(1);
            }
            c64gen_write64(f, ref->address, ip);
        break;
    case NODE_INSTRUCTION:
        printf("GEN: Instruction: %s\n", node->data.instruction.mnemonic);
        c64gen_write_instruction(node,f, ip);
        break;
    case NODE_IMMEDIATE:
        printf("GEN: Immediate: %lu\n", node->data.immediate);
        c64gen_write64(f, node->data.immediate, ip);
        break;
    case NODE_REGISTER:
        printf("GEN: Register: %u\n", node->data.reg);
        c64gen_write_register(node,f, ip);
        break;
    default:
        fprintf(stderr, "Unknown AST node type %d\n", node->type);
        exit(1);
    }
}

void c64gen_gen(ASTNode *ast, const char *filename)
{
    // Open the output file for writing
    FILE *f = fopen(filename, "wb");

    // Check if the file was opened successfully
    if (!f)
    {
        fprintf(stderr, "Failed to open output file %s\n", filename);
        exit(1);
    }

    // Initialize the instruction pointer to 0
    uint64_t ip = 0;

    // Traverse the AST and generate code
    ASTNode *current = ast;
    while (current != NULL)
    {
        // Write the current node to the output file
        c64gen_write_node(current, f, &ip);
        // Move to the next node in the AST
        current = current->next;
    }

    // Close the output file
    fclose(f);
}