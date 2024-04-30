%{
    #include <c64asm_opcodes.h>
    #include <c64asm_ast.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdint.h>
    extern int line_no;
    extern int error_count;

    void add_label(char *label);
    ASTNode *add_label_def_node(char *label);
    ASTNode *create_label_ref_node(char *label);
    ASTNode *add_instruction_node(char *mnemonic, uint16_t opcode, ASTNode* operand1, ASTNode *operand2);
    ASTNode *add_comment_node(char *comment);
    ASTNode *create_immediate_node(uint64_t immediate);
    ASTNode *create_register_node(uint8_t reg);
    void add_def_directive(char *label);
    void add_ref_directive(char *label);
%}



%union {
    char *str;
    uint64_t imm;
    uint16_t opcode;
    uint8_t byte;
}

%token REF
%token DEF

%token <imm> NUMBER 
%token <imm> HEX
%token <byte> REGISTER
%token <str> EOL
%token <opcode> LDI 
%token <opcode> ST
%token <opcode> PUSH
%token <opcode> POP
%token <opcode> JMP
%token <opcode> LDBI
%token <opcode> LDWI
%token <opcode> LDDI
%token <opcode> LDM
%token <opcode> LDBM
%token <opcode> LDWM
%token <opcode> LDDM
%token <opcode> STB
%token <opcode> STW
%token <opcode> STD
%token <opcode> TF
%token <opcode> ADDI
%token <opcode> SUBI
%token <opcode> MULI
%token <opcode> DIVI
%token <opcode> MODI
%token <opcode> MULIS
%token <opcode> DIVIS
%token <opcode> ADD
%token <opcode> SUB
%token <opcode> MUL
%token <opcode> DIV
%token <opcode> MOD
%token <opcode> MULS
%token <opcode> DIVS
%token <opcode> ANDI
%token <opcode> ORI
%token <opcode> XORI
%token <opcode> NOTI
%token <opcode> SHLI
%token <opcode> SHRI
%token <opcode> RORI
%token <opcode> ROLI
%token <opcode> AND
%token <opcode> OR
%token <opcode> XOR
%token <opcode> NOT
%token <opcode> SHL
%token <opcode> SHR
%token <opcode> ROR
%token <opcode> ROL
%token <opcode> CMP
%token <opcode> CMPI
%token <opcode> JEQ
%token <opcode> JNE
%token <opcode> JGT
%token <opcode> JLT
%token <opcode> JGE
%token <opcode> JLE
%token <opcode> BRA
%token <opcode> BRAR
%token <opcode> BEQR
%token <opcode> BNER
%token <opcode> BGTR
%token <opcode> BLTR
%token <opcode> BGER
%token <opcode> BLER
%token <opcode> RET
%token <opcode> PUSHI
%token <opcode> CALL
%token <opcode> CALLR
%token <opcode> RTC
%token <opcode> CLC
%token <opcode> SEC
%token <opcode> CLZ
%token <opcode> SEZ
%token <opcode> CLN
%token <opcode> SEN
%token <opcode> CLV
%token <opcode> SEV
%token <opcode> CLI
%token <opcode> SEI
%token <opcode> INT
%token <opcode> RTI
%token <opcode> NOP
%token <opcode> HLT

%token <str> COMMENT

%token <str> LABEL_DEF
%token <str> LABEL_REF

%type <imm> immediate
%type <str> opt_comment

%%

c64asm: 
    | c64asm line opt_comment EOL
    | c64asm error EOL { error_count++; }
    ;

line: 
    | DEF LABEL_REF {  
        add_def_directive($2);
        }
    | REF LABEL_REF {
        add_ref_directive($2);
        }
    | instruction
    | LABEL_DEF {
        add_label($1);
        add_label_def_node($1);
        }
    ;

opt_comment:  { $$ = ""; } 
    | COMMENT { $$ = $1; }
    ;

