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
#include <c64tokenizer.h>

struct c64tokenlist *c64tokenize(void)
{

    struct c64tokenlist *first = malloc(sizeof(struct c64tokenlist));
    if (first == NULL) {
        c64utils_fatal("failed to malloc() in c64tokenize()");
    }
    first->token = NULL;
    first->next = NULL;

    struct c64tokenlist *current = first;

    c64token_scan(&Token);

    while(Token.type != T_EOF) {
        if (current->token == NULL) {
            current->token = c64token_copy(&Token); // first token
        } else {
            current = c64tokenlist_add(current, &Token);
        }
        c64token_scan(&Token);
    }

    if (Token.type != T_EOF) {
        c64utils_fatal("unexpected token");
    }

    current = c64tokenlist_add(current, &Token); // last token

    return first;
}

struct c64tokenlist *c64tokenlist_add(struct c64tokenlist *list, struct c64token *token)
{
    struct c64token *copy = c64token_copy(token);
    struct c64tokenlist *new = malloc(sizeof(struct c64tokenlist));

    if (new == NULL) {
        c64utils_fatal("failed to malloc() in c64tokenlist_add()");
    }

    new->token = copy;
    new->next = NULL;

    list->next = new;

    return new;
}

void c64tokenlist_free(struct c64tokenlist *list)
{
    struct c64tokenlist *current = list;
    struct c64tokenlist *next = NULL;

    while (current != NULL) {
        next = current->next;
        free(current->token);
        free(current);
        current = next;
    }
}

void c64tokenlist_print(struct c64tokenlist *list)
{
    struct c64tokenlist *current = list;

    while (current != NULL) {
        c64token_print(current->token);
        current = current->next;
    }
}