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