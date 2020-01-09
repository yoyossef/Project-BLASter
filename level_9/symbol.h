#ifndef _SYMBOL_H_
#define _SYMBOL_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#define SYMBOL_MAX_STRING 42

typedef struct symbol {
    char* identifier;
    bool is_constant;
    int value; // seulement si c'est une constante ou tableau 
    struct symbol* next;
} symbol;


struct symbol* symbol_alloc();
struct symbol* symbol_add(struct symbol**, char*);
struct symbol* symbol_newtemp(struct symbol**);
struct symbol* symbol_newtemp_init(struct symbol**, int);
struct symbol* symbol_lookup(struct symbol*, char*);
void symbol_build_table(struct ast* ast, struct symbol** symbol_table);
void symbol_free(struct symbol*);
void symbol_print(struct symbol*);

#endif
