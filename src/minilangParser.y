%{
	#include <stdio.h>   /* for printf */
	#include "tree.h"
	extern char *yytext; /* string from scanner */
	extern int yylex();
	extern int yyparse();
	extern FILE *yyin;
	void yyerror(char* s) {
		fprintf (stderr,"INVALID: syntax error before -%s- --> error: %s\n", yytext,s); 
	}
	extern PROG *theprogram;

%}

%union {
	int intconst;
	float floatconst;
	char *stringconstid;
	char *stringconst;
}

%token <intconst> tINTCONST
%token <floatconst> tFLOATCONST
%token <stringconstid> tIDENTIFIER
%token <stringconst> tSTRINGCONST
%token tVAR
%token tWHILE
%token tDO
%token tDONE
%token tIF
%token tTHEN
%token tELSE
%token tENDIF
%token tFLOAT
%token tINT
%token tSTRING
%token tPRINT
%token tREAD
%token UMINUS
%token tERROR

%type <program> theProgram program


%start theProgram
%left '+' '-'
%left '*' '/'
%left UMINUS

%%

theProgram : program
				{ theprogram = $1;}
;

program : 	dcls  stmts
				{ $$ = makePROG ($1);}
;

dcls :		dcl dcls
				{ $$ = makePROGdcls ($1,$2);}
			|
;

dcl : tVAR tIDENTIFIER ':' type ';'
	{ $$ = makePROGdcl ($2,$4);}
;

type :		tINT
				{$$ = makePROFdlctype($1);}
			| tFLOAT
				{$$ = makePROFdlctype($1);}
			| tSTRING
				{$$ = makePROFdlctype($1);}
;

stmts : 	stmt stmts 
				{ $$ = makePROGstmts ($1,$2);}
			|
;

stmt :		read
				{$$ = makePROGstmtread($1);}
			|print
				{$$ = makePROGstmtprint($1);}
			|assign
				{$$ = makePROGstmtassign($1);}
			|ifst
				{$$ = makePROGstmtifst($1);}
			|whileloop
				{$$ = makePROGstmtwhileloop($1);}
;

read :		tREAD tIDENTIFIER ';'
				{$$ = makePROGstmtreadid($2);}
;

print :		tPRINT exp ';'
				{$$ = makePROGstmtprintexp($2);}
;

assign :	tIDENTIFIER '=' exp ';'
				{$$ = makePROGstmtassignexp($1,$3);}
;

ifst :		tIF exp tTHEN stmts midIf tENDIF
				{$$ = makePROGstmtifstexp($2,$4,$5);}
;

midIf :		tELSE stmts
				{$$ = makePROGstmtmidif($2);}
			|
;

whileloop :	tWHILE exp tDO stmts tDONE
				{$$ = makePROGstmtwhileloopexp($2,$4);}
;

exp :		tIDENTIFIER
				{$$ = makePROGid($1);}
			| tINTCONST
				{$$ = makePROGintconst($1);}
			| tFLOATCONST
				{$$ = makePROGfloatconst($1);}
			| tSTRINGCONST
				{$$ = makePROGstringconst($1);}
			| exp '*' exp 
				{$$ = makePROGitimes($1);}
			| exp '/' exp 
				{$$ = makePROGdiv($1);}
			| exp '+' exp 
				{$$ = makePROGplus($1);}
			| exp '-' exp
				{$$ = makePROGminus($1);}
			| '-' exp %prec UMINUS
				{$$ = makePROGuminus($1);}
			| '(' exp ')' 
				{$$ = $2;}
;

%%