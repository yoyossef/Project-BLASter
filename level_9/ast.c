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

ast* ast_copy(ast* T) {
    ast* result = NULL;
    if (T == NULL)
        return NULL;

    switch (T->type)
    {
        case AST_NUMBER:
            result = ast_new_number(T->number);
            break;
        case AST_ID:
            result = ast_new_id(strdup(T->id));
            break;
        case AST_INCLUDE:
            result = ast_new_include(strdup(T->id));
            break;
        default:
            result = ast_new_operation(T->type, ast_copy(T->left), ast_copy(T->right));
            break;
    }

    return result;
}

int is_arithmetic_operation(ast* T) {
    if (T == NULL)
        return 0;
    if (T->type == AST_INCLUDE || T->type == AST_VECT_ITEM || T->type == AST_MAT_ITEM) 
        return 0; 
    if (T->type == AST_NUMBER || T->type == AST_ID) 
        return 1; 
    if (T->type == AST_ADD || T->type == AST_SUB || T->type == AST_MUL || T->type == AST_DIV) 
        return is_arithmetic_operation(T->left) && is_arithmetic_operation(T->right); 

    return 0;
}

int are_similar(ast* T, ast* S) {
    if (T == NULL && S == NULL) 
        return 1; 
  
    if (T == NULL || S == NULL) 
        return 0; 
    
    if ((T->type == AST_NUMBER || T->type == AST_ID || T->type == AST_INCLUDE) && (T->type == S->type)) 
        return 1; 
    
    if (S->type == AST_ID) 
        return is_arithmetic_operation(T);

    return (T->type == S->type && are_similar(T->left, S->left) && are_similar(T->right, S->right) ); 
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
        case AST_TYPE_INT_MAT:
            printf("INT MATRIX\n");
            ast_print(ast->left, indent + 1);
            ast_print(ast->right, indent + 1);
            break;
        case AST_MAT_ITEM:
            printf("ITEM MATRIX\n");
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

void fprint_indent(int indent, FILE* flux) {
    if (indent == 0)
        return;
    for (int i = 0; i < indent; i++)
        fprintf(flux, "\t");
}

void print_include(ast* T, FILE* flux){
    if (T == NULL)
        return;

    switch (T->type) {
        case AST_INCLUDE:
            fprintf(flux,"#include <%s>\n", T->id);
            return;
            break;
        case AST_LIST:
            break;
        default:
            return;
            break;
    }
    print_include(T->left, flux);
    print_include(T->right, flux);
}

void ast_parse_opt_fun(ast* T, FILE* flux) {
    if (T == NULL)
        return;
    switch(T->type) {
        case AST_FUN:
            fprintf(flux,"%s(", T->left->id);
            ast_parse_opt_fun(T->right, flux);
            fprintf(flux,");\n");
            break;
        case AST_LIST:
            ast_parse_opt_fun(T->left, flux);
            fprintf(flux,", ");
            ast_parse_opt_fun(T->right, flux);
            break;
        default:
            ast_to_source(T, 0, 0, flux);
            break;
    }
}

void ast_parse_mat(ast* T, FILE* flux) {
    if (T == NULL)
        return;
    switch (T->type) {
        case AST_TYPE_INT_MAT:
            fprintf(flux,"int %s[", T->left->id);
            ast_parse_mat(T->right, flux);
            fprintf(flux, ";\n");
            break;
        case AST_MAT_ITEM:
            fprintf(flux, "%s[", T->left->id);
            ast_parse_mat(T->right, flux);
            break;
        case AST_LIST:
            ast_parse_mat(T->left, flux);
            fprintf(flux,"][");
            ast_parse_mat(T->right, flux);
            fprintf(flux,"]");
            break;
        default:
            ast_to_source(T, 0, 0, flux);
            break;
    }
}

char is_arith_op(ast* T) {
    if (T->type == AST_ADD || T->type == AST_SUB || 
        T->type == AST_MUL || T->type == AST_DIV)
        return 1;
    else
        return 0;
}
char is_bool_op(ast* T) {
    if (T->type == AST_AND || T->type == AST_OR || T->type == AST_EQUAL
        || T->type == AST_DIFF || T->type == AST_GEQ || T->type == AST_LEQ 
        || T->type == AST_SUP || T->type == AST_INF)
        return 1;
    else 
        return 0;
}

void ast_to_source(ast* ast, int indent, char is_for, FILE* flux) {
    int new_indent = indent;
    // Support of declaration/definition statements (e.g `int a = 3;`)
    if (ast->type == AST_LIST && ast->right != NULL && ast->left->type == AST_TYPE_INT 
        && ast->right->type == AST_AFFECT) {
        fprint_indent(new_indent, flux);
        fprintf(flux,"int %s = ", ast->left->left->id);
        ast_to_source(ast->right->right, indent, is_for, flux);
        fprintf(flux,";\n");
        return;
    }

    switch(ast->type) {
        case AST_INCLUDE:
            fprintf(flux,"#include <%s>\n", ast->id);
            break;
        case AST_DEFINE:
            fprintf(flux,"#define ");
            break;
        case AST_MAIN:
            fprintf(flux,"int main() ");
            break;
        case AST_FUN:
            ast_parse_opt_fun(ast, flux);
            return;
            break;
        case AST_ID:
            fprintf(flux,"%s", ast->id);
            break;
        case AST_NUMBER:
            fprintf(flux,"%d", ast->number);
            break;
        case AST_TYPE_INT:
            fprintf(flux,"int ");
            break;
        case AST_TYPE_INT_VECT:
            fprintf(flux,"int ");
            break;
        case AST_VECT_ITEM:
            break;
        case AST_TYPE_INT_MAT:
            ast_parse_mat(ast, flux);
            return;
            break;
        case AST_MAT_ITEM:
            ast_parse_mat(ast, flux);
            return;
            break;
        case AST_AFFECT:
            break;
        case AST_INCREMENT:
            break;
        case AST_FOR:
            is_for = 1;
            fprintf(flux,"for (");
            break;
        case AST_WHILE:
            fprintf(flux,"while (");
            break;
        case AST_IF:
            fprintf(flux,"if (");
            break;
        case AST_ELSE_IF:
            fprintf(flux,"else if (");
            break;
        case AST_ELSE:
            fprint_indent(new_indent, flux);
            fprintf(flux,"else ");
            break;
        case AST_LIST:
            if (!is_for && ast->left->type != AST_LIST)
                fprint_indent(new_indent, flux);
            break;
        case AST_BLOCK:
            fprintf(flux,"{\n");
            new_indent++;
            break;
        case AST_RETURN:
            fprintf(flux,"return ");
            break;
        default:
            fprintf(flux,"(");
            break;
    };

    if (ast->type != AST_INCLUDE && ast->type != AST_ID && ast->type != AST_NUMBER && ast->left != NULL)
        ast_to_source(ast->left, new_indent, is_for, flux);

    // Adding the semicolumn after the for condition
    if (is_for && ast->type == AST_LIST && ast->left != NULL && is_bool_op(ast->left))
        fprintf(flux,";");

    switch(ast->type) {
        case AST_TYPE_INT:
            fprintf(flux,";\n");
            break;
        case AST_TYPE_INT_VECT:
            fprintf(flux,"[");
            break;
        case AST_VECT_ITEM:
            fprintf(flux,"[");
            break;
        case AST_ADD:
            fprintf(flux,"+");
            break;
        case AST_SUB:
            fprintf(flux,"-");
            break;
        case AST_MUL:
            fprintf(flux,"*");
            break;
        case AST_DIV:
            fprintf(flux,"/");
            break;
        case AST_AFFECT:
            fprintf(flux,"=");
            break;
        case AST_INCREMENT:
            if (ast->right->number == 1)
                fprintf(flux,"++");
            else
                fprintf(flux,"+= %d", ast->right->number);
            break;
        case AST_AND:
            fprintf(flux,"&&");
            break;
        case AST_OR:
            fprintf(flux,"||");
            break;
        case AST_EQUAL:
            fprintf(flux,"==");
            break;
        case AST_DIFF:
            fprintf(flux,"!=");
            break;
        case AST_GEQ:
            fprintf(flux,">=");
            break;
        case AST_LEQ:
            fprintf(flux,"<=");
            break;
        case AST_SUP:
            fprintf(flux,">");
            break;
        case AST_INF:
            fprintf(flux,"<");
            break;
        case AST_FOR:
            fprintf(flux,") ");
            is_for = 0;
            break;
        case AST_WHILE:
            fprintf(flux,") ");
            break;
        case AST_IF:
            fprintf(flux,") ");
            break;
        case AST_ELSE_IF:
            fprintf(flux,") ");
            break;
        case AST_DEFINE:
            fprintf(flux," ");
            break;
        default:
            break;
    };

    // Using is_for as a flag to distinct the last AST_AFFECT that
    // don't have to output a semicolumn after it.
    if (is_for == 1 && ast->type == AST_LIST)
        is_for++;

    if (ast->type != AST_INCLUDE && ast->type != AST_ID && ast->type != AST_NUMBER
    && ast->type != AST_INCREMENT && ast->right != NULL)
        ast_to_source(ast->right, new_indent, is_for, flux);

    switch (ast->type) {
        case AST_DEFINE:
            fprintf(flux,"\n");
        break;
        case AST_TYPE_INT_VECT:
            fprintf(flux,"];\n");
            break;
        case AST_VECT_ITEM:
            fprintf(flux,"]");
            break;
        case AST_AFFECT:
            if (is_for < 2)
                fprintf(flux,";");
            if (!is_for)
                fprintf(flux,"\n");
            break;
        case AST_INCREMENT:
            if (is_for < 2)
                fprintf(flux,";");
            if (!is_for)
                fprintf(flux,"\n");
            break;
        case AST_BLOCK:
            new_indent--;
            fprint_indent(new_indent, flux);
            fprintf(flux,"}\n");
            break;
        case AST_RETURN:
            fprintf(flux,";\n");
            break;
        default:
            break;
    }
    if (is_arith_op(ast) || is_bool_op(ast))
        fprintf(flux,")");
}