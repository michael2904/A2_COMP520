#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "memory.h"
#include "tree.h"
 
extern int lineno;


PROG *makePROG(DECL *decls, STMT *stmts, int lineno){
	PROG *prog;
	prog = NEW(PROG);
	prog->lineno = lineno;
	prog->decls = decls;
	prog->stmts = stmts;
	return prog;
}

DECL *makePROGdcls(DECL *decl, DECL *next, int lineno){
	decl->next = next;
	return decl;
}

DECL *makePROGdcl(IDENT *ident, Types type, int lineno){
	DECL *decl;
	decl = NEW(DECL);
	decl->lineno = lineno;
	decl->kind = type;
	decl->identD = ident;
	decl->next = NULL;
	return decl;
}

STMT *makePROGstmts(STMT *stmt, STMT *next, int lineno){
	stmt->next = next;
	return stmt;
}

STMT *makePROGstmtread(IDENT *ident, int lineno){
	STMT *stmt;
	stmt = NEW(STMT);
	stmt->lineno = lineno;
	stmt->kind = readStmt;
	stmt->val.readU.readId = ident;
	return stmt;
}

STMT *makePROGstmtprint(EXP *exp, int lineno){
	STMT *stmt;
	stmt = NEW(STMT);
	stmt->lineno = lineno;
	stmt->kind = printStmt;
	stmt->val.printU.printExp = exp;
	return stmt;
}

STMT *makePROGstmtassign(IDENT *ident, EXP *exp, int lineno){
	STMT *stmt;
	stmt = NEW(STMT);
	stmt->lineno = lineno;
	stmt->kind = assignStmt;
	stmt->val.assignU.identId = ident;
	stmt->val.assignU.assignExp = exp;
	return stmt;
}

STMT *makePROGstmtif(EXP *cond, STMT *stmt_if, STMT *stmt_else, int lineno){
	STMT *stmt;
	stmt = NEW(STMT);
	stmt->lineno = lineno;
	if(stmt_else == NULL){
		stmt->kind = ifStmt;
		stmt->val.ifU.condExp = cond;
		stmt->val.ifU.ifStmt = stmt_if;
	}else{
		stmt->kind = ifseStmt;
		stmt->val.ifseU.condExp = cond;
		stmt->val.ifseU.ifStmt = stmt_if;
		stmt->val.ifseU.ifseStmt = stmt_else;
	}
	return stmt;
}

STMT *makePROGstmtwhileloop(EXP *cond, STMT *body, int lineno){
	STMT *stmt;
	stmt = NEW(STMT);
	stmt->lineno = lineno;
	stmt->kind = whileStmt;
	stmt->val.whileU.condExp = cond;
	stmt->val.whileU.bodyStmt = body;
	return stmt;
}

// expressions

IDENT *makePROGid(char *id, int lineno) {
	IDENT *i;
	i = NEW(IDENT);
	i->lineno = lineno;
	i->ident = id;
	return i;
}

EXP *makePROGidentifier(IDENT *ident, int lineno) {
	EXP *e;
	e = NEW(EXP);
	e->lineno = lineno;
	e->kind = idK;
	e->val.ident = ident;
	return e;
}

EXP *makePROGintconst(int intconst, int lineno) {
	EXP *e;
	e = NEW(EXP);
	e->lineno = lineno;
	e->kind = intconstK;
	e->val.intconstE = intconst;
	return e;
}

EXP *makePROGfloatconst(float floatconst, int lineno) {
	EXP *e;
	e = NEW(EXP);
	e->lineno = lineno;
	e->kind = floatconstK;
	e->val.floatconstE = floatconst;
	return e;
}

EXP *makePROGstringconst(char *stringconst, int lineno) {
	EXP *e;
	e = NEW(EXP);
	e->lineno = lineno;
	e->kind = stringconstK;
	char *substr = (char*) malloc(strlen(stringconst));
	strncpy(substr,stringconst+1,strlen(stringconst)-2);
	e->val.stringconstE = substr;
	return e;
}

EXP *makePROGtimes(EXP *left, EXP *right, int lineno) {
	EXP *e;
	e = NEW(EXP);
	e->lineno = lineno;
	e->kind = timesK;
	e->val.timesE.left = left;
	e->val.timesE.right = right;
	return e;
}

EXP *makePROGdiv(EXP *left, EXP *right, int lineno) {
	EXP *e;
	e = NEW(EXP);
	e->lineno = lineno;
	e->kind = divK;
	e->val.divE.left = left;
	e->val.divE.right = right;
	return e; 
}

EXP *makePROGplus(EXP *left, EXP *right, int lineno) {
	EXP *e;
	e = NEW(EXP);
	e->lineno = lineno;
	e->kind = plusK;
	e->val.plusE.left = left;
	e->val.plusE.right = right;
	return e;
}

EXP *makePROGminus(EXP *left, EXP *right, int lineno) {
	EXP *e;
	e = NEW(EXP);
	e->lineno = lineno;
	e->kind = minusK;
	e->val.minusE.left = left;
	e->val.minusE.right = right;
	return e;
}

EXP *makePROGunary(EXP *unary, int lineno) {
	EXP *e;
	e = NEW(EXP);
	e->lineno = lineno;
	e->kind = unaryK;
	e->val.unary = unary;
	return e;
}