instruction:
      LDI REGISTER ',' immediate {
            add_instruction_node("LDI", OP_LDI, create_register_node($2), create_immediate_node($4));
        }
    | ST REGISTER ',' immediate {
            add_instruction_node("ST", OP_ST, create_register_node($2), create_immediate_node($4));
        }
    | PUSH REGISTER {
            add_instruction_node("PUSH", OP_PUSH, create_register_node($2), NULL);
        }
    | POP REGISTER {
            add_instruction_node("POP", OP_POP, create_register_node($2), NULL);
        }
    | JMP LABEL_REF {
            add_instruction_node("JMP", OP_JMP, create_label_ref_node($2), NULL);
        }
    | LDBI REGISTER ',' immediate {
            add_instruction_node("LDBI", OP_LDBI, create_register_node($2), create_immediate_node($4));
        }
    | LDWI REGISTER ',' immediate {
            add_instruction_node("LDWI", OP_LDWI, create_register_node($2), create_immediate_node($4));
        }
    | LDDI REGISTER ',' immediate {
            add_instruction_node("LDDI", OP_LDDI, create_register_node($2), create_immediate_node($4));
        }
    | LDM REGISTER ',' immediate {
            add_instruction_node("LDM", OP_LDM, create_register_node($2), create_immediate_node($4));
        }
    | LDBM REGISTER ',' immediate {
            add_instruction_node("LDBM", OP_LDBM, create_register_node($2), create_immediate_node($4));
        }
    | LDWM REGISTER ',' immediate {
            add_instruction_node("LDWM", OP_LDWM, create_register_node($2), create_immediate_node($4));
        }
    | LDDM REGISTER ',' immediate {
            add_instruction_node("LDDM", OP_LDDM, create_register_node($2), create_immediate_node($4));
        }
    | STB REGISTER ',' immediate {
            add_instruction_node("STB", OP_STB, create_register_node($2), create_immediate_node($4));
        }
    | STW REGISTER ',' immediate {
            add_instruction_node("STW", OP_STW, create_register_node($2), create_immediate_node($4));
        }
    | STD REGISTER ',' immediate {
            add_instruction_node("STD", OP_STD, create_register_node($2), create_immediate_node($4));
        }
    | TF REGISTER ',' REGISTER {
            add_instruction_node("TF", OP_TF, create_register_node($2), create_register_node($4));
        }
    | ADDI REGISTER ',' immediate {
            add_instruction_node("ADDI", OP_ADDI, create_register_node($2), create_immediate_node($4));
        }
    | SUBI REGISTER ',' immediate {
            add_instruction_node("SUBI", OP_SUBI, create_register_node($2), create_immediate_node($4));
        }
    | MULI REGISTER ',' immediate {
            add_instruction_node("MULI", OP_MULI, create_register_node($2), create_immediate_node($4));
        }
    | DIVI REGISTER ',' immediate {
            add_instruction_node("DIVI", OP_DIVI, create_register_node($2), create_immediate_node($4));
        }
    | MODI REGISTER ',' immediate {
            add_instruction_node("MODI", OP_MODI, create_register_node($2), create_immediate_node($4));
        }
    | MULIS REGISTER ',' immediate {
            add_instruction_node("MULIS", OP_MULIS, create_register_node($2), create_immediate_node($4));
        }
    | DIVIS REGISTER ',' immediate {
            add_instruction_node("DIVIS", OP_DIVIS, create_register_node($2), create_immediate_node($4));
        }
    | ADD REGISTER ',' REGISTER {
            add_instruction_node("ADD", OP_ADD, create_register_node($2), create_register_node($4));
        }
    | SUB REGISTER ',' REGISTER {
            add_instruction_node("SUB", OP_SUB, create_register_node($2), create_register_node($4));
        }
    | MUL REGISTER ',' REGISTER {
            add_instruction_node("MUL", OP_MUL, create_register_node($2), create_register_node($4));
        }
    | DIV REGISTER ',' REGISTER {
            add_instruction_node("DIV", OP_DIV, create_register_node($2), create_register_node($4));
        }
    | MOD REGISTER ',' REGISTER {
            add_instruction_node("MOD", OP_MOD, create_register_node($2), create_register_node($4));
        }
    | MULS REGISTER ',' REGISTER {
            add_instruction_node("MULS", OP_MULS, create_register_node($2), create_register_node($4));
        }
    | DIVS REGISTER ',' REGISTER {
            add_instruction_node("DIVS", OP_DIVS, create_register_node($2), create_register_node($4));
        }
    | ANDI REGISTER ',' immediate {
            add_instruction_node("ANDI", OP_ANDI, create_register_node($2), create_immediate_node($4));
        }
    | ORI REGISTER ',' immediate {
            add_instruction_node("ORI", OP_ORI, create_register_node($2), create_immediate_node($4));
        }
    | XORI REGISTER ',' immediate {
            add_instruction_node("XORI", OP_XORI, create_register_node($2), create_immediate_node($4));
        }
    | NOTI REGISTER ',' immediate {
            add_instruction_node("NOTI", OP_NOTI, create_register_node($2), create_immediate_node($4));
        }
    | SHLI REGISTER ',' immediate {
            add_instruction_node("SHLI", OP_SHLI, create_register_node($2), create_immediate_node($4));
        }
    | SHRI REGISTER ',' immediate {
            add_instruction_node("SHRI", OP_SHRI, create_register_node($2), create_immediate_node($4));
        }
    | RORI REGISTER ',' immediate {
            add_instruction_node("RORI", OP_RORI, create_register_node($2), create_immediate_node($4));
        }
    | ROLI REGISTER ',' immediate {
            add_instruction_node("ROLI", OP_ROLI, create_register_node($2), create_immediate_node($4));
        }
    | AND REGISTER ',' REGISTER {
            add_instruction_node("AND", OP_AND, create_register_node($2), create_register_node($4));
        }
    | OR REGISTER ',' REGISTER {
            add_instruction_node("OR", OP_OR, create_register_node($2), create_register_node($4));
        }
    | XOR REGISTER ',' REGISTER {
            add_instruction_node("XOR", OP_XOR, create_register_node($2), create_register_node($4));
        }
    | NOT REGISTER ',' REGISTER {
            add_instruction_node("NOT", OP_NOT, create_register_node($2), create_register_node($4));
        }
    | SHL REGISTER ',' REGISTER {
            add_instruction_node("SHL", OP_SHL, create_register_node($2), create_register_node($4));
        }
    | SHR REGISTER ',' REGISTER {
            add_instruction_node("SHR", OP_SHR, create_register_node($2), create_register_node($4));
        }
    | ROR REGISTER ',' REGISTER {
            add_instruction_node("ROR", OP_ROR, create_register_node($2), create_register_node($4));
        }
    | ROL REGISTER ',' REGISTER {
            add_instruction_node("ROL", OP_ROL, create_register_node($2), create_register_node($4));
        }
    | CMP REGISTER ',' REGISTER {
            add_instruction_node("CMP", OP_CMP, create_register_node($2), create_register_node($4));
        }
    | CMPI REGISTER ',' immediate {
            add_instruction_node("CMPI", OP_CMPI, create_register_node($2), create_immediate_node($4));
        }
    | BRA LABEL_REF {
            add_instruction_node("BRA", OP_BRA, create_label_ref_node($2), NULL);
        }
    | JEQ LABEL_REF {
            add_instruction_node("JEQ", OP_JEQ, create_label_ref_node($2), NULL);
        }
    | JNE LABEL_REF {
            add_instruction_node("JNE", OP_JNE, create_label_ref_node($2), NULL);
        }
    | JGT LABEL_REF {
            add_instruction_node("JGT", OP_JGT, create_label_ref_node($2), NULL);
        }
    | JLT LABEL_REF {
            add_instruction_node("JLT", OP_JLT, create_label_ref_node($2), NULL);
        }
    | JGE LABEL_REF {
            add_instruction_node("JGE", OP_JGE, create_label_ref_node($2), NULL);
        }
    | JLE LABEL_REF {
            add_instruction_node("JLE", OP_JLE, create_label_ref_node($2), NULL);
        }
    | CALL LABEL_REF {
            add_instruction_node("CALL", OP_CALL, create_label_ref_node($2), NULL);
        }
    | RET {
            add_instruction_node("RET", OP_RET, NULL, NULL);
        }
    | PUSHI immediate {
            add_instruction_node("PUSHI", OP_PUSHI, create_immediate_node($2), NULL);
        }
    | NOP {
            add_instruction_node("NOP", OP_NOP, NULL, NULL);
        }
    | HLT {
            add_instruction_node("HLT", OP_HLT, NULL, NULL);
        }
    ;


