typedef enum ast_type { AST_ID, AST_NUMBER, AST_AFFECT, AST_ADD, AST_SUB, AST_MUL, AST_DIV } ast_type;

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
