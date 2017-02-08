%{
	#include "y.tab.h"  /* for exp.y types */
	#include <string.h> /* for strlen */
	#include <stdlib.h> /* for malloc and atoi */
%}

DIGIT		[0-9]
ALPHA		[a-zA-Z_]

%option noyywrap

%%

[ \t\n\r]+		/* ignore */;

"var"		return tVAR;
"while"		return tWHILE;
"do"		return tDO;
"done"		return tDONE;
"if"		return tIF;
"then"		return tTHEN;
"else"		return tELSE;
"endif"		return tENDIF;
"float"		return tFLOAT;
"int"		return tINT;
"string"	return tSTRING;
"print"		return tPRINT;
"read"		return tREAD;


"*"			return '*';
"/"			return '/';
"+"			return '+';
"-"			return '-';
"("			return '(';
")"			return ')';
":"			return ':';
";"			return ';';
"="			return '=';

0|([1-9]{DIGIT}*) {
			yylval.intconst = atoi (yytext);
			return tINTCONST;
}

([1-9]{DIGIT}*|0)"."{DIGIT}+	{
			yylval.floatconst = atof(yytext);
			return tFLOATCONST;
}

[a-zA-Z_][a-zA-Z0-9_]* {
			yylval.stringconstid = (char *) malloc (strlen (yytext) + 1);
			sprintf (yylval.stringconstid, "%s", yytext);
			return tIDENTIFIER;
}

\"(\\.|[^"])*\" {
			yylval.stringconst = (char *) malloc (strlen (yytext) + 1);
			sprintf (yylval.stringconst, "%s", yytext);
			return tSTRINGCONST;
}

"//".*		/* ignore */

.			{
			printf ("INVALID: syntax error before -%s-\n", yytext); 
			exit(1);
			}

%%