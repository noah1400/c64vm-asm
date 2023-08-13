#include <c64asm.h>

void c64asm_init(void)
{
    Putback = '\n';
    Line = 1;
    Pos = 1;
}