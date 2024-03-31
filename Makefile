CC=gcc
LEX=flex
YACC=bison
LEXFILE=src/lexer/c64asm_lexer.l
YACCFILE=src/parser/c64asm_parser.y
INCLUDE=src/include
BINDIR=bin

TARGET=$(BINDIR)/c64asm

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(LEXFILE) $(YACCFILE)
	$(LEX) -o $(BINDIR)/lex.yy.c $(LEXFILE)
	$(YACC) -d -o $(BINDIR)/y.tab.c $(YACCFILE)
	$(CC) -o $(TARGET) $(BINDIR)/y.tab.c -I$(INCLUDE) -lfl -g

clean:
	rm -f $(BINDIR)/*
