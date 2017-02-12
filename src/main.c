#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "y.tab.h"
#include "pretty.h"


extern FILE *yyin;
extern int yyparse(void);
PROG *theprogram;
int lineno;

int main(int argc,char *argv[]){
	int result;
	if ( argc > 1 ){
		printf("reading file %s\n",argv[1]);
		yyin = fopen( argv[1], "r" );
	}else{
		yyin = stdin;
	}
	result = yyparse ();
	int outPrettyLen = strlen(argv[1]) + 7 + 1;

	char *outPrettyFN = (char*)malloc(outPrettyLen * sizeof(char));
	FILE *outPretty= fopen(outPrettyFN, "w");
	prettyPROG(theprogram);
	printf("*************-DONE-*************\n");
	if(result == 0) {
		printf("\nVALID \n");
	} else {
		printf("\nINVALID \n");
	}
	return(result);
}