immediate: NUMBER { $$ = $1; }
    | HEX { $$ = $1; }
    ;

%%

#include <c64asm_symbols.h>

void add_label(char *label) {

    if (symbol_table_find_any_type(current_table, label) != NULL 
        || symbol_table_find_ref_directive(current_table, label) != NULL ){
        yyerror("Label already defined");
    }
    symbol_table_add(current_table, SYMBOL_TYPE_LABEL, label, ADDR_UNDEFINED);
}

void add_def_directive(char *label) {
    if (symbol_table_find_ref_directive(current_table, label) != NULL
        || symbol_table_find_def_directive(current_table, label) != NULL) {
        yyerror("Label already referenced");
        }
    symbol_table_add_def_directive(current_table, label);
}

void add_ref_directive(char *label) {
    if (symbol_table_find_ref_directive(current_table, label) != NULL
        || symbol_table_find_def_directive(current_table, label) != NULL
        || symbol_table_find_any_type(current_table, label) != NULL ) {
        yyerror("Label already defined");
    }
    symbol_table_add_ref_directive(current_table, label);
}

ASTNode *add_label_def_node(char *label) {
    ASTNode *node = ast_create_label_def_node(label);
    ast_append_node(&current_ast, node);
    return node;
}

ASTNode *create_label_ref_node(char *label) {
    ASTNode *node = ast_create_label_ref_node(label);
    return node;
}

ASTNode *add_instruction_node(char *mnemonic, uint16_t opcode, ASTNode* operand1, ASTNode *operand2) {
    ASTNode *node = ast_create_instruction_node(mnemonic, opcode, operand1, operand2);
    ast_append_node(&current_ast, node);
    return node;
}

ASTNode *create_immediate_node(uint64_t immediate) {
    ASTNode *node = ast_create_immediate_node(immediate);
    return node;
}

ASTNode *create_register_node(uint8_t reg) {
    ASTNode *node = ast_create_register_node(reg);
    return node;
}

