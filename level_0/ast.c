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

void ast_free(ast* ast) {
    if (ast != NULL) {
        switch (ast->type) {
            case AST_NUMBER:
                break;
            case AST_ID:
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
        case AST_ID:
            printf("ID (%s)\n", ast->id);
            break;
        case AST_NUMBER:
            printf("NUMBER (%d)\n", ast->number);
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
    };
}

void print_indent(int indent) {
    if (indent == 0)
        return;
    for (int i = 0; i < indent; i++)
        printf("\t");
}

void ast_to_source(ast* ast, int indent) {
    int new_indent = indent;

    // AST_ADD, AST_SUB, AST_MUL, AST_DIV
    if (ast->type >= 2 && ast->type <= 5)
        printf("(");

    switch(ast->type) {
        case AST_BLOCK:
            printf("{\n");
            new_indent++;
            break;
        case AST_LIST:
            print_indent(new_indent);
            break;
        case AST_ID:
            printf("%s", ast->id);
            break;
        case AST_NUMBER:
            printf("%d", ast->number);
            break;
        case AST_FOR:
            printf("for");
            break;
        case AST_WHILE:
            printf("while");
            break;
        case AST_IF:
            printf("if");
            break;
        case AST_ELSE:
            printf("else");
            break;
        case AST_ELSE_IF:
            printf("else if");
            break;
        default:
            break;
    };

    if (ast->type != AST_ID && ast->type != AST_NUMBER && ast->left != NULL)
        ast_to_source(ast->left, new_indent);

    switch(ast->type) {
        case AST_ADD:
            printf("+");
            break;
        case AST_SUB:
            printf("-");
            break;
        case AST_MUL:
            printf("*");
            break;
        case AST_DIV:
            printf("/");
            break;
        case AST_AFFECT:
            printf("=");
            break;
        default:
            break;
    };

    if (ast->type != AST_ID && ast->type != AST_NUMBER && ast->right != NULL)
        ast_to_source(ast->right, new_indent);

    switch (ast->type) {
        case AST_BLOCK:
            new_indent--;
            print_indent(new_indent);
            printf("}\n");
            break;
        case AST_AFFECT:
            printf(";\n");
        default:
            break;
    }

    if (ast->type >= 2 && ast->type <= 5)
        printf(")");
}