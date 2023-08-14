/*
Copyright (c) 2023 Noah Scholz

This file is part of the c64asm project.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
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