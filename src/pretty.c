#include <stdio.h>
#include "pretty.h"
 
int ind;
extern char* prettyFilePath;
FILE *prettyFile;

void prettyPROG(PROG *prog){
	prettyFile = fopen(prettyFilePath, "w");
	if(prog != NULL){
		ind = 0;
		prettyDECL(prog->decls);
		prettySTMT(prog->stmts);
	}
}

void prettyDECL(DECL *d){
	if(d != NULL){
		switch (d->kind) {
			case intK:
				fprintf(prettyFile,"var %s : int;\n",d->identD->ident);
				break;
			case floatK:
				fprintf(prettyFile,"var %s : float;\n",d->identD->ident);
				break;
			case stringK:
				fprintf(prettyFile,"var %s : string;\n",d->identD->ident);
				break;
		}
		if(d->next != NULL){
			prettyDECL(d->next);
		}
	}

}

void prettySTMT(STMT *s){
	if(s != NULL){
		int i;
		for(i = 0;i<ind;i++){
			fprintf(prettyFile,"	");
		}
		switch (s->kind) {
			case readStmt:
				fprintf(prettyFile,"read %s;\n",s->val.readU.readId->ident);
				break;
			case printStmt:
				fprintf(prettyFile,"print ");
				prettyEXP(s->val.printU.printExp);
				fprintf(prettyFile,";\n");
				break;
			case assignStmt:
				fprintf(prettyFile,"%s = ",s->val.assignU.identId->ident);
				prettyEXP(s->val.assignU.assignExp);
				fprintf(prettyFile,";\n");
				break;
			case ifStmt:
				fprintf(prettyFile,"if ");
				prettyEXP(s->val.ifU.condExp);
				fprintf(prettyFile," then \n");
				ind = ind + 1;
				prettySTMT(s->val.ifU.ifStmt);
				for(i = 0;i<ind;i++){
					fprintf(prettyFile,"	");
				}
				fprintf(prettyFile,"endif\n");
				ind = ind - 1;
				break;
			case ifseStmt:
				fprintf(prettyFile,"if ");
				prettyEXP(s->val.ifseU.condExp);
				fprintf(prettyFile," then \n");
				ind = ind + 1;
				prettySTMT(s->val.ifseU.ifStmt);
				ind = ind - 1;
				fprintf(prettyFile,"else\n");
				ind = ind + 1;
				prettySTMT(s->val.ifseU.ifseStmt);
				ind = ind - 1;
				for(i = 0;i<ind;i++){
					fprintf(prettyFile,"	");
				}
				fprintf(prettyFile,"endif\n");
				break;
			case whileStmt:
				fprintf(prettyFile,"while ");
				prettyEXP(s->val.whileU.condExp);
				fprintf(prettyFile," do\n");
				ind = ind + 1;
				prettySTMT(s->val.whileU.bodyStmt);
				ind = ind - 1;
				for(i = 0;i<ind;i++){
					fprintf(prettyFile,"	");
				}
				fprintf(prettyFile,"done\n");
				break;
		}
		if(s->next != NULL){
			prettySTMT(s->next);
		}
	}
}

void prettyEXP(EXP *e){
	if(e != NULL){
		switch (e->kind) {
			case idK:
				fprintf(prettyFile,"%s",e->val.ident->ident);
				break;
			case intconstK:
				fprintf(prettyFile,"%i",e->val.intconstE);
				break;
			case floatconstK:
				fprintf(prettyFile,"%f",e->val.floatconstE);
				break;
			case stringconstK:
				fprintf(prettyFile,"\"%s\"",e->val.stringconstE);
				break;
			case timesK:
				fprintf(prettyFile,"(");
				prettyEXP(e->val.timesE.left);
				fprintf(prettyFile,"*");
				prettyEXP(e->val.timesE.right);
				fprintf(prettyFile,")");
				break;
			case divK:
				fprintf(prettyFile,"(");
				prettyEXP(e->val.divE.left);
				fprintf(prettyFile,"/");
				prettyEXP(e->val.divE.right);
				fprintf(prettyFile,")");
				break;
			case plusK:
				fprintf(prettyFile,"(");
				prettyEXP(e->val.plusE.left);
				fprintf(prettyFile,"+");
				prettyEXP(e->val.plusE.right);
				fprintf(prettyFile,")");
				break;
			case minusK:
				fprintf(prettyFile,"(");
				prettyEXP(e->val.minusE.left);
				fprintf(prettyFile,"-");
				prettyEXP(e->val.minusE.right);
				fprintf(prettyFile,")");
				break;
			case unaryK:
				fprintf(prettyFile,"-");
				prettyEXP(e->val.minusE.right);
				break;
		}
	}
}
