#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "optimizer.h"    
#include "ast_library.h"


ast* replace_by_set(ast* T) {
    ast* l0 = T->left->left->right;
    ast* hi = T->left->right->left->right;
    ast* val = T->right->left->left->right;
    ast* vect_v = ast_new_id(strdup(T->right->left->left->left->left->id));

    ast* tmp = ast_new_operation(AST_LIST, vect_v, val);
    tmp = ast_new_operation(AST_LIST, hi, tmp);
    
    T->left->left->right = NULL;
    T->left->right->left->right = NULL;
    T->right->left->left->right = NULL;

    return ast_new_operation(AST_OPT_FUN_VECT_SET, l0, tmp);
}

ast* replace_by_swap(ast* T) {
    char* v2_1 = T->right->left->left->right->right->left->id;
    char* v2_2 = T->right->left->right->left->left->left->id;
    char* v1_1 = T->right->left->right->left->right->left->id;
    char* v1_2 = T->right->left->right->right->left->left->left->id;

    char* i1 = T->right->left->left->right->right->right->id;
    char* i2 = T->right->left->right->left->left->right->id;  
    char* i3 = T->right->left->right->left->right->right->id; 
    char* i4 = T->right->left->right->right->left->left->right->id; 

    if (strcmp(i1, i2) != 0 || strcmp(i1, i3) != 0 || strcmp(i1, i4) != 0 || strcmp(v2_1, v2_2) != 0 || strcmp(v1_1, v1_2) != 0)
        return NULL; 

    ast* l0 = T->left->left->right;
    ast* hi = T->left->right->left->right;
    ast* vect_v1 = ast_new_id(strdup(v1_1));
    ast* vect_v2 = ast_new_id(strdup(v2_1));

    ast* tmp = ast_new_operation(AST_LIST, vect_v1, vect_v2);
    tmp = ast_new_operation(AST_LIST, hi, tmp);
    
    T->left->left->right = NULL;
    T->left->right->left->right = NULL;

    return ast_new_operation(AST_OPT_FUN_VECT_SWAP, l0, tmp);
}

ast* replace_by_addition(ast* T) {
    char* i1 = T->right->left->left->right->left->right->id;
    char* i2 = T->right->left->left->right->right->right->id;
    char* i3 = T->right->left->left->left->right->id;
    
    if (strcmp(i1, i2) != 0 || strcmp(i1, i3) != 0)
        return NULL;

    ast* l0 = T->left->left->right;
    ast* hi = T->left->right->left->right;
    ast* vect_a = ast_new_id(strdup(T->right->left->left->right->left->left->id));
    ast* vect_b = ast_new_id(strdup(T->right->left->left->right->right->left->id));
    ast* vect_c = ast_new_id(strdup(T->right->left->left->left->left->id));

    ast* tmp = ast_new_operation(AST_LIST, vect_b, vect_c);
    tmp = ast_new_operation(AST_LIST, vect_a, tmp);
    tmp = ast_new_operation(AST_LIST, hi, tmp);
    
    T->left->left->right = NULL;
    T->left->right->left->right = NULL;

    return ast_new_operation(AST_OPT_FUN_VECT_ADD, l0, tmp);
}

ast* replace_by_scalar_product(ast* T) {
    char* i1 = T->right->left->left->right->left->right->id;
    char* i2 = T->right->left->left->right->right->right->id;
    char* i3 = T->right->left->left->left->right->id;
    
    if (strcmp(i1, i2) != 0 || strcmp(i1, i3) != 0)
        return NULL;

    ast* l0 = T->left->left->right;
    ast* hi = T->left->right->left->right;
    ast* vect_a = ast_new_id(strdup(T->right->left->left->right->left->left->id));
    ast* vect_b = ast_new_id(strdup(T->right->left->left->right->right->left->id));
    ast* vect_c = ast_new_id(strdup(T->right->left->left->left->left->id));

    ast* tmp = ast_new_operation(AST_LIST, vect_b, vect_c);
    tmp = ast_new_operation(AST_LIST, vect_a, tmp);
    tmp = ast_new_operation(AST_LIST, hi, tmp);
    
    T->left->left->right = NULL;
    T->left->right->left->right = NULL;

    return ast_new_operation(AST_OPT_FUN_SC_PROD, l0, tmp);
}

