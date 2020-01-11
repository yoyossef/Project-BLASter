%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "ast.h"
    #include "symbol.h"
    #include "optimizer.h"

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
%token <string> LIB
%token <value> NUMBER
%type <ast> include
%type <ast> includes
%type <ast> define
%type <ast> defines
%type <ast> main
%type <ast> function
%type <ast> functions
%type <ast> arguments
%type <ast> block
%type <ast> instructions_list
%type <ast> instruction
%type <ast> instruction_if
%type <ast> statement_elif
%type <ast> instruction_elif
%type <ast> instruction_else
%type <ast> affectation
%type <ast> declaration
%type <ast> arith_expr
%type <ast> condition

%token INCLUDE DEFINE MAIN RETURN
%token VOID INT
%token INCREMENT
%token GEQ LEQ
%token EQUAL DIFF
%token AND OR
%token FOR WHILE
%token IF ELSE 

%left '+' '-'
%left '*' '/'
%left OR
%left AND

%%

axiom:
    includes                { parser_ast = $1; return 0; }
    ;

includes:
    include includes        { $$ = ast_new_operation(AST_LIST, $1, $2); }
    | defines               { $$ = $1; }
    ;

include:
    INCLUDE '<' LIB '>'     { $$ = ast_new_include($3); }
    ;

defines:
    define defines          { $$ = ast_new_operation(AST_LIST, $1, $2); }
    | main                  { $$ = $1; }
    | functions             { $$ = $1; }
    ;

define:
    DEFINE ID NUMBER        { $$ = ast_new_operation(AST_DEFINE, ast_new_id($2), ast_new_number($3)); }
    ;

functions:
    function functions      { $$ = ast_new_operation(AST_LIST, $1, $2); }
    | function              { $$ = $1; }
    ;

function:
    VOID ID '('  ')' block              { 
        ast* tmp = ast_new_operation(AST_LIST, ast_new_id($2), NULL);
        $$ = ast_new_operation(AST_FUN, tmp, $5); 
    }
    | VOID ID '(' arguments ')' block   { 
        ast* tmp = ast_new_operation(AST_LIST, ast_new_id($2), $4);
        $$ = ast_new_operation(AST_FUN, tmp, $6); 
    }
    ;

arguments:
    ID ',' arguments        { $$ = ast_new_operation(AST_LIST, ast_new_id($1), $3); }
    | ID                    { $$ = ast_new_id($1); }
    ;

main:
    MAIN block              { $$ = ast_new_operation(AST_MAIN, $2, NULL); }
    ;

block:
    '{' '}'                         { $$ = ast_new_operation(AST_BLOCK, NULL, NULL); }
    | '{' instructions_list '}'     { $$ = ast_new_operation(AST_BLOCK, $2, NULL); }
    ;

instructions_list:
    instruction                         { $$ = ast_new_operation(AST_LIST, $1, NULL); }
    | instruction instructions_list     { $$ = ast_new_operation(AST_LIST, $1, $2); }
    ;

instruction:
    declaration ';'                     { $$ = $1; }
    | affectation ';'                   { $$ = $1; }
    | INT ID '=' arith_expr ';'                   
        { 
            ast* tmp1 = ast_new_operation(AST_TYPE_INT, ast_new_id($2), NULL);
            ast* tmp2 = ast_new_operation(AST_AFFECT, ast_new_id(strdup($2)), $4);
            $$ = ast_new_operation(AST_LIST, tmp1, tmp2); 
        }
    | FOR '(' affectation ';' condition ';' affectation ')' block 
        { 
            ast* tmp1 = ast_new_operation(AST_LIST, $5, $7);
            ast* tmp2 = ast_new_operation(AST_LIST, $3, tmp1);
            $$ = ast_new_operation(AST_FOR, tmp2, $9); 
        }
    | WHILE '(' condition ')' block     { $$ = ast_new_operation(AST_WHILE, $3, $5); }
    | instruction_if                    { $$ = $1; }
    | instruction_if statement_elif     { $$ = ast_new_operation(AST_LIST, $1, $2); }
    | RETURN arith_expr ';'             { $$ = ast_new_operation(AST_RETURN, $2, NULL); }
    ;

instruction_if:
    IF '(' condition ')' block          { $$ = ast_new_operation(AST_IF, $3, $5); }
    ;

