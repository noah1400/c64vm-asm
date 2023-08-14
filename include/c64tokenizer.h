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
#ifndef _c64tokenizer_h_
#define _c64tokenizer_h_

#include <stdlib.h>
#include <c64token.h>

struct c64tokenlist {
    struct c64tokenlist *next;
    struct c64token *token;
};

struct c64tokenlist *c64tokenize(void);

struct c64tokenlist *c64tokenlist_add(struct c64tokenlist *list, struct c64token *token);
void c64tokenlist_free(struct c64tokenlist *list);

void c64tokenlist_print(struct c64tokenlist *list);


#endif // _c64tokenizer_h_