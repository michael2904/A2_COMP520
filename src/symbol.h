#include "tree.h"

#define HashSize 317

typedef struct SYMBOL {
	char *ident;
	Types type;
	union {
		int intconstS;
		float floatconstS;
		char *stringconstS;
	} val;
	struct SYMBOL *next;
} SYMBOL; 

typedef struct SymbolTable {
	SYMBOL *table[HashSize];
	struct SymbolTable *next;
} SymbolTable;

SymbolTable *initSymbolTable();

SymbolTable *scopeSymbolTable(SymbolTable *t);

SYMBOL *putSymbol(SymbolTable *t, char *ident, Types type);

SYMBOL *getSymbol(SymbolTable *t, char *ident);

int defSymbol(SymbolTable *t, char *ident);

void makeProgSymbolTable(PROG *prog);