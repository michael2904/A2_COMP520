#include <stdio.h>
#include "pretty.h"
 
int ind;

void prettyPROG(PROG *prog){
	ind = 0;
	prettyDECL(prog->decls);
	prettySTMT(prog->stmts);
}

void prettyDECL(DECL *d){
	TYPES *type = d->kind;
	switch (type->type) {
		case intK:
			printf("var %s : int;\n",d->identD->ident);
			break;
		case floatK:
			printf("var %s : float;\n",d->identD->ident);
			break;
		case stringK:
			printf("var %s : string;\n",d->identD->ident);
			break;
	}
	if(d->next != NULL){
		prettyDECL(d->next);
	}
}

void prettySTMT(STMT *s){
	int i;
	for(i = 0;i<ind;i++){
		printf("	");
	}
	switch (s->kind) {
		case readStmt:
			printf("read %s;\n",s->val.readU.readId->ident);
			break;
		case printStmt:
			printf("print ");
			prettyEXP(s->val.printU.printExp);
			printf(";\n");
			break;
		case assignStmt:
			printf("%s = ",s->val.assignU.identId->ident);
			prettyEXP(s->val.assignU.assignExp);
			printf(";\n");
			break;
		case ifStmt:
			printf("if ");
			prettyEXP(s->val.ifU.condExp);
			printf(" then \n");
			ind = ind + 1;
			prettySTMT(s->val.ifU.ifStmt);
			for(i = 0;i<ind;i++){
				printf("	");
			}
			printf("endif\n");
			ind = ind - 1;
			break;
		case ifseStmt:
			printf("if ");
			prettyEXP(s->val.ifseU.condExp);
			printf(" then \n");
			ind = ind + 1;
			prettySTMT(s->val.ifseU.ifStmt);
			ind = ind - 1;
			printf("else\n");
			ind = ind + 1;
			prettySTMT(s->val.ifseU.ifseStmt);
			ind = ind - 1;
			for(i = 0;i<ind;i++){
				printf("	");
			}
			printf("endif\n");
			break;
		case whileStmt:
			printf("while ");
			prettyEXP(s->val.whileU.condExp);
			printf(" do\n");
			ind = ind + 1;
			prettySTMT(s->val.whileU.bodyStmt);
			ind = ind - 1;
			for(i = 0;i<ind;i++){
				printf("	");
			}
			printf("done\n");
			break;
	}
	if(s->next != NULL){
		prettySTMT(s->next);
	}
}

void prettyEXP(EXP *e){
	switch (e->kind) {
		case idK:
			printf("%s",e->val.ident->ident);
			break;
		case intconstK:
			printf("%i",e->val.intconstE);
			break;
		case floatconstK:
			printf("%f",e->val.floatconstE);
			break;
		case stringconstK:
			printf("%s",e->val.stringconstE);
			break;
		case timesK:
			printf("(");
			prettyEXP(e->val.timesE.left);
			printf("*");
			prettyEXP(e->val.timesE.right);
			printf(")");
			break;
		case divK:
			printf("(");
			prettyEXP(e->val.divE.left);
			printf("/");
			prettyEXP(e->val.divE.right);
			printf(")");
			break;
		case plusK:
			printf("(");
			prettyEXP(e->val.plusE.left);
			printf("+");
			prettyEXP(e->val.plusE.right);
			printf(")");
			break;
		case minusK:
			printf("(");
			prettyEXP(e->val.minusE.left);
			printf("-");
			prettyEXP(e->val.minusE.right);
			printf(")");
			break;
		case unaryK:
			printf("-");
			prettyEXP(e->val.minusE.right);
			break;
	}
}
