#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "optimizer.h"    
#include "ast_library.h"


ast* replace_by_addition(ast* T) {
    ast* vect_c = ast_new_id(strdup(T->right->left->left->left->left->id));
    ast* vect_a = ast_new_id(strdup(T->right->left->left->right->left->left->id));
    ast* vect_b = ast_new_id(strdup(T->right->left->left->right->right->left->id));
    
    return ast_new_operation(AST_AFFECT, vect_c, ast_new_operation(AST_OPT_FUN_VECT_ADD, vect_a, vect_b));
}

ast* replace_by_scalar_product(ast* T) {
    ast* vect_c = ast_new_id(strdup(T->right->left->left->left->left->id));
    ast* vect_a = ast_new_id(strdup(T->right->left->left->right->left->left->id));
    ast* vect_b = ast_new_id(strdup(T->right->left->left->right->right->left->id));
    
    return ast_new_operation(AST_AFFECT, vect_c, ast_new_operation(AST_OPT_FUN_SC_PROD, vect_a, vect_b));
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
            case '+':
                tmp = replace_by_addition(T->left);
                ast_free(T->left);
                T->left = tmp;
                break;
            case '.':
                tmp = replace_by_scalar_product(T->left);
                ast_free(T->left);
                T->left = tmp;
                break;
            default:
                break;
        }
        return ; 
    }
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

void optimize_level_1(ast* T) {
    optimize_addition(T);
    optimize_scalar_product(T);
}