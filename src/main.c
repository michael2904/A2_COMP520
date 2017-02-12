#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "y.tab.h"
#include "pretty.h"


extern FILE *yyin;
extern int yyparse(void);
PROG *theprogram;
int lineno;
FILE *outPretty;

void replace(char *str, char *orig, char *rep, char *dest)
{
	printf("Replacing %s %s %s %s\n",str,orig,rep,dest);

	char *p;
	if(!(p = strstr(str, orig)))  // Is 'orig' even in 'str'?
		return;
	printf("*************-DONE Is 'orig' even in 'str'?-*************\n");

	strncpy(dest, str, p-str); // Copy characters from 'str' start to 'orig' st$
	printf("*************-DONE strncpy-*************\n");
	dest[p-str] = '\0';

	sprintf(dest+(p-str), "%s%s", rep, p+strlen(orig));
	printf("*************-DONE sprintf-*************\n");
}

void remakeFile(char *fileName,char *replName){
	char *sub1 = "min";
	int outPrettyLen1 = strlen(fileName) + strlen(replName) - strlen(sub1);
	char *rep1 = (char*)malloc((strlen(replName) + strlen(sub1) + 1) * sizeof(char));
	rep1 = strcat(strcat(strcat(rep1,replName),"."),sub1);
	
	char *outPrettyFN1 = (char*)malloc(outPrettyLen1 * sizeof(char));
	replace(fileName, sub1, rep1, outPrettyFN1);
	printf("*************-DONE First replace %s-*************\n",outPrettyFN1);
	free(sub1);
	free(rep1);
	char *sub2 = "programs";
	int outPrettyLen2 = strlen(outPrettyFN1) + strlen(replName) - strlen(sub2);
	printf("*************-DONE Getting length %d-*************\n",outPrettyLen2);
	char *outPrettyFN2 = (char*)malloc(outPrettyLen2 * sizeof(char));
	printf("*************-DONE Allocating %s-*************\n",outPrettyFN2);
	replace(outPrettyFN1, sub2, replName,outPrettyFN2);
	printf("*************-DONE Second replace %s-*************\n",outPrettyFN2);
	free(sub2);
	outPretty = fopen(outPrettyFN1, "w");
	printf("reading file %s\n",outPrettyFN1);
}


void clovisFile(char *filePath){
	char *delimiter;
	char *path;
	char *token, *completeFileName, *name,*fileName;
	path = strdup(filePath);
	delimiter = "/";
	while((token = strsep(&path, delimiter))){
	completeFileName = token;
	}
	free(path);
	delimiter = ".";
	name = strsep(&completeFileName, delimiter);
	fileName = (char *)malloc(strlen(name));
}

int main(int argc,char *argv[]){
	int result;
	if ( argc > 1 ){
		printf("reading file %s\n",argv[1]);
		yyin = fopen( argv[1], "r" );
	}else{
		yyin = stdin;
	}
	result = yyparse ();
	printf("*************-DONE PARSING-*************\n");
	// remakeFile(argv[1],"pretty");
	// outPretty = fopen(outPretty, "w");
	prettyPROG(theprogram);
	printf("*************-DONE-*************\n");
	if(result == 0) {
		printf("\nVALID \n");
	} else {
		printf("\nINVALID \n");
	}
	return(result);
}