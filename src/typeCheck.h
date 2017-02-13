#include <stdlib.h>
#include <stdio.h>
#include "symbol.h"
#include "tree.h"
#include "memory.h"

extern SymbolTable *symbolTable;

void typeCheckProg(PROG *prog);
void tcStmts(STMT *stmts);
void tcExpression(EXP *exp);
void tcAssignment(STMT *stmts);