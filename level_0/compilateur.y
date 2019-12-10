%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "ast.h"

    extern FILE* yyin;
    int yylex();
    void yyerror(char*);
    void lex_free();
    struct ast* parser_ast = NULL;
%}

%union {
    char* string;
    int value;
    struct ast* ast;
}

%token <string> ID
%token <value> NUMBER
%type <ast> affectation
%type <ast> arith_expr

%left '+' '-'
%left '*' '/'

%%

axiom:
    affectation '\n'            { parser_ast = $1; return 0; }
    ;

affectation:
    ID '=' arith_expr ';'       { $$ = ast_new_operation(AST_AFFECT, ast_new_id($1), $3); }
    ;

arith_expr:
    arith_expr '+' arith_expr   { $$ = ast_new_operation(AST_ADD, $1, $3); }
    | arith_expr '-' arith_expr { $$ = ast_new_operation(AST_SUB, $1, $3); }
    | arith_expr '*' arith_expr { $$ = ast_new_operation(AST_MUL, $1, $3); }
    | arith_expr '/' arith_expr { $$ = ast_new_operation(AST_DIV, $1, $3); }
    | '(' arith_expr ')'        { $$ = $2; }
    | ID                        { $$ = ast_new_id($1); }
    | NUMBER                    { $$ = ast_new_number($1); }
    ;

%%

void yyerror(char* msg) {
    printf("syntax error: %s\n", msg);
    exit(1);
}

int main(int argc, char* argv[]) {

    if (argc < 2)
        exit(1);

    yyin = fopen(argv[1], "r");
    printf("Entrez une expression :\n");
    
    if (yyparse() == 0)
        ast_print(parser_ast, 0);

    // Be clean.
    lex_free();
    ast_free(parser_ast);
    
    return 0;
}
