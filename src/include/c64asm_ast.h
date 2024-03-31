#ifndef c64asm_ast_h
#define c64asm_ast_h

typedef enum {
    INST_LDI,
    INST_ST,
    INST_PUSH,
    INST_POP,
    INST_JMP
} InstructionType;

#endif // c64asm_ast_h