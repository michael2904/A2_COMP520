#include "generate.h"


void generateProg(PROG *prog){
	printf("#include <stdio.h>\n#include <stdlib.h>\nvoid main(){\n");
	if(prog->decls != NULL){
		generateDcls(prog->decls);
	}
	if(prog->stmts != NULL){
		generateStmts(prog->stmts);
	}
	printf("}\n");

}

void generateDcls(DECL *decl){
	while(decl != NULL){
		switch(decl->kind){
			case intK:
				printf("int %s;\n",decl->identD->ident);
				break;
			case floatK:
				printf("float %s;\n",decl->identD->ident);
				break;
			case stringK:
				printf("char %s[4096];\n",decl->identD->ident);
				break;
		}
		decl = decl->next;
	}
}

void generateStmts(STMT *stmts){
	while(stmts != NULL){
		switch(stmts->kind){
			case readStmt:
				switch(stmts->val.readU.readId->type){
					case intK:
						printf("scanf(\"%%d\", &%s);\n",stmts->val.readU.readId->ident);
						break;
					case floatK:
						printf("scanf(\"%%f\", &%s);\n",stmts->val.readU.readId->ident);
						break;
					case stringK:
						printf("scanf(\"%%s\", %s);\n",stmts->val.readU.readId->ident);
						break;
				}
				break;
			case printStmt:
				switch(stmts->val.printU.printExp->type){
					case intK:
						printf("printf(\"%%d\", ");
						generateExpression(stmts->val.printU.printExp);
						printf(");\n");
						break;
					case floatK:
						printf("printf(\"%%f\", ");
						generateExpression(stmts->val.printU.printExp);
						printf(");\n");
						break;
					case stringK:
						printf("printf(\"%%s\", ");
						generateExpression(stmts->val.printU.printExp);
						printf(");\n");
						break;
				}
				break;
			case assignStmt:
				printf("%s = ",stmts->val.assignU.identId->ident);
				if(stmts->val.assignU.assignExp->type == stringK){
					printf("\"");
				}
				generateExpression(stmts->val.assignU.assignExp);
				if(stmts->val.assignU.assignExp->type == stringK){
					printf("\"");
				}
				printf(";\n");
				break;
			case ifStmt:
				printf("if (");
				generateExpression(stmts->val.ifU.condExp);
				printf(") {\n");
				generateStmts(stmts->val.ifU.ifStmt);
				printf("}\n");
				break;
			case ifseStmt:
				printf("if (");
				generateExpression(stmts->val.ifU.condExp);
				printf(") {\n");
				generateStmts(stmts->val.ifU.ifStmt);
				printf("} else {\n");
				generateStmts(stmts->val.ifseU.ifseStmt);
				printf("}\n");
				break;
			case whileStmt:
				printf("while (");
				generateExpression(stmts->val.whileU.condExp);
				printf(") {\n");
				generateStmts(stmts->val.whileU.bodyStmt);
				printf("}\n");
				break;
		}
		stmts = stmts->next;
	}

}

void generateExpression(EXP *exp){
	SYMBOL *symb;
	if(exp != NULL){
		// printf("exp");
		switch(exp->kind){
			case idK:
				printf("%s",exp->val.ident->ident);
				break;
			case intconstK:
				printf("%d",exp->val.intconstE);
				break;
			case floatconstK:
				printf("%f",exp->val.floatconstE);
				break;
			case stringconstK:
				printf("%s",exp->val.stringconstE);
				break;
			case timesK:
				if(exp->val.timesE.left->type == intK && exp->val.timesE.right->type == stringK ){
					int i;
					for(i = 0; i<exp->val.timesE.left->val.intconstE;i++){
						printf("%s",exp->val.timesE.right->val.stringconstE);
					}
				}else if(exp->val.timesE.left->type == stringK && exp->val.timesE.right->type == intK){
					int i;
					for(i = 0; i<exp->val.timesE.right->val.intconstE;i++){
						printf("%s",exp->val.timesE.left->val.stringconstE);
					}
				}else{
					generateExpression(exp->val.timesE.left);
					printf(" * ");
					generateExpression(exp->val.timesE.right);
				}
				break;
			case divK:
				generateExpression(exp->val.divE.left);
				printf(" / ");
				generateExpression(exp->val.divE.right);
				break;
			case plusK:
				if(exp->val.plusE.left->type == stringK && exp->val.plusE.right->type == stringK ){
					printf("%s%s",exp->val.plusE.left->val.stringconstE,exp->val.plusE.right->val.stringconstE);
				}else{
					generateExpression(exp->val.plusE.left);
					printf(" + ");
					generateExpression(exp->val.plusE.right);
				}
				break;
			case minusK:
				generateExpression(exp->val.minusE.left);
				printf(" - ");
				generateExpression(exp->val.minusE.right);
				break;
			case unaryK:
				printf(" - ");
				generateExpression(exp->val.unary);
				break;
		}
	}
}
