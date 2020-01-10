#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

ast* ast_new_operation(ast_type type, ast* left, ast* right) {
    ast* new = malloc(sizeof(ast));
    new->type = type;
    new->left = left;
    new->right = right;
    return new;
}

ast* ast_new_number(int number) {
    ast* new = malloc(sizeof(ast));
    new->type = AST_NUMBER;
    new->number = number;
    return new;
}

ast* ast_new_id(char* id) {
    ast* new = malloc(sizeof(ast));
    new->type = AST_ID;
    new->id = id;
    return new;
}

ast* ast_new_include(char* id) {
    ast* new = malloc(sizeof(ast));
    new->type = AST_INCLUDE;
    new->id = id;
    return new;
}

int is_aithmetic_operation(ast* T) {
    if (T == NULL)
        return 0;
    if (T->type == AST_INCLUDE) 
        return 0; 
    if (T->type == AST_NUMBER || T->type == AST_ID) 
        return 1; 
    if (T->type == AST_ADD || T->type == AST_SUB || T->type == AST_MUL || T->type == AST_DIV) 
        return is_aithmetic_operation(T->left) || is_aithmetic_operation(T->right); 

    return 0;
}

int are_identical(ast* T, ast* S) {
    if (T == NULL && S == NULL) 
        return 1; 
  
    if (T == NULL || S == NULL) 
        return 0; 
    
    if ((T->type == AST_NUMBER || T->type == AST_ID || T->type == AST_INCLUDE) && (T->type == S->type)) 
        return 1; 

    return (T->type == S->type && are_identical(T->left, S->left) && are_identical(T->right, S->right) ); 
}

void ast_free(ast* ast) {
    if (ast != NULL) {
        switch (ast->type) {
            case AST_NUMBER:
                break;
            case AST_ID:
                free(ast->id);
                break;
            case AST_INCLUDE:
                free(ast->id);
                break;
            default:
                ast_free(ast->left);
                ast_free(ast->right);
                break;
        }
    }
    free(ast);
}

void ast_print(ast* ast, int indent) {
    print_indent(indent);
    if (ast == NULL) {
        printf("NULL\n");
        return ;
    }

    switch(ast->type) {
        case AST_INCLUDE:
            printf("INCLUDE (%s)\n", ast->id);
            break;
        case AST_DEFINE:
            printf("DEFINE\n");
            ast_print(ast->left, indent + 1);
            ast_print(ast->right, indent + 1);
            break;
        case AST_MAIN:
            printf("MAIN\n");
            ast_print(ast->left, indent + 1);
            ast_print(ast->right, indent + 1);
            break;
        case AST_FUN:
            printf("FUN\n");
            ast_print(ast->left, indent + 1);
            ast_print(ast->right, indent + 1);
            break;
        case AST_RETURN:
            printf("RETURN\n");
            ast_print(ast->left, indent + 1);
            ast_print(ast->right, indent + 1);
            break;
        case AST_ID:
            printf("ID (%s)\n", ast->id);
            break;
        case AST_NUMBER:
            printf("NUMBER (%d)\n", ast->number);
            break;
        case AST_TYPE_INT_VECT:
            printf("INT VECTOR\n");
            ast_print(ast->left, indent + 1);
            ast_print(ast->right, indent + 1);
            break;
        case AST_VECT_ITEM:
            printf("ITEM VECTOR\n");
            ast_print(ast->left, indent + 1);
            ast_print(ast->right, indent + 1);
            break;
        case AST_ADD:
            printf("+\n");
            ast_print(ast->left, indent + 1);
            ast_print(ast->right, indent + 1);
            break;
        case AST_SUB:
            printf("-\n");
            ast_print(ast->left, indent + 1);
            ast_print(ast->right, indent + 1);
            break;
        case AST_MUL:
            printf("*\n");
            ast_print(ast->left, indent + 1);
            ast_print(ast->right, indent + 1);
            break;
        case AST_DIV:
            printf("/\n");
            ast_print(ast->left, indent + 1);
            ast_print(ast->right, indent + 1);
            break;
        case AST_TYPE_INT:
            printf("TYPE_INT\n");
            ast_print(ast->left, indent + 1);
            ast_print(ast->right, indent + 1);
            break;
        case AST_AFFECT:
            printf("=\n");
            ast_print(ast->left, indent + 1);
            ast_print(ast->right, indent + 1);
            break;
        case AST_INCREMENT:
            printf("++\n");
            ast_print(ast->left, indent + 1);
            ast_print(ast->right, indent + 1);
            break;
        case AST_EQUAL:
            printf("==\n");
            ast_print(ast->left, indent + 1);
            ast_print(ast->right, indent + 1);
            break;
        case AST_DIFF:
            printf("!=\n");
            ast_print(ast->left, indent + 1);
            ast_print(ast->right, indent + 1);
            break;
        case AST_GEQ:
            printf(">=\n");
            ast_print(ast->left, indent + 1);
            ast_print(ast->right, indent + 1);
            break;
        case AST_LEQ:
            printf("<=\n");
            ast_print(ast->left, indent + 1);
            ast_print(ast->right, indent + 1);
            break;
        case AST_SUP:
            printf(">\n");
            ast_print(ast->left, indent + 1);
            ast_print(ast->right, indent + 1);
            break;
        case AST_INF:
            printf("<\n");
            ast_print(ast->left, indent + 1);
            ast_print(ast->right, indent + 1);
            break;
        case AST_AND:
            printf("&&\n");
            ast_print(ast->left, indent + 1);
            ast_print(ast->right, indent + 1);
            break;
        case AST_OR:
            printf("||\n");
            ast_print(ast->left, indent + 1);
            ast_print(ast->right, indent + 1);
            break;
        case AST_FOR:
            printf("for\n");
            ast_print(ast->left, indent + 1);
            ast_print(ast->right, indent + 1);
            break;
        case AST_WHILE:
            printf("while\n");
            ast_print(ast->left, indent + 1);
            ast_print(ast->right, indent + 1);
            break;
        case AST_IF:
            printf("if\n");
            ast_print(ast->left, indent + 1);
            ast_print(ast->right, indent + 1);
            break;
        case AST_ELSE:
            printf("else\n");
            ast_print(ast->left, indent + 1);
            ast_print(ast->right, indent + 1);
            break;
        case AST_ELSE_IF:
            printf("else if\n");
            ast_print(ast->left, indent + 1);
            ast_print(ast->right, indent + 1);
            break;
        case AST_LIST:
            printf("list\n");
            ast_print(ast->left, indent + 1);
            ast_print(ast->right, indent);
            break;
        case AST_BLOCK:
            printf("block\n");
            ast_print(ast->left, indent + 1);
            break;
        default:
            break;
    };
}

void print_indent(int indent) {
    if (indent == 0)
        return;
    for (int i = 0; i < indent; i++)
        printf("\t");
}