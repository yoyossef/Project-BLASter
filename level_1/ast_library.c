#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast_library.h"


ast* get_addition_ast() {
    ast* tmp;

    ast* init = ast_new_operation(AST_AFFECT, ast_new_id(strdup("i")), ast_new_number(0));
    ast* condition = ast_new_operation(AST_INF, ast_new_id(strdup("i")), ast_new_id(strdup("n")));
    tmp = ast_new_operation(AST_ADD, ast_new_id(strdup("i")), ast_new_number(1));
    ast* increment = ast_new_operation(AST_AFFECT, ast_new_id(strdup("i")), tmp);
    tmp = ast_new_operation(AST_LIST, condition, increment);
    ast* init_for = ast_new_operation(AST_LIST, init, tmp);

    ast* item_vect_a = ast_new_operation(AST_VECT_ITEM, ast_new_id(strdup("a")), ast_new_id(strdup("i")));
    ast* item_vect_b = ast_new_operation(AST_VECT_ITEM, ast_new_id(strdup("b")), ast_new_id(strdup("i")));
    ast* item_vect_c = ast_new_operation(AST_VECT_ITEM, ast_new_id(strdup("c")), ast_new_id(strdup("i")));
    tmp = ast_new_operation(AST_ADD, item_vect_a, item_vect_b);
    tmp = ast_new_operation(AST_AFFECT, item_vect_c, tmp);
    tmp = ast_new_operation(AST_LIST, tmp, NULL);
    ast* body_for = ast_new_operation(AST_BLOCK, tmp, NULL);

    return ast_new_operation(AST_FOR, init_for, body_for); 
}

ast* get_scalar_product_ast() {
    ast* tmp;

    ast* init = ast_new_operation(AST_AFFECT, ast_new_id(strdup("i")), ast_new_number(0));
    ast* condition = ast_new_operation(AST_INF, ast_new_id(strdup("i")), ast_new_id(strdup("n")));
    tmp = ast_new_operation(AST_ADD, ast_new_id(strdup("i")), ast_new_number(1));
    ast* increment = ast_new_operation(AST_AFFECT, ast_new_id(strdup("i")), tmp);
    tmp = ast_new_operation(AST_LIST, condition, increment);
    ast* init_for = ast_new_operation(AST_LIST, init, tmp);

    ast* item_vect_a = ast_new_operation(AST_VECT_ITEM, ast_new_id(strdup("a")), ast_new_id(strdup("i")));
    ast* item_vect_b = ast_new_operation(AST_VECT_ITEM, ast_new_id(strdup("b")), ast_new_id(strdup("i")));
    ast* item_vect_c = ast_new_operation(AST_VECT_ITEM, ast_new_id(strdup("c")), ast_new_id(strdup("i")));
    tmp = ast_new_operation(AST_MUL, item_vect_a, item_vect_b);
    tmp = ast_new_operation(AST_AFFECT, item_vect_c, tmp);
    tmp = ast_new_operation(AST_LIST, tmp, NULL);
    ast* body_for = ast_new_operation(AST_BLOCK, tmp, NULL);

    return ast_new_operation(AST_FOR, init_for, body_for); 
}