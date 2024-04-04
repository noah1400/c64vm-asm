#ifndef c64asm_gen_h
#define c64asm_gen_h

#include <stdio.h>
#include <stdint.h>
#include <c64asm_ast.h>
#include <c64asm_symbols.h>



void c64gen_write64(FILE *f, uint64_t value, uint64_t *ip);
void c64gen_write32(FILE *f, uint32_t value, uint64_t *ip);
void c64gen_write16(FILE *f, uint16_t value, uint64_t *ip);
void c64gen_write8(FILE *f, uint8_t value, uint64_t *ip);

void c64gen_gen(ASTNode *ast, const char *filename, SymbolTable *table);

#endif // c64asm_gen_h