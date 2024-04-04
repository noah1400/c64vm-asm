#include <c64asm_gen.h>

void c64gen_write_node(ASTNode *node, FILE *f, uint64_t *ip, SymbolTable *symbol_table);

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

void c64gen_write_instruction(ASTNode *instruction, FILE *f, uint64_t *ip, SymbolTable *symbol_table)
{
    uint16_t opcode = instruction->data.instruction.opcode;
    c64gen_write16(f, opcode, ip);
    ASTNode *op1 = instruction->data.instruction.operands[0];
    ASTNode *op2 = instruction->data.instruction.operands[1];
    if (op1)
    {
        c64gen_write_node(op1,f, ip, symbol_table); 
    }
    if (op2)
    {
        c64gen_write_node(op2,f, ip, symbol_table);
    }
}

void c64gen_write_register(ASTNode *reg,FILE *f, uint64_t *ip)
{
    uint8_t reg_num = reg->data.reg+1;
    c64gen_write8(f, reg_num, ip);
}

void c64gen_first_pass(ASTNode *node, uint64_t *ip, SymbolTable *symbol_table)
{
    if (!node)
    {
        return;
    }
    printf("FIRST PASS: NODE AT IP: %lu\n", *ip);
    switch (node->type)
    {
    case NODE_LABEL_DEF:
        printf("FIRST PASS: Label Definition: %s\n", node->data.label);
        Symbol *label = symbol_table_find(symbol_table, node->data.label, SYMBOL_TYPE_LABEL);
        if (!label)
        {
            fprintf(stderr, "Undefined label %s\n", node->data.label);
            exit(1);
        }
        printf("Set address for label %s: %lu\n", node->data.label, *ip);
        label->address = *ip;
        break;
    case NODE_LABEL_REF:
        printf("FIRST PASS: Label Reference: %s\n", node->data.label);
        Symbol *ref = symbol_table_find(symbol_table, node->data.label, SYMBOL_TYPE_LABEL);
        if (!ref)
        {
            fprintf(stderr, "Undefined label %s\n", node->data.label);
            exit(1);
        }
        *ip += sizeof(uint64_t);
        break;
    case NODE_INSTRUCTION:
        printf("FIRST PASS: Instruction: %s\n", node->data.instruction.mnemonic);
        *ip += sizeof(uint16_t);
        ASTNode *op1 = node->data.instruction.operands[0];
        ASTNode *op2 = node->data.instruction.operands[1];
        c64gen_first_pass(op1, ip, symbol_table);
        c64gen_first_pass(op2, ip, symbol_table);
        break;
    case NODE_IMMEDIATE:
        *ip += sizeof(uint64_t);
        break;
    case NODE_REGISTER:
        *ip += sizeof(uint8_t);
        break;
    default:
        fprintf(stderr, "Unknown AST node type %d\n", node->type);
        exit(1);
    }

    
}

void c64gen_write_node(ASTNode *node, FILE *f, uint64_t *ip, SymbolTable *symbol_table)
{
    switch (node->type)
    {
    case NODE_LABEL_DEF:
        printf("GEN: Label Definition: %s\n", node->data.label);
        Symbol *label = symbol_table_find(symbol_table, node->data.label, SYMBOL_TYPE_LABEL);
        if (label->address != *ip)
        {
            fprintf(stderr, "Address mismatch for label %s: %lu != %lu\n", node->data.label, label->address, *ip);
            exit(1);
        }
        // Do nothing (labels are handled in the first pass)
        break;
    case NODE_LABEL_REF:
        printf("GEN: Label Reference: %s\n", node->data.label);
        Symbol *ref = symbol_table_find(symbol_table, node->data.label, SYMBOL_TYPE_LABEL);
        if (!ref)
        {
            fprintf(stderr, "Undefined label %s\n", node->data.label);
            exit(1);
        }
        printf("Writing address for label %s: %lu\n", node->data.label, ref->address);
        c64gen_write64(f, ref->address, ip);
        break;
    case NODE_INSTRUCTION:
        printf("GEN: Instruction: %s\n", node->data.instruction.mnemonic);
        c64gen_write_instruction(node,f, ip, symbol_table);
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

void c64gen_gen(ASTNode *ast, const char *filename, SymbolTable *symbol_table)
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
        // Scan code and set label addresses
        c64gen_first_pass(current, &ip, symbol_table);
        // Move to the next node in the AST
        current = current->next;
    }

    // Reset the instruction pointer to 0
    ip = 0;
    // Reset the current node to the start of the AST
    current = ast;

    while (current != NULL)
    {
        // Write the current node to the output file
        c64gen_write_node(current, f, &ip, symbol_table);
        // Move to the next node in the AST
        current = current->next;
    }

    printf("Writing HLT\n");
    //Write HLT ( 0xffff )
    c64gen_write8(f, 0xff, &ip);
    c64gen_write8(f, 0xff, &ip);

    // Close the output file
    fclose(f);
}
