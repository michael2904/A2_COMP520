#include <stdio.h>
#include <stdlib.h>

extern FILE *yyin;
extern int yyparse(void);

int main(int argc,char *argv[]){
	int result;
	if ( argc > 1 ){
		printf("reading file %s\n",argv[1]);
		yyin = fopen( argv[1], "r" );
	}else{
		yyin = stdin;
	}
	result = yyparse ();
	return(result);
}