#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "pretty.h"
#include "symbol.h"
#include "y.tab.h"


extern FILE *yyin;
extern int yyparse(void);
PROG *theprogram;
SymbolTable *symbolTable;
int lineno;
char *prettyFilePath = NULL;
char *symbolFilePath = NULL;
char *generatedFilePath = NULL;


void prepFilePath(char *filePath){
	char *path;
	char *token;
	char *name;
	char *type;
	path = strdup(filePath);
	int i = 0;
	while((token = strsep(&path, "/"))){
		if(i > 1) type = name;
		name = token;
		i++;
	}
	free(path);
	name = strsep(&name, ".");
	char prettyFileS[10]="./pretty/";
	char prettyFileE[12]=".pretty.min";
	int prettyFileSize= strlen(prettyFileS)+strlen(type)+2+strlen(name)+strlen(prettyFileE);
	prettyFilePath = (char *)malloc(prettyFileSize* sizeof(char));
	sprintf(prettyFilePath, "%s%s/%s%s", prettyFileS,type,name,prettyFileE);
	// prettyFilePath[prettyFileSize] = '\0';
	printf("prettyFilePath - %s----\n",prettyFilePath );

	char symbolFileS[10]="./symbol/";
	char symbolFileE[12]=".symbol.txt";
	int symbolFileSize= strlen(symbolFileS)+strlen(type)+2+strlen(name)+strlen(symbolFileE);
	symbolFilePath = (char *)malloc(symbolFileSize* sizeof(char));
	sprintf(symbolFilePath, "%s%s/%s%s", symbolFileS,type,name,symbolFileE);
	// symbolFilePath[symbolFileSize] = '\0';
	printf("symbolFilePath - %s----\n",symbolFilePath );

	char generatedFileS[13]="./generated/";
	char generatedFileE[3]=".c";
	int generatedFileSize= strlen(generatedFileS)+strlen(type)+2+strlen(name)+strlen(generatedFileE);
	generatedFilePath = (char *)malloc(generatedFileSize* sizeof(char));
	sprintf(generatedFilePath, "%s%s/%s%s", generatedFileS,type,name,generatedFileE);
	// generatedFilePath[generatedFileSize] = '\0';
	printf("generatedFilePath - %s----\n",generatedFilePath );

}

int main(int argc,char *argv[]){
	int result;
	if ( argc > 0 ){
		printf("reading file %s\n",argv[1]);
		yyin = fopen( argv[1], "r" );
	}else{
		printf("This is not a file\n");
		yyin = stdin;
	}
	result = yyparse ();
	fclose(yyin);
	prepFilePath(argv[1]);
	printf("prettyFilePath - %s----\n",prettyFilePath );
	printf("symbolFilePath - %s----\n",symbolFilePath );
	printf("generatedFilePath - %s----\n",generatedFilePath );
	prettyPROG(theprogram);
	makeProgSymbolTable(theprogram);
	typeCheckProg(theprogram);
	generateProg(theprogram);
	if(result == 0) {
		printf("\nVALID \n");
	} else {
		printf("\nINVALID \n");
	}
	return(result);
}