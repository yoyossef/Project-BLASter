#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "optimizer.h"  


void variable_is_replaceable_private(char* argument, ast* source, ast* function, symbol* table, opt_symbol* reference) {
    symbol* tmp;

    if (!reference->is_same_symbol || source == NULL || function == NULL)
        return;

    switch (source->type)
    {
        case AST_NUMBER:
            break;
        case AST_INCLUDE:
            break;
        case AST_ID:
            if (strcmp(argument, function->id) == 0) {
                tmp = symbol_lookup(table, source->id);
                if (reference->symbol != NULL && tmp != reference->symbol) {
                    reference->is_same_symbol =0;
                    reference->symbol = NULL;
                    return;
                }
                reference->symbol = tmp;
            }
            break;
        default:
            variable_is_replaceable_private(argument, source->left, function->left, table, reference);
            variable_is_replaceable_private(argument, source->right, function->right, table, reference);
            break;
    }
}

int variable_is_replaceable(char* argument, ast* source, ast* function, symbol* table) {
    opt_symbol* tmp;
    int result;   

    tmp = malloc(sizeof(struct opt_symbol)); 
    tmp->is_same_symbol = 1;
    tmp->symbol = NULL;
    variable_is_replaceable_private(argument, source, function, table, tmp);
    result = (tmp->is_same_symbol) ? 1 : 0;
    free(tmp);

    return result;
}

int variables_are_replaceable(ast* variables, ast* source, ast* function, symbol* table) {
    if (variables == NULL)
        return 1;
    
    if (variables->type == AST_ID)
        return variable_is_replaceable(variables->id, source, function, table);

    if (variables->type == AST_LIST)
        return variables_are_replaceable(variables->left, source, function, table) &&
            variables_are_replaceable(variables->right, source, function, table);
    
    return 0;
}

char* get_argument(char* argument, ast* source, ast* function) {
    char* tmp = NULL;
    switch (source->type)
    {
        case AST_NUMBER:
            break;
        case AST_INCLUDE:
            break;
        case AST_ID:
            if (strcmp(argument, function->id) == 0) 
                tmp = strdup(source->id);
            break;
        default:
            tmp = get_argument(argument, source->left, function->left);
            if (tmp == NULL)
                tmp = get_argument(argument, source->right, function->right);
            break;
    }

    return tmp;
}

ast* replace_private(ast* arguments, ast* source, ast* function) {
    ast* result = NULL;
    char* argument;
    
    if (arguments->type == AST_ID) {
        argument = get_argument(arguments->id, source, function);
        result = ast_new_id(argument);
    }
    
    if (arguments->type == AST_LIST) {
        result = ast_new_operation(AST_LIST, replace_private(arguments->left, source, function), replace_private(arguments->right, source, function));
    }

    return result;
}

ast* replace(ast* source, ast* function) {
    ast* function_name;
    ast* arguments;
    ast* function_body;

    function_name = ast_new_id(strdup(function->left->left->id));
    arguments = function->left->right;
    function_body = function->right->left->left;

    return ast_new_operation(AST_FUN, function_name, replace_private(arguments, source, function_body));
}

void optimize_function(ast* source, ast* function, symbol* table) {
    if (source == NULL)
        return; 

    if (source->type == AST_NUMBER || source->type == AST_ID || source->type == AST_INCLUDE || source->type == AST_FUN) 
        return; 

    if (source->type == AST_LIST) {
        if (are_identical(source->left, function->right->left->left)) {
            ast* function_body = function->right->left->left;
            ast* arguments = function->left->right;
            ast* tmp;

            if (variables_are_replaceable(arguments, source->left, function_body, table)) {
                tmp = replace(source->left, function);
                ast_free(source->left);
                source->left = tmp;
            }
        }

        optimize_function(source->right, function, table);
        return;
    }
    
    optimize_function(source->left, function, table);
    optimize_function(source->right, function, table);
}

void optimize(ast* source, ast* library, symbol* table) {
    if (library == NULL)
        return; 

    if (library->type == AST_NUMBER || library->type == AST_ID || library->type == AST_INCLUDE) 
        return; 
    
    if (library->type == AST_FUN) {
        optimize_function(source, library, table);
        return;
    }

    optimize(source, library->left, table);
    optimize(source, library->right, table);
}