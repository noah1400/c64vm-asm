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
#ifndef _c64utils_h_
# define _c64utils_h_

# include <c64token.h>
# include <c64utils.h>
# include <stdio.h>
# include <stdlib.h>

char	c64utils_toupper(char c);

void	c64utils_fatals(char *s1, char *s2);
void	c64utils_fatalc(char *s, char c);
void	c64utils_fatald(char *s, int d);
void	c64utils_fatal(char *s);

#endif // _c64utils_h_