#include "typeCheck.h"


void typeCheckProg(PROG *prog){
	//printf("*************-DONE typeCheckProg-*************\n");
	if(prog->stmts != NULL){
		tcStmts(prog->stmts);
	}

}

void tcStmts(STMT *stmts){
	SYMBOL *symb;
	while(stmts != NULL){
		switch(stmts->kind){
			case readStmt:
				symb = getSymbol(symbolTable,stmts->val.readU.readId->ident);
				if(symb == NULL){
					printf("This symbol \"%s\" has no been defined.\n",stmts->val.readU.readId->ident);
					exit(1);
				}
				stmts->val.readU.readId->type = symb->type;
				break;
			case printStmt:
				tcExpression(stmts->val.printU.printExp);
				break;
			case assignStmt:
				tcAssignment(stmts);
				break;
			case ifStmt:
				tcExpression(stmts->val.ifU.condExp);
				if(stmts->val.ifU.condExp->type != intK){
					printf("Type Check exception at line %d. \n", stmts->val.ifU.condExp->lineno);
					exit(1);
				}
				tcStmts(stmts->val.ifU.ifStmt);
				break;
			case ifseStmt:
				tcExpression(stmts->val.ifseU.condExp);
				if(stmts->val.ifU.condExp->type != intK){
					printf("Type Check exception at line %d. \n", stmts->val.ifU.condExp->lineno);
					exit(1);
				}
				tcStmts(stmts->val.ifseU.ifStmt);
				tcStmts(stmts->val.ifseU.ifseStmt);
				break;
			case whileStmt:
				//printf("*************-whileStmt-*************\n");
				tcExpression(stmts->val.whileU.condExp);
				//printf("*************-done tcExpression-*************\n");
				if(stmts->val.whileU.condExp->type != intK){
					printf("Type Check exception at line %d. \n", stmts->val.ifU.condExp->lineno);
					exit(1);
				}
				//printf("*************-int-*************\n");
				tcStmts(stmts->val.whileU.bodyStmt);
				//printf("*************-tcStmts-*************\n");
				break;
		}
		stmts = stmts->next;
	}

}

void tcAssignment(STMT *stmts){
	if(stmts!= NULL){
		if(!(defSymbol(symbolTable,stmts->val.assignU.identId->ident))){
			printf("This symbol \"%s\" has no been defined.\n",stmts->val.assignU.identId->ident);
			exit(1);
		}
		tcExpression(stmts->val.assignU.assignExp);
		Types type = getSymbol(symbolTable,stmts->val.assignU.identId->ident)->type;
		switch(type){
			case intK:
				if(!(stmts->val.assignU.assignExp->type == intK)){
					printf("This symbol has a wrong type. not int\n");
					exit(1);
				}
				stmts->val.assignU.assignExp->type = intK;
				break;
			case floatK:
				if(!(stmts->val.assignU.assignExp->type == intK || stmts->val.assignU.assignExp->type == floatK)){
					printf("This symbol has a wrong type.\n");
					exit(1);
				}
				stmts->val.assignU.assignExp->type = floatK;
				break;
			case stringK:
				if(!(stmts->val.assignU.assignExp->type == stringK)){
					printf("This symbol has a wrong type.\n");
					exit(1);
				}
				stmts->val.assignU.assignExp->type = stringK;
				break;
		}
	}
}

void tcExpression(EXP *exp){
	SYMBOL *symb;
	if(exp != NULL){
		switch(exp->kind){
			case idK:
				symb = getSymbol(symbolTable,exp->val.ident->ident);
				if(symb == NULL){
					printf("This symbol \"%s\" has no been defined.\n",exp->val.ident->ident);
					exit(1);
				}
				switch(symb->type){
					case intK:
						exp->type = intK;
						break;
					case floatK:
						exp->type = floatK;
						break;
					case stringK:
						exp->type = stringK;
						break;
				}
				break;
			case intconstK:
				exp->type = intK;
				break;
			case floatconstK:
				exp->type = floatK;
				break;
			case stringconstK:
				exp->type = stringK;
				break;
			case timesK:
				tcExpression(exp->val.timesE.left);
				tcExpression(exp->val.timesE.right);
				if(exp->val.timesE.left->type == intK){
					if(exp->val.timesE.right->type == stringK){
						exp->type = stringK;
					}else if(exp->val.timesE.right->type == floatK){
						exp->type = floatK;
					}else{
						exp->type = intK;
					}
				}else if(exp->val.timesE.left->type == floatK){
					if(exp->val.timesE.right->type == stringK){
						printf("This symbol has a wrong type.\n");
						exit(1);
					}
					exp->type = floatK;
				}else{
					if(!(exp->val.timesE.right->type == intK)){
						printf("This symbol has a test wrong type.\n");
						exit(1);
					}
					exp->type = stringK;
				}
				break;
			case divK:
				tcExpression(exp->val.divE.left);
				tcExpression(exp->val.divE.right);
				if(exp->val.timesE.left->type == intK){
					if(exp->val.timesE.right->type == intK){
						exp->type = intK;
					}else if(exp->val.timesE.right->type == floatK){
						exp->type = floatK;
					}else{
						printf("This symbol has a wrong type.\n");
						exit(1);
					}
				}else if(exp->val.timesE.left->type == floatK){
					if(exp->val.timesE.right->type == stringK){
						printf("This symbol has a wrong type.\n");
						exit(1);
					}
					exp->type = floatK;
				}else{
					printf("This symbol has a wrong type.\n");
					exit(1);
				}
				break;
			case plusK:
				tcExpression(exp->val.plusE.left);
				tcExpression(exp->val.plusE.right);
				if(exp->val.timesE.left->type == intK){
					if(exp->val.timesE.right->type == intK){
						exp->type = intK;
					}else if(exp->val.timesE.right->type == floatK){
						exp->type = floatK;
					}else{
						printf("This symbol has a wrong type.\n");
						exit(1);
					}
				}else if(exp->val.timesE.left->type == floatK){
					if(exp->val.timesE.right->type == stringK){
						printf("This symbol has a wrong type.\n");
						exit(1);
					}
					exp->type = floatK;
				}else{
					if(!(exp->val.timesE.right->type == stringK)){
						printf("This symbol has a wrong type.\n");
						exit(1);
					}
					exp->type = stringK;
				}
				break;
			case minusK:
				tcExpression(exp->val.minusE.left);
				tcExpression(exp->val.minusE.right);
				if(exp->val.timesE.left->type == intK){
					if(exp->val.timesE.right->type == intK){
						exp->type = intK;
					}else if(exp->val.timesE.right->type == floatK){
						exp->type = floatK;
					}else{
						printf("This symbol has a wrong type.\n");
						exit(1);
					}
				}else if(exp->val.timesE.left->type == floatK){
					if(exp->val.timesE.right->type == stringK){
						printf("This symbol has a wrong type.\n");
						exit(1);
					}
					exp->type = floatK;
				}else{
					printf("This symbol has a wrong type.\n");
					exit(1);
				}
				break;
			case unaryK:
				tcExpression(exp->val.unary);
				break;
		}
	}
}