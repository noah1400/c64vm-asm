%{
    #include <c64asm_opcodes.h>
    #include <c64asm_ast.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdint.h>
    extern int line_no;

    void add_label(char *label);
    ASTNode *add_label_def_node(char *label);
    ASTNode *add_label_ref_node(char *label);
    ASTNode *add_instruction_node(char *mnemonic, uint16_t opcode, ASTNode* operand1, ASTNode *operand2);
    ASTNode *add_comment_node(char *comment);
    ASTNode *add_immediate_node(uint64_t immediate);
    ASTNode *add_register_node(uint8_t reg);
%}

%union {
    char *str;
    uint64_t imm;
    uint16_t opcode;
    uint8_t byte;
}

%token <imm> NUMBER 
%token <imm> HEX
%token <byte> REGISTER
%token <opcode> LDI 
%token <opcode> ST
%token <opcode> PUSH
%token <opcode> POP
%token <opcode> EOL
%token <opcode> JMP
%token <str> COMMENT

%token <str> LABEL_DEF
%token <str> LABEL_REF

%type <imm> immediate
%type <str> opt_comment

%%

c64asm: 
    | c64asm line opt_comment EOL
    | c64asm error EOL { printf("Error on line %d\n", line_no); }
    ;

line: 
    | instruction
    | LABEL_DEF { 
        printf("%s:\n", $1);
        add_label($1);
        add_label_def_node($1);
        }
    ;

opt_comment:  { $$ = ""; } 
    | COMMENT { $$ = $1; }
    ;

instruction: LDI REGISTER ',' immediate { 
            printf("0x%04lx r%d, %d\n", OP_LDI, $2, $4); 
            add_instruction_node("LDI", OP_LDI, add_register_node($2), add_immediate_node($4));
        }
    | ST REGISTER ',' immediate { 
            printf("0x%04lx r%d, %d\n", OP_ST, $2, $4); 
            add_instruction_node("ST", OP_ST, add_register_node($2), add_immediate_node($4));
        }
    | PUSH REGISTER { 
            printf("PUSH r%d\n", $2); 
            add_instruction_node("PUSH", OP_PUSH, add_register_node($2), NULL);
        }
    | POP REGISTER { 
            printf("POP r%d\n", $2); 
            add_instruction_node("POP", OP_POP, add_register_node($2), NULL);
        }
    | JMP LABEL_REF { 
            printf("JMP %s\n", $2); 
            add_instruction_node("JMP", OP_JMP, add_label_ref_node($2), NULL);
        }
    ;

immediate: NUMBER { $$ = $1; }
    | HEX { $$ = $1; }
    ;

%%

#include <c64asm_symbols.h>

void add_label(char *label) {
    printf("Label: %s\n", label);
    if (symbol_table_find(symbol_table, label) != NULL) {
        printf("Error: Label %s already defined\n", label);
        exit(1);
    }
    symbol_table_add(symbol_table, SYMBOL_TYPE_LABEL, label, 0);
}

ASTNode *add_label_def_node(char *label) {
    ASTNode *node = ast_create_label_def_node(label);
    ast_append_node(&ast_head, node);
    return node;
}

ASTNode *add_label_ref_node(char *label) {
    ASTNode *node = ast_create_label_ref_node(label);
    ast_append_node(&ast_head, node);
    return node;
}

ASTNode *add_instruction_node(char *mnemonic, uint16_t opcode, ASTNode* operand1, ASTNode *operand2) {
    ASTNode *node = ast_create_instruction_node(mnemonic, opcode, operand1, operand2);
    ast_append_node(&ast_head, node);
    return node;
}

ASTNode *add_immediate_node(uint64_t immediate) {
    ASTNode *node = ast_create_immediate_node(immediate);
    ast_append_node(&ast_head, node);
    return node;
}

ASTNode *add_register_node(uint8_t reg) {
    ASTNode *node = ast_create_register_node(reg);
    ast_append_node(&ast_head, node);
    return node;
}

