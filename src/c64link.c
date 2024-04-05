#include <c64asm_link.h>

c64linker_t *c64linker_create()
{
    c64linker_t *linker = malloc(sizeof(c64linker_t));
    if (!linker) {
        fprintf(stderr, "Failed to allocate memory for linker\n");
        exit(1);
    }

    for (int i = 0; i < SYMBOL_TABLE_SIZE; i++) {
        linker->def_directives[i] = NULL;
    }

    linker->objs = NULL;
    return linker;
}

void c64linker_free(c64linker_t *linker)
{
    c64link_OBJ_t *obj = linker->objs;
    while (obj) {
        c64link_OBJ_t *next = obj->next;
        c64linker_free_object(obj);
        obj = next;
    }

    free(linker);
}

c64link_OBJ_t *c64linker_create_object(char *filename)
{
    c64link_OBJ_t *obj = malloc(sizeof(c64link_OBJ_t));
    if (!obj) {
        fprintf(stderr, "Failed to allocate memory for object\n");
        exit(1);
    }

    obj->filename = strdup(filename);
    obj->symtab = NULL;
    obj->ast = NULL;
    obj->next = NULL;
    return obj;
}

void c64linker_add_object(c64linker_t *linker, c64link_OBJ_t *obj)
{
    obj->next = linker->objs;
    linker->objs = obj;
}

void c64linker_free_object(c64link_OBJ_t *obj)
{
    free(obj->filename);
    symbol_table_free(obj->symtab);
    ast_free(obj->ast);
    free(obj);
}

void true_or_fail(int condition, const char *message)
{
    if (!condition) {
        fprintf(stderr, "%s\n", message);
        exit(1);
    }
}

void c64linker_resolve_label_addresses_node(ASTNode *node, SymbolTable *symtab, uint64_t *ip)
{
    if (!node) {
        printf("AST IS NULL\n");
        return;
    }
    printf("RESOLVING NODE AT IP: %lu\n", *ip);
    switch (node->type)
    {
        case NODE_LABEL_DEF:
            printf("RESOLVING LABEL DEF: %s\n", node->data.label);
            Symbol *label = symbol_table_find(symtab, node->data.label, SYMBOL_TYPE_LABEL);
            true_or_fail(label != NULL, "Label not found");
            printf("RESOLVING LABEL DEF: %s to address %lu\n", node->data.label, *ip);
            label->address = *ip;
            break;
        case NODE_LABEL_REF:
            printf("RESOLVING LABEL REF: %s\n", node->data.label);
            Symbol *ref = symbol_table_find(symtab, node->data.label, SYMBOL_TYPE_LABEL);
            true_or_fail(ref != NULL, "Label not found");
            *ip += sizeof(uint64_t);
            break;
        case NODE_INSTRUCTION:
            printf("RESOLVING INSTRUCTION: %s\n", node->data.instruction.mnemonic);
            *ip += sizeof(uint16_t);
            ASTNode *op1 = node->data.instruction.operands[0];
            ASTNode *op2 = node->data.instruction.operands[1];
            c64linker_resolve_label_addresses_node(op1, symtab, ip);
            c64linker_resolve_label_addresses_node(op2, symtab, ip);
            break;
        case NODE_IMMEDIATE:
            printf("RESOLVING IMMEDIATE: %lu\n", node->data.immediate);
            *ip += sizeof(uint64_t);
            break;
        case NODE_REGISTER:
            printf("RESOLVING REGISTER: %u\n", node->data.reg);
            *ip += sizeof(uint8_t);
            break;
        default:
            printf("UNKNOWN NODE TYPE %d\n", node->type);
            exit(1);
    }
}

void c64linker_resolve_label_addresses(ASTNode *ast, SymbolTable *symtab, uint64_t *ip)
{
    ASTNode *node = ast;
    while (node) {
        c64linker_resolve_label_addresses_node(node, symtab, ip);
        node = node->next;
    }
}

void c64linker_link(c64linker_t *linker)
{
    printf("LINKING\n");
    c64link_OBJ_t *obj = linker->objs;
    uint64_t ip = 0;
    while (obj) {
        printf("LINKING OBJECT: %s\n", obj->filename);
        obj->start_address = ip;
        c64linker_resolve_label_addresses(obj->ast, obj->symtab, &ip);
        symbol_table_resolve_def_directives(obj->symtab);
        obj = obj->next;
    }
    // TODO: Link objects
}