statement_elif:
    instruction_elif statement_elif     { $$ = ast_new_operation(AST_LIST, $1, $2); }
    | instruction_else                  { $$ = $1; }
    ;

instruction_elif:
    ELSE IF '(' condition ')' block     { $$ = ast_new_operation(AST_ELSE_IF, $4, $6); }
    ;

instruction_else:
    ELSE block          { $$ = ast_new_operation(AST_ELSE, NULL, $2); }
    ;

affectation:
    ID '=' arith_expr   { $$ = ast_new_operation(AST_AFFECT, ast_new_id($1), $3); }
    | ID INCREMENT      { $$ = ast_new_operation(AST_INCREMENT, ast_new_id($1), ast_new_number(1)); }
    | ID '[' NUMBER ']' '=' arith_expr   {
        ast* tmp = ast_new_operation(AST_VECT_ITEM, ast_new_id($1), ast_new_number($3));
        $$ = ast_new_operation(AST_AFFECT, tmp, $6); 
    }
    | ID '[' ID ']' '=' arith_expr   {
        ast* tmp = ast_new_operation(AST_VECT_ITEM, ast_new_id($1), ast_new_id($3));
        $$ = ast_new_operation(AST_AFFECT, tmp, $6); 
    }
    ;

declaration:
    INT ID                      { $$ = ast_new_operation(AST_TYPE_INT, ast_new_id($2), NULL); }
    | INT ID '[' NUMBER ']'     { $$ = ast_new_operation(AST_TYPE_INT_VECT, ast_new_id($2), ast_new_number($4)); }
    ;

arith_expr:
    arith_expr '+' arith_expr       { $$ = ast_new_operation(AST_ADD, $1, $3); }
    | arith_expr '-' arith_expr     { $$ = ast_new_operation(AST_SUB, $1, $3); }
    | arith_expr '*' arith_expr     { $$ = ast_new_operation(AST_MUL, $1, $3); }
    | arith_expr '/' arith_expr     { $$ = ast_new_operation(AST_DIV, $1, $3); }
    | '(' arith_expr ')'            { $$ = $2; }
    | ID                            { $$ = ast_new_id($1); }
    | NUMBER                        { $$ = ast_new_number($1); }
    | ID '[' NUMBER ']'             { $$ = ast_new_operation(AST_VECT_ITEM, ast_new_id($1), ast_new_number($3)); }
    | ID '[' ID ']'                 { $$ = ast_new_operation(AST_VECT_ITEM, ast_new_id($1), ast_new_id($3)); }
    ;

condition:
    condition OR condition          { $$ = ast_new_operation(AST_OR, $1, $3); }
    | condition AND condition       { $$ = ast_new_operation(AST_AND, $1, $3); }
    | '(' condition ')'             { $$ = $2; }
    | arith_expr EQUAL arith_expr   { $$ = ast_new_operation(AST_EQUAL, $1, $3); }
    | arith_expr DIFF arith_expr    { $$ = ast_new_operation(AST_DIFF, $1, $3); }
    | arith_expr GEQ arith_expr     { $$ = ast_new_operation(AST_GEQ, $1, $3); }
    | arith_expr LEQ arith_expr     { $$ = ast_new_operation(AST_LEQ, $1, $3); }
    | arith_expr '>' arith_expr     { $$ = ast_new_operation(AST_SUP, $1, $3); }
    | arith_expr '<' arith_expr     { $$ = ast_new_operation(AST_INF, $1, $3); }
    ;

%%

void yyerror(char* msg) {
    printf("syntax error: %s\n", msg);
    exit(1);
}

int main(int argc, char* argv[]) {
    struct symbol* symbol_table = NULL;
    struct ast* source_code = NULL;
    struct ast* library = NULL;

    if (argc < 2)
        exit(1);

    yyin = fopen(argv[1], "r");
    
    // Code Source
    if (yyparse() == 0) {
        source_code = parser_ast;
        symbol_build_table(source_code, &symbol_table);
    }
    fclose(yyin);

    // Biblitheque Connue
    yyin = fopen(argv[2], "r");
    
    if (yyparse() == 0) {
        library = parser_ast;
    }

    // Optimisation
    optimize(source_code, library, symbol_table);
    
    // Affichage du resultat
    ast_print(source_code, 0);

    // Be clean.
    lex_free();
    ast_free(source_code);
    ast_free(library);
    symbol_free(symbol_table);
    fclose(yyin);
    
    return 0;
}
