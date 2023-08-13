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