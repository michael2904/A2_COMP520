#include "generate.h"

extern char* generatedFilePath;
FILE *generatedFile;
int ind;


void generateProg(PROG *prog){
	generatedFile = fopen(generatedFilePath, "w");
	fprintf(generatedFile,"#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\nint main(){\n");
	ind = 1;
	if(prog->decls != NULL){
		generateDcls(prog->decls);
	}
	if(prog->stmts != NULL){
		generateStmts(prog->stmts);
	}
	ind = ind -1;
	fprintf(generatedFile,"}\n");

}

void generateDcls(DECL *decl){
	while(decl != NULL){
		int i;
		for(i = 0;i<ind;i++){
			fprintf(generatedFile,"	");
		}
		switch(decl->kind){
			case intK:
				fprintf(generatedFile,"int %s;\n",decl->identD->ident);
				break;
			case floatK:
				fprintf(generatedFile,"float %s;\n",decl->identD->ident);
				break;
			case stringK:
				fprintf(generatedFile,"char %s[4096];\n",decl->identD->ident);
				break;
		}
		decl = decl->next;
	}
}

void generateStmts(STMT *stmts){
	while(stmts != NULL){
		int i;
		for(i = 0;i<ind;i++){
			fprintf(generatedFile,"	");
		}
		switch(stmts->kind){
			case readStmt:
				switch(stmts->val.readU.readId->type){
					case intK:
						fprintf(generatedFile,"scanf(\"%%d\", &%s);\n",stmts->val.readU.readId->ident);
						break;
					case floatK:
						fprintf(generatedFile,"scanf(\"%%f\", &%s);\n",stmts->val.readU.readId->ident);
						break;
					case stringK:
						fprintf(generatedFile,"scanf(\"%%s\", %s);\n",stmts->val.readU.readId->ident);
						break;
				}
				break;
			case printStmt:
				switch(stmts->val.printU.printExp->type){
					case intK:
						fprintf(generatedFile,"printf(\"%%d\", ");
						generateExpression(stmts->val.printU.printExp);
						fprintf(generatedFile,");\n");
						break;
					case floatK:
						fprintf(generatedFile,"printf(\"%%f\", ");
						generateExpression(stmts->val.printU.printExp);
						fprintf(generatedFile,");\n");
						break;
					case stringK:
						fprintf(generatedFile,"printf(\"%%s\", ");
						generateExpression(stmts->val.printU.printExp);
						fprintf(generatedFile,");\n");
						break;
				}
				break;
			case assignStmt:
				if(stmts->val.assignU.assignExp->type == stringK){
					fprintf(generatedFile,"strcpy(%s, \"",stmts->val.assignU.identId->ident);
					generateExpression(stmts->val.assignU.assignExp);
					fprintf(generatedFile,"\");\n");
				}else{
					fprintf(generatedFile,"%s = ",stmts->val.assignU.identId->ident);
					generateExpression(stmts->val.assignU.assignExp);
					fprintf(generatedFile,";\n");
				}
				break;
			case ifStmt:
				fprintf(generatedFile,"if (");
				generateExpression(stmts->val.ifU.condExp);
				fprintf(generatedFile,") {\n");
				ind = ind + 1;
				generateStmts(stmts->val.ifU.ifStmt);
				for(i = 0;i<ind;i++){
					fprintf(generatedFile,"	");
				}
				fprintf(generatedFile,"}\n");
				ind = ind - 1;
				break;
			case ifseStmt:
				fprintf(generatedFile,"if (");
				generateExpression(stmts->val.ifU.condExp);
				fprintf(generatedFile,") {\n");
				ind = ind + 1;
				generateStmts(stmts->val.ifU.ifStmt);
				ind = ind - 1;
				fprintf(generatedFile,"} else {\n");
				ind = ind + 1;
				generateStmts(stmts->val.ifseU.ifseStmt);
				ind = ind - 1;
				for(i = 0;i<ind;i++){
					fprintf(generatedFile,"	");
				}
				fprintf(generatedFile,"}\n");
				break;
			case whileStmt:
				fprintf(generatedFile,"while (");
				generateExpression(stmts->val.whileU.condExp);
				fprintf(generatedFile,") {\n");
				ind = ind + 1;
				generateStmts(stmts->val.whileU.bodyStmt);
				ind = ind - 1;
				for(i = 0;i<ind;i++){
					fprintf(generatedFile,"	");
				}
				fprintf(generatedFile,"}\n");
				break;
		}
		stmts = stmts->next;
	}

}

void generateExpression(EXP *exp){
	SYMBOL *symb;
	if(exp != NULL){
		// fprintf(generatedFile,"exp");
		switch(exp->kind){
			case idK:
				fprintf(generatedFile,"%s",exp->val.ident->ident);
				break;
			case intconstK:
				fprintf(generatedFile,"%d",exp->val.intconstE);
				break;
			case floatconstK:
				fprintf(generatedFile,"%f",exp->val.floatconstE);
				break;
			case stringconstK:
				fprintf(generatedFile,"%s",exp->val.stringconstE);
				break;
			case timesK:
				if(exp->val.timesE.left->type == intK && exp->val.timesE.right->type == stringK ){
					int i;
					for(i = 0; i<exp->val.timesE.left->val.intconstE;i++){
						fprintf(generatedFile,"%s",exp->val.timesE.right->val.stringconstE);
					}
				}else if(exp->val.timesE.left->type == stringK && exp->val.timesE.right->type == intK){
					int i;
					for(i = 0; i<exp->val.timesE.right->val.intconstE;i++){
						fprintf(generatedFile,"%s",exp->val.timesE.left->val.stringconstE);
					}
				}else{
					generateExpression(exp->val.timesE.left);
					fprintf(generatedFile," * ");
					generateExpression(exp->val.timesE.right);
				}
				break;
			case divK:
				generateExpression(exp->val.divE.left);
				fprintf(generatedFile," / ");
				generateExpression(exp->val.divE.right);
				break;
			case plusK:
				if(exp->val.plusE.left->type == stringK && exp->val.plusE.right->type == stringK ){
					fprintf(generatedFile,"%s%s",exp->val.plusE.left->val.stringconstE,exp->val.plusE.right->val.stringconstE);
				}else{
					generateExpression(exp->val.plusE.left);
					fprintf(generatedFile," + ");
					generateExpression(exp->val.plusE.right);
				}
				break;
			case minusK:
				generateExpression(exp->val.minusE.left);
				fprintf(generatedFile," - ");
				generateExpression(exp->val.minusE.right);
				break;
			case unaryK:
				fprintf(generatedFile," - ");
				generateExpression(exp->val.unary);
				break;
		}
	}
}
