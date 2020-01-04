#ifndef AST_LIBRARY_H
#define AST_LIBRARY_H


#include "ast.h"

ast* get_set_ast();
ast* get_swap_ast();
ast* get_addition_ast();
ast* get_scalar_product_ast();
ast* get_axpy_ast();

#endif