#ifndef _c64utils_h_
#define _c64utils_h_

#include <stdio.h>
#include <c64token.h>
#include <c64utils.h>

char c64utils_toupper(char c);

void c64utils_fatals(char *s1, char *s2);
void c64utils_fatalc(char *s, char c);
void c64utils_fatald(char *s, int d);
void c64utils_fatal(char *s);

#endif // _c64utils_h_