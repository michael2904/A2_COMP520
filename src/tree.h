#ifndef TREE_H
#define TREE_H

#include <stddef.h>
#include "memory.h"

typedef enum {intK, floatK, stringK} Types;
typedef enum {readStmt,printStmt,assignStmt,ifStmt,ifseStmt,whileStmt} StatementKinds;
typedef enum {idK,intconstK,floatconstK,stringconstK,timesK,divK,plusK,minusK,unaryK} ExpKinds;

typedef struct PROG {
	int lineno;
	struct DECL *decls;
	struct STMT *stmts;
} PROG;

typedef struct DECL {
	int lineno;
	struct TYPES *kind;
	struct IDENT *identD;
	struct DECL *next;
} DECL;

typedef struct STMT {
	int lineno;
	StatementKinds kind;
	union {
		struct {
			struct IDENT *readId;
		} readU;
		struct {
			struct EXP *printExp;
		} printU;
		struct {
			struct IDENT *identId;
			struct EXP *assignExp;
		} assignU;
		struct {
			struct EXP *condExp;
			struct STMT *ifStmt;
		} ifU;
		struct {
			struct EXP *condExp;
			struct STMT *ifStmt;
			struct STMT *ifseStmt;
		} ifseU;
		struct {
			struct EXP *condExp;
			struct STMT *bodyStmt;
		} whileU;
	} val;
	struct STMT* next;
} STMT;

typedef struct TYPES {
	Types type;
} TYPES;

typedef struct IDENT {
	int lineno;
	TYPES type;
	char *ident;
} IDENT;


typedef struct EXP {
	int lineno;
	ExpKinds kind;
	union {
		int intconstE;
		float floatconstE;
		char *stringconstE;
		struct IDENT *ident;
		struct EXP *unary;
		struct {
			struct EXP *left;
			struct EXP *right;
		} timesE;
		struct {
			struct EXP *left;
			struct EXP *right;
		} divE;
		struct {
			struct EXP *left;
			struct EXP *right;
		} plusE;
		struct {
			struct EXP *left; 
			struct EXP *right;
		} minusE;
	} val;
} EXP;

PROG *makePROG(DECL *decls, STMT *stmts, int lineno);

DECL *makePROGdcls(DECL *decl, DECL *next, int lineno);

DECL *makePROGdcl(IDENT *ident, TYPES *type, int lineno);
 
TYPES *makePROGdclInt();

TYPES *makePROGdclFloat();

TYPES *makePROGdclString();

STMT *makePROGstmts(STMT *stmt, STMT *next, int lineno);

STMT *makePROGstmtread(IDENT *ident, int lineno);

STMT *makePROGstmtprint(EXP *exp, int lineno);

STMT *makePROGstmtassign(IDENT *ident, EXP *exp, int lineno);

STMT *makePROGstmtif(EXP *cond, STMT *stmt_if, STMT *stmt_else, int lineno);

STMT *makePROGstmtifse(STMT *stmt_else, int lineno);

STMT *makePROGstmtwhileloop(EXP *cond, STMT *body, int lineno);

IDENT *makePROGid(char *id, int lineno);

EXP *makePROGidentifier(IDENT *ident, int lineno);

EXP *makePROGintconst(int intconst, int lineno);

EXP *makePROGfloatconst(float floatconst, int lineno);

EXP *makePROGstringconst(char *stringconst, int lineno);

EXP *makePROGtimes(EXP *left, EXP *right, int lineno);

EXP *makePROGdiv(EXP *left, EXP *right, int lineno);

EXP *makePROGplus(EXP *left, EXP *right, int lineno);

EXP *makePROGminus(EXP *left, EXP *right, int lineno);

EXP *makePROGunary(EXP *unary, int lineno);

#endif /* !TREE_H */
