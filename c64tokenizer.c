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

    current->token = c64token_copy(&Token); // should be T_EOF

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