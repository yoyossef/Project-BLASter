#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "ast.h"

void optimize_level_1(ast*);
void optimize_addition(ast*);
void optimize_scalar_product(ast*);

#endif