#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast_library.h"


ast* get_set_ast() {
    ast* tmp;

    ast* init = ast_new_operation(AST_AFFECT, ast_new_id(strdup("i")), ast_new_operation(AST_ARITH_OP, NULL, NULL));
    ast* condition = ast_new_operation(AST_INF, ast_new_id(strdup("i")), ast_new_operation(AST_ARITH_OP, NULL, NULL));
    ast* increment = ast_new_operation(AST_INCREMENT, ast_new_id("i"), ast_new_number(1));
    tmp = ast_new_operation(AST_LIST, condition, increment);
    ast* init_for = ast_new_operation(AST_LIST, init, tmp);

    ast* item_vect_v = ast_new_operation(AST_VECT_ITEM, ast_new_id(strdup("c")), ast_new_id(strdup("i")));
    ast* val = ast_new_operation(AST_ARITH_OP, NULL, NULL);
    tmp = ast_new_operation(AST_AFFECT, item_vect_v, val);
    tmp = ast_new_operation(AST_LIST, tmp, NULL);
    ast* body_for = ast_new_operation(AST_BLOCK, tmp, NULL);

    return ast_new_operation(AST_FOR, init_for, body_for); 
}

ast* get_swap_ast() {
    ast* tmp;
    ast* tmp1;
    ast* tmp2;
    ast* tmp3;

    ast* init = ast_new_operation(AST_AFFECT, ast_new_id(strdup("i")), ast_new_operation(AST_ARITH_OP, NULL, NULL));
    ast* condition = ast_new_operation(AST_INF, ast_new_id(strdup("i")), ast_new_operation(AST_ARITH_OP, NULL, NULL));
    ast* increment = ast_new_operation(AST_INCREMENT, ast_new_id("i"), ast_new_number(1));
    tmp1 = ast_new_operation(AST_LIST, condition, increment);
    ast* init_for = ast_new_operation(AST_LIST, init, tmp1);

    ast* int_tmp = ast_new_operation(AST_TYPE_INT, ast_new_id("tmp"), NULL);
    ast* item_vect_v2_1 = ast_new_operation(AST_VECT_ITEM, ast_new_id(strdup("v2")), ast_new_id(strdup("i")));
    ast* item_vect_v2_2 = ast_new_operation(AST_VECT_ITEM, ast_new_id(strdup("v2")), ast_new_id(strdup("i")));
    ast* item_vect_v1_1 = ast_new_operation(AST_VECT_ITEM, ast_new_id(strdup("v1")), ast_new_id(strdup("i")));
    ast* item_vect_v1_2 = ast_new_operation(AST_VECT_ITEM, ast_new_id(strdup("v1")), ast_new_id(strdup("i")));
    tmp1 = ast_new_operation(AST_AFFECT, ast_new_id("tmp"), item_vect_v2_1);
    tmp2 = ast_new_operation(AST_AFFECT, item_vect_v2_2, item_vect_v1_1);
    tmp3 = ast_new_operation(AST_AFFECT, item_vect_v1_2, ast_new_id("tmp"));
    tmp = ast_new_operation(AST_LIST, tmp3, NULL);
    tmp = ast_new_operation(AST_LIST, tmp2, tmp);
    tmp1 = ast_new_operation(AST_LIST, int_tmp, tmp1);
    tmp = ast_new_operation(AST_LIST, tmp1, tmp);
    ast* body_for = ast_new_operation(AST_BLOCK, tmp, NULL);

    return ast_new_operation(AST_FOR, init_for, body_for); 
}

ast* get_addition_ast() {
    ast* tmp;

    ast* init = ast_new_operation(AST_AFFECT, ast_new_id(strdup("i")), ast_new_operation(AST_ARITH_OP, NULL, NULL));
    ast* condition = ast_new_operation(AST_INF, ast_new_id(strdup("i")), ast_new_operation(AST_ARITH_OP, NULL, NULL));
    ast* increment = ast_new_operation(AST_INCREMENT, ast_new_id("i"), ast_new_number(1));
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

    ast* init = ast_new_operation(AST_AFFECT, ast_new_id(strdup("i")), ast_new_operation(AST_ARITH_OP, NULL, NULL));
    ast* condition = ast_new_operation(AST_INF, ast_new_id(strdup("i")), ast_new_operation(AST_ARITH_OP, NULL, NULL));
    ast* increment = ast_new_operation(AST_INCREMENT, ast_new_id("i"), ast_new_number(1));
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

ast* get_axpy_ast() {
    ast* tmp;

    ast* init = ast_new_operation(AST_AFFECT, ast_new_id(strdup("i")), ast_new_operation(AST_ARITH_OP, NULL, NULL));
    ast* condition = ast_new_operation(AST_INF, ast_new_id(strdup("i")), ast_new_operation(AST_ARITH_OP, NULL, NULL));
    ast* increment = ast_new_operation(AST_INCREMENT, ast_new_id("i"), ast_new_number(1));
    tmp = ast_new_operation(AST_LIST, condition, increment);
    ast* init_for = ast_new_operation(AST_LIST, init, tmp);

    ast* item_vect_y1 = ast_new_operation(AST_VECT_ITEM, ast_new_id(strdup("y")), ast_new_id(strdup("i")));
    ast* alpha = ast_new_operation(AST_ARITH_OP, NULL, NULL);
    ast* item_vect_x = ast_new_operation(AST_VECT_ITEM, ast_new_id(strdup("x")), ast_new_id(strdup("i")));
    ast* item_vect_y2 = ast_new_operation(AST_VECT_ITEM, ast_new_id(strdup("y")), ast_new_id(strdup("i")));
    tmp = ast_new_operation(AST_MUL, alpha, item_vect_x);
    tmp = ast_new_operation(AST_ADD, tmp, item_vect_y2);
    tmp = ast_new_operation(AST_AFFECT, item_vect_y1, tmp);
    tmp = ast_new_operation(AST_LIST, tmp, NULL);
    ast* body_for = ast_new_operation(AST_BLOCK, tmp, NULL);

    return ast_new_operation(AST_FOR, init_for, body_for); 
}