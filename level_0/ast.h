typedef enum ast_type { 
    AST_ID, 
    AST_NUMBER, 
    AST_TYPE_INT, 
    AST_ADD, AST_SUB, AST_MUL, AST_DIV, 
    AST_AFFECT, 
    AST_AND, AST_OR, AST_EQUAL, AST_DIFF, AST_GEQ, AST_LEQ, AST_SUP, AST_INF, 
    AST_FOR, AST_WHILE, 
    AST_IF, AST_ELSE_IF, AST_ELSE,  
    AST_LIST, AST_BLOCK 
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
void ast_free(ast*);
void ast_print(ast*, int);
void print_indent(int);
void ast_to_source(ast*, int, char);