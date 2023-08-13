#ifndef _c64tokenizer_h_
#define _c64tokenizer_h_

#include <c64token.h>

struct c64tokenlist {
    c64tokenlist *next;
    c64token *token;
};

struct c64tokenlist *c64tokenize(void);

struct c64tokenlist *c64tokenlist_add(c64tokenlist *list, c64token *token);
struct c64tokenlist *c64tokenlist_remove(c64tokenlist *list, c64token *token);


#endif // _c64tokenizer_h_