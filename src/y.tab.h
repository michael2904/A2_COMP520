/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     tINTCONST = 258,
     tFLOATCONST = 259,
     tIDENTIFIER = 260,
     tSTRINGCONST = 261,
     tVAR = 262,
     tWHILE = 263,
     tDO = 264,
     tDONE = 265,
     tIF = 266,
     tTHEN = 267,
     tELSE = 268,
     tENDIF = 269,
     tFLOAT = 270,
     tINT = 271,
     tSTRING = 272,
     tPRINT = 273,
     tREAD = 274,
     UMINUS = 275,
     tERROR = 276
   };
#endif
/* Tokens.  */
#define tINTCONST 258
#define tFLOATCONST 259
#define tIDENTIFIER 260
#define tSTRINGCONST 261
#define tVAR 262
#define tWHILE 263
#define tDO 264
#define tDONE 265
#define tIF 266
#define tTHEN 267
#define tELSE 268
#define tENDIF 269
#define tFLOAT 270
#define tINT 271
#define tSTRING 272
#define tPRINT 273
#define tREAD 274
#define UMINUS 275
#define tERROR 276




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 17 "minilangParser.y"
{
	int intconst;
	float floatconst;
	char *stringconst;
	struct PROG *prog;
	struct DECL *dcl;
	struct STMT *stmt;
	struct IDENT *ident;
	struct EXP *exp;
}
/* Line 1529 of yacc.c.  */
#line 102 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYLTYPE yylloc;
