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