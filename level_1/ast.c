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
    
    if (S->type == AST_ARITH_OP) 
        return is_aithmetic_operation(T); 
    
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
        case AST_OPT_FUN_VECT_ADD:
            printf("VECTORS ADDITION\n");
            ast_print(ast->left, indent + 1);
            ast_print(ast->right, indent + 1);
            break;
        case AST_OPT_FUN_SC_PROD:
            printf("SCALAR PRODUCT\n");
            ast_print(ast->left, indent + 1);
            ast_print(ast->right, indent + 1);
            break;
        case AST_OPT_FUN_AXPY:
            printf("VECTOR AXPY\n");
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

void ast_to_source(ast* ast, int indent, char is_for) {
    int new_indent = indent;
    // Support of declaration/definition statements (e.g `int a = 3;`)
    if (ast->type == AST_LIST && ast->right != NULL && ast->left->type == AST_TYPE_INT 
        && ast->right->type == AST_AFFECT) {
        print_indent(new_indent);
        printf("int %s = ", ast->left->left->id);
        ast_to_source(ast->right->right, indent, is_for);
        printf(";\n");
        return;
    }

    switch(ast->type) {
        case AST_INCLUDE:
            printf("#include <%s>\n", ast->id);
            break;
        case AST_DEFINE:
            printf("#define ");
            break;
        case AST_MAIN:
            printf("int main(int argc, char *argv[]) ");
            break;
        case AST_BLOCK:
            printf("{\n");
            new_indent++;
            break;
        case AST_LIST:
            if (!is_for && ast->left->type != AST_LIST &&
            ast->type != AST_INCLUDE && ast->type != AST_DEFINE)
                print_indent(new_indent);
            break;
        case AST_ID:
            printf("%s", ast->id);
            break;
        case AST_NUMBER:
            printf("%d", ast->number);
            break;
        case AST_FOR:
            is_for = 1;
            printf("for (");
            break;
        case AST_WHILE:
            printf("while (");
            break;
        case AST_IF:
            printf("if (");
            break;
        case AST_ELSE_IF:
            printf("else if (");
            break;
        case AST_ELSE:
            print_indent(new_indent);
            printf("else ");
            break;
        case AST_AFFECT:
            break;
        case AST_TYPE_INT:
            printf("int ");
            break;
        case AST_TYPE_INT_VECT:
            printf("int ");
            break;
        case AST_VECT_ITEM:
            break;
        case AST_RETURN:
            printf("return ");
            break;
        default:
            printf("(");
            break;
    };

    if (ast->type != AST_INCLUDE && ast->type != AST_ID && ast->type != AST_NUMBER && ast->left != NULL)
        ast_to_source(ast->left, new_indent, is_for);

    // Adding the semicolumn after the for condition
    if (is_for && ast->type == AST_LIST && ast->left != NULL 
        && ast->left->type >= 13 && ast->left->type <= 20)
        printf(";");

    switch(ast->type) {
        case AST_TYPE_INT:
            printf(";\n");
            break;
        case AST_TYPE_INT_VECT:
            printf("[");
            break;
        case AST_VECT_ITEM:
            printf("[");
            break;
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
        case AST_AND:
            printf("&&");
            break;
        case AST_OR:
            printf("||");
            break;
        case AST_EQUAL:
            printf("==");
            break;
        case AST_DIFF:
            printf("!=");
            break;
        case AST_GEQ:
            printf(">=");
            break;
        case AST_LEQ:
            printf("<=");
            break;
        case AST_SUP:
            printf(">");
            break;
        case AST_INF:
            printf("<");
            break;
        case AST_FOR:
            printf(") ");
            is_for = 0;
            break;
        case AST_WHILE:
            printf(") ");
            break;
        case AST_IF:
            printf(") ");
            break;
        case AST_ELSE_IF:
            printf(") ");
            break;
        case AST_DEFINE:
            printf(" ");
            break;
        default:
            break;
    };

    // Using is_for as a flag to distinct the last AST_AFFECT that
    // don't have to output a semicolumn after it.
    if (is_for == 1 && ast->type == AST_LIST)
        is_for++;

    if (ast->type != AST_INCLUDE && ast->type != AST_ID && ast->type != AST_NUMBER && ast->right != NULL)
        ast_to_source(ast->right, new_indent, is_for);

    switch (ast->type) {
        case AST_DEFINE:
            printf("\n");
        break;
        case AST_TYPE_INT_VECT:
            printf("];\n");
            break;
        case AST_VECT_ITEM:
            printf("]");
            break;
        case AST_AFFECT:
            if (is_for < 2)
                printf(";");
            if (!is_for)
                printf("\n");
            break;
        case AST_BLOCK:
            new_indent--;
            print_indent(new_indent);
            printf("}\n");
            break;
        case AST_RETURN:
            printf(";\n");
            break;
        default:
            break;
    }
    if ((ast->type >= 8 && ast->type <= 11) || (ast->type >= 13 && ast->type <= 20))
        printf(")");
}