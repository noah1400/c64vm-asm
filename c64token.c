#include <c64token.h>

void c64token_putback(char c)
{
    Putback = c;
    Pos--;
}

int c64token_chrpos(char *s, char c)
{
    char *p = strchr(s, c);
    return (p ? p - s : -1);
}

char c64token_next(void)
{
    char c;
    if (Putback) {
        c = Putback;
        Putback = '\0';
        return c;
    }
    c = fgetc(Infile);
    if (c == '\n') {
        Line++;
        Pos = 1;
    } else {
        Pos++;
    }
    return c;
}

char c64token_skip(void)
{
    char c = c64token_next();
    while (' ' == c || '\t' == c || '\n' == c || '\r' == c || '\f' == c) {
        c = c64token_next();
    }
    return c;
}

int c64token_scanint(char c)
{
    int k, val = 0;

    char f = 0;

    while((k = c64token_chrpos("0123456789", c)) >= 0) {
        val = val * 10 + k;
        c = c64token_next();
        f = 1;
    }

    if (!f) {
        fatal("integer expected");
    }

    c64token_putback(c);
    return val;
}

int c64token_scanhex(char c)
{
    int k, val = 0;

    char f = 0;

    while((k = c64token_chrpos("0123456789ABCDEF", c64utils_toupper(c))) >= 0) {
        val = val * 16 + k;
        c = c64token_next();
        f = 1;
    }

    if (!f) {
        fatal("hexadecimal number expected");
    }

    c64token_putback(c);
    return val;
}

int c64token_scanident(char c, char *buf, int lim)
{
    int i = 0;

    while (isalpha(c) || isdigit(c) || '_' == c)
    {
        if (lim - 1 == i) {
            fatal("identifier too long");
        } else if (i < lim - 1) {
            buf[i++] = c;
        }
        c = c64token_next();
    }

    c64token_putback(c);
    buf[i] = '\0';
    return i;
}

char c64token_scan(struct c64token *t)
{
    char c, type;

    c = c64token_skip();

    switch(c)
    {
        case EOF:
            t->type = T_EOF;
            t->line = Line;
            t->pos = Pos;
            t->str = "EOF";
            t->len = 3;
            t->val = 0;
            break;
        case ':':
            t->type = T_COLON;
            t->line = Line;
            t->pos = Pos;
            t->str = ":";
            t->len = 1;
            t->val = 0;
            break;
        case ',':
            t->type = T_COMMA;
            t->line = Line;
            t->pos = Pos;
            t->str = ",";
            t->len = 1;
            t->val = 0;
            break;
        case '{':
            t->type = T_LBRACE;
            t->line = Line;
            t->pos = Pos;
            t->str = "{";
            t->len = 1;
            t->val = 0;
            break;
        case '}':
            t->type = T_RBRACE;
            t->line = Line;
            t->pos = Pos;
            t->str = "}";
            t->len = 1;
            t->val = 0;
            break;
        case '$':
            t->type = T_IMM;
            t->line = Line;
            t->pos = Pos;
            t->str = "$";
            t->len = 1;
            t->val = c64token_scanhex(c64token_next());
            break;
        case '#':
            t->type = T_IMM;
            t->line = Line;
            t->pos = Pos;
            t->str = "#";
            t->len = 1;
            t->val = c64token_scanint(c64token_next());
            break;
        default:
            if (isalpha(c) || '_' == c) {
                c64token_scanident(c, Text, TEXT_LEN);
                strcpy(t->str, Text);
                t->line = Line;
                t->pos = Pos;
                t->len = strlen(Text);
                type = c64token_lookup(Text);
                if (type) {
                    t->type = type;
                    t->val = 0;
                } else {
                    t->type = T_IDENT;
                    t->val = 0;
                }
                break;
            }
            fatalc("unknown character", c);
    }

    return 1;
}