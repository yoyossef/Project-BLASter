#ifndef AST_H
#define AST_H

#define BUFFER_SIZE 255

typedef enum ast_type { 
    AST_INCLUDE, AST_DEFINE, AST_MAIN, AST_FUN,
    AST_ID, AST_NUMBER, AST_TYPE_INT, AST_TYPE_INT_VECT, AST_VECT_ITEM, AST_TYPE_INT_MAT, AST_MAT_ITEM,
    AST_ADD, AST_SUB, AST_MUL, AST_DIV, 
    AST_AFFECT, AST_INCREMENT,
    AST_AND, AST_OR, AST_EQUAL, AST_DIFF, AST_GEQ, AST_LEQ, AST_SUP, AST_INF, 
    AST_FOR, AST_WHILE, 
    AST_IF, AST_ELSE_IF, AST_ELSE, 
    AST_LIST, AST_BLOCK, AST_RETURN,
} ast_type;

typedef struct ast {
    ast_type type;
    union {
        int number;
        char* id;
        struct {
            struct ast* left;
            struct ast* right;
        };
    };
} ast;

ast* ast_new_operation(ast_type, ast*, ast*);
ast* ast_new_number(int);
ast* ast_new_id(char*);
ast* ast_new_include(char*);
ast* ast_copy(ast* T);
int are_similar(ast*, ast*);
void ast_free(ast*);
void ast_print(ast*, int);
void print_indent(int);
void fprint_indent(int, FILE*);
char is_arith_op(ast*);
char is_bool_op(ast*);

/**
 * @brief Prints the includes of a lib
 */
void print_include(ast*, FILE*);

/**
 * @brief Parses a function call AST and prints it w/ arguments
 */
void ast_parse_opt_fun(ast*, FILE*);

void ast_parse_mat(ast*, FILE*);

/**
 * @brief Parses an AST and prints the code w/ indents
 */
void ast_to_source(ast*, int, char, FILE*);

#endif