# CC=gcc
# CFLAGS=-W -Wall
# EXEC=main

# all: $(EXEC)

# main: lib_0.o main.o
# 	$(CC) -o $@ $^ $(LDFLAGS)

# lib_0.o: level_0/lib_0.c
# 	$(CC) -o $@ -c $^ -W -Wall

# main.o: main.c  level_0/lib_0.h
# 	$(CC) -o $@ -c $<

# clean:
# 	rm *.o $(EXEC)

prefixe=compilateur

all: $(prefixe).y $(prefixe).l ast.c ast.h
	yacc -d $(prefixe).y
	lex $(prefixe).l
	gcc y.tab.c lex.yy.c ast.c -ly -ll -g

clean:
	rm *.o y.tab.c y.tab.h lex.yy.c a.out
