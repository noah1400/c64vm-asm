#include <c64asm.h>

void c64asm_init(void)
{
    Putback = '\n';
    Line = 1;
    Pos = 1;
    // Registers = {
    //     "ACC", "IP", "SP", "FP", "MB", "IM", "R1", "R2", "R3", "R4", "R5", "R6", "R7", "R8"
    // };
    Registers[0] = "ACC";
    Registers[1] = "IP";
    Registers[2] = "SP";
    Registers[3] = "FP";
    Registers[4] = "MB";
    Registers[5] = "IM";
    Registers[6] = "R1";
    Registers[7] = "R2";
    Registers[8] = "R3";
    Registers[9] = "R4";
    Registers[10] = "R5";
    Registers[11] = "R6";
    Registers[12] = "R7";
    Registers[13] = "R8";
    
}