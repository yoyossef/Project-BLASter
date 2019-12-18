%{
    #include <stdlib.h>
    #include <string.h>
    #include "y.tab.h"
%}

identifier      [a-zA-Z_][0-9a-zA-Z_]*
integer          ([1-9][0-9]*|[0-9])
comment         (\/\/.*)|(\/\*([^*]|\*+[^*/])*\*+\/)

%%

"if"            { return IF; }
"while"         { return WHILE; }
"else"          { return ELSE; }
"for"           { return FOR; }



{comment}       { }
{identifier}    { yylval.string = strdup(yytext); return ID; }
{integer}       { yylval.value = atoi(yytext); return NUMBER; }



"=="            { return EQUAL; }
"!="		    { return DIFF;}
">="            { return GEQ; }
"<="            { return LEQ; }
"&&"            { return AND; }
"||"            { return OR; }



[=+\-\*/()<>]       { return yytext[0]; }  
[{},;]              { return yytext[0]; }  
[\n\t ]             { }  
.                   { printf("Caractere inconnu: %s", yytext); }

%%

void lex_free() {
    yy_delete_buffer(YY_CURRENT_BUFFER);
    free(yy_buffer_stack);
}