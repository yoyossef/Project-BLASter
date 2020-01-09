#include "symbol.h"


struct symbol* symbol_alloc(){
    struct symbol* new_symbol;
    new_symbol = malloc(sizeof(struct symbol));
    new_symbol->identifier = NULL;
    new_symbol->is_constant = false;
    new_symbol->value = 0; 
    new_symbol->next = NULL;
    return new_symbol;
}

struct symbol* symbol_add(struct symbol** table, char* name)
{
    if(*table == NULL){
        *table = symbol_alloc();
        (*table)->identifier = name;
        return *table;
    } else{
        struct symbol* scan = *table;
        while(scan->next != NULL)
            scan = scan->next;
        scan->next = symbol_alloc();
        scan->next->identifier = name;
        return scan->next;
    }
}

struct symbol* symbol_newtemp(struct symbol** table){
    static int temporary_number = 0; // plus propre qu'une variable globale
    char temporary_name[SYMBOL_MAX_STRING];
    snprintf(temporary_name, SYMBOL_MAX_STRING, "_temp_%d", temporary_number);
    temporary_number++;
    return symbol_add(table, temporary_name);
}


struct symbol*  symbol_newtemp_init(struct symbol** table,int num){
    struct symbol* temp = symbol_newtemp(table);
    temp->is_constant = true;
    temp->value = num;
    return temp;
}

struct symbol* symbol_lookup(struct symbol* table, char* identifier)
{
    while(table != NULL)
    {
        if(strcmp(table->identifier, identifier) == 0)
            return table;
        table = table->next;
    }
    return NULL;
}

void symbol_free(struct symbol* list){
    struct symbol* parcours = list;
    struct symbol* before;
    while(parcours != NULL){
        before = parcours;
        parcours = parcours->next;
        free(before->identifier);
        free(before);
    }
}

void symbol_build_table(struct ast* ast, struct symbol** symbol_table) {
    struct symbol* tmp = NULL;
    if (ast == NULL) 
        return;

    switch (ast->type) {
        case AST_NUMBER:
            break;
        case AST_INCLUDE:
            break;
        case AST_ID:
            tmp = symbol_lookup(*symbol_table, ast->id);
            if (tmp == NULL) {
                symbol_add(symbol_table, ast->id);
            }
            break;
        default:
            symbol_build_table(ast->left, symbol_table);
            symbol_build_table(ast->right, symbol_table);
            break;
    }
}

void symbol_print(struct symbol* symbol)
{
    while(symbol != NULL){
        printf("identifier: %7s, is constant:", symbol->identifier);
        if(symbol->is_constant) 
            printf("true,  value: %d", symbol->value);
        else
            printf("false, value: N/A");

        printf("\n");
        symbol = symbol->next;
    }
}
