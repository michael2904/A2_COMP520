#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"
#include "symbol.h"

extern char *symbolFilePath;
extern SymbolTable *symbolTable;
FILE *symbolFile;

int Hash(char *str){
	unsigned int hash = 0;
	while (*str) hash = (hash << 1) + *str++; 
	return hash % HashSize;
}

SymbolTable *initSymbolTable(){
	// printf("initSymbolTable\n");
	SymbolTable *t;
	int i;
	t = NEW(SymbolTable);
	for (i=0; i < HashSize; i++)
		t->table[i] = NULL;
	t->next = NULL;
	// printf("Done\n");
	return t;
}

SYMBOL *putSymbol(SymbolTable *t, char *ident, Types type){
	// printf("putSymbol\n");
	int i = Hash(ident);
	SYMBOL *s;
	for (s = t->table[i]; s; s = s->next) {
			if (strcmp(s->ident,ident)==0) return s;
	}
	s = NEW(SYMBOL);
	s->ident = ident;
	s->type = type;
	s->next = t->table[i];
	t->table[i] = s;
	return s;
}
 
SYMBOL *getSymbol(SymbolTable *t, char *ident){
	int i = Hash(ident);
	SYMBOL *s;
	for (s = t->table[i]; s; s = s->next) {
			if (strcmp(s->ident,ident)==0) return s;
	}
	if (t->next==NULL) return NULL;
	return getSymbol(t->next,ident);
}
 
int defSymbol(SymbolTable *t, char *ident){
	// printf("defSymbol %s \n",ident);
	int i = Hash(ident);
	SYMBOL *s;
	for (s = t->table[i]; s; s = s->next) {
		if (strcmp(s->ident,ident)==0) return 1;
	}
	return 0;
}

void makeProgSymbolTable(PROG *prog){
	printf("symbolFilePath-%s-\n",symbolFilePath);
	symbolFile = fopen(symbolFilePath, "w");
	DECL *decl;
	decl = prog->decls;
	symbolTable = initSymbolTable();
	while(decl != NULL){
		char *ident;
		ident = decl->identD->ident;
		int ret = defSymbol(symbolTable,ident);
		if(ret){
			printf("---- This identifier ( \"%s\") was already declared at %d ----\n",decl->identD->ident,decl->identD->lineno);
			exit(1);
		}else{
			putSymbol(symbolTable,decl->identD->ident,decl->kind);
			switch(decl->kind){
				case intK:
					fprintf(symbolFile,"%s  |  int;\n",decl->identD->ident);
					break;
				case floatK:
					fprintf(symbolFile,"%s  |  float;\n",decl->identD->ident);
					break;
				case stringK:
					fprintf(symbolFile,"%s  |  string;\n",decl->identD->ident);
					break;
			}
			decl = decl->next;
		}
	}
}