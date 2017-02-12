
# Basic Makefile -- provides explicit rules
# Creates "myprogram" from "scan.l" and "myprogram.c"
#
LEX=flex
CC = gcc

minilang: y.tab.o lex.yy.o main.o tree.h tree.o pretty.h pretty.o memory.h memory.o
	$(CC) lex.yy.o y.tab.o tree.o pretty.o memory.o main.o -o minilang -ll

y.tab.c y.tab.h: minilangParser.y
	bison --yacc --defines minilangParser.y

lex.yy.c: minilangScan.l
	$(LEX) minilangScan.l

clean:
	rm y.tab.* lex.yy.*; rm *.o; rm minilang
