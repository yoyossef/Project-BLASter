CC=gcc
CFLAGS=-W -Wall
EXEC=main

all: $(EXEC)

main: lib_0.o main.o
	$(CC) -o $@ $^ $(LDFLAGS)

lib_0.o: level_0/lib_0.c
	$(CC) -o $@ -c $^ -W -Wall

main.o: main.c  level_0/lib_0.h
	$(CC) -o $@ -c $<

clean:
	rm *.o $(EXEC)