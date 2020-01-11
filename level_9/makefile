
EXEC=blaster
PREFIX=compilateur
CCFLAGS= -Wall -o $(EXEC) -g
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    CCFLAGS += -lfl
endif
ifeq ($(UNAME_S),Darwin)
    CCFLAGS += -ll -ly
endif

all: $(PREFIX).y $(PREFIX).l ast.c ast.h symbol.c symbol.h optimizer.c optimizer.h
	yacc -d $(PREFIX).y
	lex $(PREFIX).l
	gcc y.tab.c lex.yy.c ast.c symbol.c optimizer.c $(CCFLAGS)

clean:
	rm *.o y.tab.c y.tab.h lex.yy.c a.out $(EXEC)
