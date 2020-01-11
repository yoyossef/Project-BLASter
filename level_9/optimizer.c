#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "optimizer.h"  


void variable_is_replaceable_private(char* variable, ast* source, ast* function, symbol* table, opt_symbol* reference) {
    symbol* tmp;

    if (!reference->is_same_symbol || source == NULL || function == NULL)
        return;

    if (source->type == AST_NUMBER || source->type == AST_INCLUDE)
        return;
    
    if (function->type == AST_ID) {
        if (strcmp(variable, function->id) == 0) {
            tmp = symbol_lookup(table, source->id);
            if (reference->symbol != NULL && tmp != reference->symbol) {
                reference->is_same_symbol =0;
                reference->symbol = NULL;
                return;
            }
            reference->symbol = tmp;
        }
        return;
    }

    variable_is_replaceable_private(variable, source->left, function->left, table, reference);
    variable_is_replaceable_private(variable, source->right, function->right, table, reference);
}

int variable_is_replaceable(char* variable, ast* source, ast* function, symbol* table) {
    opt_symbol* tmp;
    int result;   

    tmp = malloc(sizeof(struct opt_symbol)); 
    tmp->is_same_symbol = 1;
    tmp->symbol = NULL;
    variable_is_replaceable_private(variable, source, function, table, tmp);
    result = (tmp->is_same_symbol) ? 1 : 0;
    free(tmp);

    return result;
}

int variables_are_replaceable(ast* source, ast* function, symbol* table) {
    int result = 1;
    symbol *variable = NULL, *tmp = NULL;
    symbol_build_table(function, &tmp);
    variable = tmp;

    while (result && variable != NULL) {
        result = variable_is_replaceable(variable->identifier, source, function, table);
        variable = variable->next;
    }
    symbol_free(tmp);

    return result;
}

ast* get_argument(char* argument, ast* source, ast* function) {
    ast* tmp = NULL;

    if (function == NULL)
        return NULL;
        
    switch (function->type) {
        case AST_NUMBER:
            break;
        case AST_INCLUDE:
            break;
        case AST_ID:
            if (strcmp(argument, function->id) == 0) 
                tmp = ast_copy(source);
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
    
    if (arguments->type == AST_ID) {
        result = get_argument(arguments->id, source, function);
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
        if (are_similar(source->left, function->right->left->left)) {
            ast* function_body = function->right->left->left;
            ast* tmp;

            if (variables_are_replaceable(source->left, function_body, table)) {
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