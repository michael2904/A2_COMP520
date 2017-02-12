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
	char *stringconst;
	struct PROG *prog;
	struct DECL *dcl;
	struct STMT *stmt;
	struct IDENT *ident;
	struct EXP *exp;
	struct TYPES *type;
}

%token <intconst> tINTCONST
%token <floatconst> tFLOATCONST
%token <stringconst> tIDENTIFIER
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

%type <prog> program 
%type <stmt> stmts stmt read print assign ifst midIf whileloop
%type <dcl> dcls dcl
%type <exp> exp
%type <type> type

%start program
%left '+' '-'
%left '*' '/'
%left UMINUS

%%

program : 	dcls  stmts
				{ theprogram = makePROG ($1,$2,@1.first_line);}
;

dcls :		dcl dcls
				{ $$ = makePROGdcls ($1,$2,@1.first_line);}
			|
				{$$ = NULL;}
;

dcl : 		tVAR tIDENTIFIER ':' type ';'
				{ $$ = makePROGdcl (makePROGid($2,@1.first_line),$4,@1.first_line);}
;

type :		tINT
				{$$ = makePROGdclInt();}
			| tFLOAT
				{$$ = makePROGdclFloat();}
			| tSTRING
				{$$ = makePROGdclString();}
;

stmts : 	stmt stmts 
				{$$ = makePROGstmts ($1,$2,@1.first_line);}
			|
				{$$ = NULL;}
;

stmt :		read
				{$$ = $1;}
			|print
				{$$ = $1;}
			|assign
				{$$ = $1;}
			|ifst
				{$$ = $1;}
			|whileloop
				{$$ = $1;}
;

read :		tREAD tIDENTIFIER ';'
				{$$ = makePROGstmtread(makePROGid($2,@1.first_line),@1.first_line);}
;

print :		tPRINT exp ';'
				{$$ = makePROGstmtprint($2,@1.first_line);}
;

assign :	tIDENTIFIER '=' exp ';'
				{$$ = makePROGstmtassign(makePROGid($1,@1.first_line),$3,@2.first_line);}
;

ifst :		tIF exp tTHEN stmts midIf tENDIF
				{$$ = makePROGstmtif($2,$4,$5,@1.first_line);}
;

midIf :		tELSE stmts
				{$$ = $2;}
			|
				{$$ = NULL;}
;

whileloop :	tWHILE exp tDO stmts tDONE
				{$$ = makePROGstmtwhileloop($2,$4,@1.first_line);}
;

exp :		tIDENTIFIER
				{$$ = makePROGidentifier(makePROGid($1,@1.first_line),@1.first_line);}
			| tINTCONST
				{$$ = makePROGintconst($1,@1.first_line);}
			| tFLOATCONST
				{$$ = makePROGfloatconst($1,@1.first_line);}
			| tSTRINGCONST
				{$$ = makePROGstringconst($1,@1.first_line);}
			| exp '*' exp 
				{$$ = makePROGtimes($1,$3,@2.first_line);}
			| exp '/' exp 
				{$$ = makePROGdiv($1,$3,@2.first_line);}
			| exp '+' exp 
				{$$ = makePROGplus($1,$3,@2.first_line);}
			| exp '-' exp
				{$$ = makePROGminus($1,$3,@2.first_line);}
			| '-' exp %prec UMINUS
				{$$ = makePROGunary($2,@1.first_line);}
			| '(' exp ')' 
				{$$ = $2;}
;

%%