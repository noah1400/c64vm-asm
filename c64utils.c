/*
Copyright (c) 2023 Noah Scholz

This file is part of the c64asm project.

c64asm is free software: you can redistribute it and/or modify
it under the terms of the MIT License. See the LICENSE file.

c64asm is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

You should have received a copy of the MIT License
along with c64asm. If not, see <https://mit-license.org/>.
*/
#include <c64utils.h>

char c64utils_toupper(char c)
{
    // char can be digits or letters in the range a-z or A-Z and 0-9
    if (c >= 'a' && c <= 'z') {
        return c - 32;
    }
    return c;
}

void c64utils_fatals(char *s1, char *s2)
{
    fprintf(stderr, "%d:%d *** FATAL: %s %s\n", Line, Pos, s1, s2);
    exit(1);
}

void c64utils_fatalc(char *s, char c)
{
    fprintf(stderr, "%d:%d *** FATAL: %s '%c'\n", Line, Pos, s, c);
    exit(1);
}

void c64utils_fatald(char *s, int d)
{
    fprintf(stderr, "%d:%d *** FATAL: %s %d\n", Line, Pos, s, d);
    exit(1);
}

void c64utils_fatal(char *s)
{
    fprintf(stderr, "%d:%d *** FATAL: %s\n", Line, Pos, s);
    exit(1);
}