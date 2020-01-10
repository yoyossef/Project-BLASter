#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "ast.h"
#include "symbol.h"

typedef struct opt_symbol {
    int is_same_symbol;
    struct symbol* symbol;
} opt_symbol;

int variable_is_replaceable(char* variable, ast* source, ast* function, symbol* table);
int variables_are_replaceable(ast* variables, ast* source, ast* function, symbol* table);
char* get_argument(char* argument, ast* source, ast* function);
ast* replace(ast* source, ast* function);
void optimize(ast* source, ast* library, symbol* table);

#endif