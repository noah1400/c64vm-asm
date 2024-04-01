#ifndef c64asm_opcodes_h
#define c64asm_opcodes_h

#include <stdint.h>

#define OP_LDI (uint16_t)0x0001

#define OP_ST (uint16_t)0x0003

#define OP_PUSH (uint16_t)0x0091
#define OP_POP (uint16_t)0x0093

#define OP_JMP (uint16_t)0x0061

#endif // c64asm_opcodes_h