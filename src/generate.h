#include <stdlib.h>
#include <stdio.h>
#include "symbol.h"
#include "tree.h"

extern SymbolTable *symbolTable;



void generateProg(PROG *prog);
void generateStmts(STMT *stmts);
void generateExpression(EXP *exp);
void generateDcls(DECL *decl);