ast* replace_by_axpy(ast* T) {
    char* y1 = T->right->left->left->left->left->id;
    char* y2 = T->right->left->left->right->right->left->id;

    char* i1 = T->right->left->left->right->right->right->id;
    char* i2 = T->right->left->left->left->right->id;
    char* i3 = T->right->left->left->right->left->right->right->id;

    if (strcmp(y1, y2) != 0 || strcmp(i1, i2) != 0 || strcmp(i1, i3) != 0)
        return NULL;

    ast* l0 = T->left->left->right;
    ast* hi = T->left->right->left->right;
    ast* vect_y = ast_new_id(strdup(T->right->left->left->left->left->id));
    ast* alpha = T->right->left->left->right->left->left;
    ast* vect_x = ast_new_id(strdup(T->right->left->left->right->left->right->left->id));

    ast* tmp = ast_new_operation(AST_LIST, vect_x, vect_y);
    tmp = ast_new_operation(AST_LIST, alpha, tmp);
    tmp = ast_new_operation(AST_LIST, hi, tmp);
    
    T->left->left->right = NULL;
    T->left->right->left->right = NULL;
    T->right->left->left->right->left->left = NULL;
    
    return ast_new_operation(AST_OPT_FUN_AXPY, l0, tmp);
}

void optimize(ast* T, ast* S, char operation) {
    if (S == NULL)
        return ; 
  
    if (T == NULL)
        return ; 

    if (T->type == AST_NUMBER || T->type == AST_ID || T->type == AST_INCLUDE) 
        return ; 
  
    optimize(T->left, S, operation); 
    optimize(T->right, S, operation); 
  
    if (are_identical(T->left, S)) {
        ast* tmp;
        switch (operation)
        {
            case 's':
                tmp = replace_by_set(T->left);
                if (tmp != NULL) {
                    ast_free(T->left);
                    T->left = tmp;
                }
                break;
            case 'w':
                tmp = replace_by_swap(T->left);
                if (tmp != NULL) {
                    ast_free(T->left);
                    T->left = tmp;
                }
                break;
            case '+':
                tmp = replace_by_addition(T->left);
                if (tmp != NULL) {
                    ast_free(T->left);
                    T->left = tmp;
                }
                break;
            case '.':
                tmp = replace_by_scalar_product(T->left);
                if (tmp != NULL) {
                    ast_free(T->left);
                    T->left = tmp;
                }
                break;
            case 'g':
                tmp = replace_by_axpy(T->left);
                if (tmp != NULL) {
                    ast_free(T->left);
                    T->left = tmp;
                }
                break;
            default:
                break;
        }
        return ; 
    }
}

void optimize_set(ast* T) {
    ast* set_ast = get_set_ast();
    optimize(T, set_ast, 's');

    ast_free(set_ast);
}

void optimize_swap(ast* T) {
    ast* swap_ast = get_swap_ast();
    optimize(T, swap_ast, 'w');

    ast_free(swap_ast);
}

void optimize_addition(ast* T) {
    ast* addition_ast = get_addition_ast();
    optimize(T, addition_ast, '+');

    ast_free(addition_ast);
}

void optimize_scalar_product(ast* T) {
    ast* scalar_product_ast = get_scalar_product_ast();
    optimize(T, scalar_product_ast, '.');

    ast_free(scalar_product_ast);
}

void optimize_axpy(ast* T) {
    ast* axpy_ast = get_axpy_ast();
    optimize(T, axpy_ast, 'g');

    ast_free(axpy_ast);
}

void optimize_level_1(ast* T) {
    optimize_set(T);
    optimize_swap(T);
    optimize_addition(T);
    optimize_scalar_product(T);
    optimize_axpy(T);
}