%{
	#include <iostream>
	#include <string.h>
	#include <ctype.h>
	#include "y.tab.h"
	using namespace std;
	extern char* yylval;
	//extern int yylex();
	//extern int yyparse(void);
	int x, product, mode, sq;
	//int yylex(void);
	extern int yyparse();
	//int yylval();
	//int yywrap();
%}
%option noyywrap
%%
\(	yylval = strdup(yytext); return OBRACE;
\)	yylval = strdup(yytext); return EBRACE;
[a-zA-Z][a-zA-Z]*[(][a-zA-Z][a-zA-Z,]*[)]	yylval = strdup(yytext); return PREDICATE;
[\t]+	/*ignore*/
\n
=>	yylval = strdup(yytext); return IMPLIES;
\|	yylval = strdup(yytext); return OR;
\&	yylval = strdup(yytext); return AND;
~	yylval = strdup(yytext); return NEGATE;
#	yylval = strdup(yytext); return HASH;
%%

