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