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
  new->id = strdup(id);
  return new;
}

void ast_free(ast* ast) {
    switch (ast->type) {
        case AST_NUMBER:
            break;
        case AST_ID:
            free(ast->id);
            break;
        case AST_ADD:
            ast_free(ast->left);
            ast_free(ast->right);
            break;
        case AST_AFFECT:
            ast_free(ast->left);
            ast_free(ast->right);
            break;
        case AST_SUB:
            ast_free(ast->left);
            ast_free(ast->right);
            break;
        case AST_MUL:
            ast_free(ast->left);
            ast_free(ast->right);
            break;
        case AST_DIV:
            ast_free(ast->left);
            ast_free(ast->right);
            break;
    }
    free(ast);
}

void ast_print(ast* ast, int indent) {
    for (int i = 0; i < indent; i++)
        printf("    ");
    switch(ast->type) {
        case AST_ID:
            printf("ID (%s)\n", ast->id);
            break;
        case AST_NUMBER:
            printf("NUMBER (%d)\n", ast->number);
            break;
        case AST_AFFECT:
            printf("=\n");
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
    };
}
