#ifndef c64asm_opcodes_h
#define c64asm_opcodes_h

#include <stdint.h>

#define OP_LDI (uint16_t)0x0001
#define OP_LDBI (uint16_t)0x0101
#define OP_LDWI (uint16_t)0x0201
#define OP_LDDI (uint16_t)0x0301
#define OP_LDM (uint16_t)0x0002
#define OP_LDBM (uint16_t)0x0102
#define OP_LDWM (uint16_t)0x0202
#define OP_LDDM (uint16_t)0x0302
#define OP_ST (uint16_t)0x0003
#define OP_STB (uint16_t)0x0103
#define OP_STW (uint16_t)0x0203
#define OP_STD (uint16_t)0x0303
#define OP_TF (uint16_t)0x0004

#define OP_ADDI (uint16_t)0x0011
#define OP_SUBI (uint16_t)0x0012
#define OP_MULI (uint16_t)0x0013
#define OP_DIVI (uint16_t)0x0014
#define OP_MODI (uint16_t)0x0015
#define OP_MULIS (uint16_t)0x0016
#define OP_DIVIS (uint16_t)0x0017

#define OP_ADD (uint16_t)0x0021
#define OP_SUB (uint16_t)0x0022
#define OP_MUL (uint16_t)0x0023
#define OP_DIV (uint16_t)0x0024
#define OP_MOD (uint16_t)0x0025
#define OP_MULS (uint16_t)0x0026
#define OP_DIVS (uint16_t)0x0027

#define OP_ANDI (uint16_t)0x0031
#define OP_ORI (uint16_t)0x0032
#define OP_XORI (uint16_t)0x0033
#define OP_NOTI (uint16_t)0x0034
#define OP_SHLI (uint16_t)0x0035
#define OP_SHRI (uint16_t)0x0036
#define OP_RORI (uint16_t)0x0037
#define OP_ROLI (uint16_t)0x0038

#define OP_AND (uint16_t)0x0041
#define OP_OR (uint16_t)0x0042
#define OP_XOR (uint16_t)0x0043
#define OP_NOT (uint16_t)0x0044
#define OP_SHL (uint16_t)0x0045
#define OP_SHR (uint16_t)0x0046
#define OP_ROR (uint16_t)0x0047
#define OP_ROL (uint16_t)0x0048

#define OP_CMP (uint16_t)0x0051
#define OP_CMPI (uint16_t)0x0052

#define OP_JMP (uint16_t)0x0061
#define OP_JEQ (uint16_t)0x0062
#define OP_JNE (uint16_t)0x0063
#define OP_JGT (uint16_t)0x0064
#define OP_JLT (uint16_t)0x0065
#define OP_JGE (uint16_t)0x0066
#define OP_JLE (uint16_t)0x0067

#define OP_BRAR (uint16_t)0x0171
#define OP_BEQR (uint16_t)0x0172
#define OP_BNER (uint16_t)0x0173
#define OP_BGTR (uint16_t)0x0174
#define OP_BLTR (uint16_t)0x0175
#define OP_BGER (uint16_t)0x0176
#define OP_BLER (uint16_t)0x0177

#define OP_RET (uint16_t)0x0081

#define OP_PUSH (uint16_t)0x0091
#define OP_PUSHI (uint16_t)0x0092
#define OP_POP (uint16_t)0x0093

#define OP_CALL (uint16_t)0x00A1
#define OP_CALLR (uint16_t)0x00A2
#define OP_RTC (uint16_t)0x00A3

#define OP_CLC (uint16_t)0x00B1
#define OP_SEC (uint16_t)0x00B2
#define OP_CLZ (uint16_t)0x00B3
#define OP_SEZ (uint16_t)0x00B4
#define OP_CLN (uint16_t)0x00B5
#define OP_SEN (uint16_t)0x00B6
#define OP_CLV (uint16_t)0x00B7
#define OP_SEV (uint16_t)0x00B8
#define OP_CLI (uint16_t)0x00B9
#define OP_SEI (uint16_t)0x00BA

#define OP_INT (uint16_t)0x00C1
#define OP_RTI (uint16_t)0x00C2

#define OP_NOP (uint16_t)0x0000
#define OP_HLT (uint16_t)0xFFFF

#endif // c64asm_opcodes_h
