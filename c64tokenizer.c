#include <c64tokenizer.h>

struct c64tokenlist *c64tokenize(void)
{
    while(c64token_scan(&Token)) {
        c64tokenlist_addToken(Token);
    }

    if (Token.type != T_EOF) {
        fatal("unexpected token");
    }

    c64tokenlist_setLastToken(Token); // set last token to EOF

    return c64tokenlist_getFirstToken();
}