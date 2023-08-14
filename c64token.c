#include <c64token.h>

struct c64token *c64token_copy(struct c64token *t)
{
    struct c64token *newToken = (struct c64token *)malloc(sizeof(struct c64token));
    if (newToken == NULL) {
        c64utils_fatal("failed to maloc() in c64token_createToken()");
    }
    newToken->type = t->type;
    strcpy(newToken->str, t->str);
    newToken->val = t->val;
    newToken->len = t->len;
    newToken->line = t->line;
    newToken->pos = t->pos;
    return newToken;
}

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
        c64utils_fatal("integer expected");
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
        c64utils_fatal("hexadecimal number expected");
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
            c64utils_fatal("identifier too long");
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
            strcpy(t->str, "EOF");
            t->len = 3;
            t->val = 0;
            break;
        case ':':
            t->type = T_COLON;
            t->line = Line;
            t->pos = Pos;
            strcpy(t->str, ":");
            t->len = 1;
            t->val = 0;
            break;
        case ',':
            t->type = T_COMMA;
            t->line = Line;
            t->pos = Pos;
            strcpy(t->str, ",");
            t->len = 1;
            t->val = 0;
            break;
        case '{':
            t->type = T_LBRACE;
            t->line = Line;
            t->pos = Pos;
            strcpy(t->str, "{");
            t->len = 1;
            t->val = 0;
            break;
        case '}':
            t->type = T_RBRACE;
            t->line = Line;
            t->pos = Pos;
            strcpy(t->str, "}");
            t->len = 1;
            t->val = 0;
            break;
        case '$':
            t->type = T_IMM;
            t->line = Line;
            t->pos = Pos;
            strcpy(t->str, "$");
            t->len = 1;
            t->val = c64token_scanhex(c64token_next());
            break;
        case '#':
            t->type = T_IMM;
            t->line = Line;
            t->pos = Pos;
            strcpy(t->str, "#");
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
            c64utils_fatalc("unknown character", c);
    }

    return 1;
}

int c64token_lookup(char *s)
{
    int i;

    for (i = 0; i < REGISTER_COUNT; i++) {
        if (0 == strcmp(Registers[i], s)) {
            return T_REG;
        }
    }

    // TODO: add instructions here
    // and return T_INSTR

    return 0;
}

void c64token_print(struct c64token *t)
{
    printf("%s (%d) at %d:%d: %s", c64token_typestr(t->type), t->type, t->line, t->pos, t->str);
    if (T_IMM == t->type) {
        printf(" = $%016X", t->val);
    }
    printf("\n");
}

char *c64token_typestr(int type)
{
    switch(type)
    {
        case T_EOF:
            return "T_EOF";
        case T_COLON:
            return "T_COLON";
        case T_COMMA:
            return "T_COMMA";
        case T_LBRACE:
            return "T_LBRACE";
        case T_RBRACE:
            return "T_RBRACE";
        case T_IMM:
            return "T_IMM";
        case T_REG:
            return "T_REG";
        case T_IDENT:
            return "T_IDENT";
        default:
            return "T_UNKNOWN";
    }
}