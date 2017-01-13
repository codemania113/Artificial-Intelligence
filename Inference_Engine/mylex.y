%{
#include "homework.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <map>
using namespace std;
#define YYSTYPE char*
typedef struct yy_buffer_state *YY_BUFFER_STATE;
YY_BUFFER_STATE yy_scan_buffer(char *,size_t);
void yy_delete_buffer(YY_BUFFER_STATE buffer);
void yy_switch_to_buffer(YY_BUFFER_STATE buffer);
extern int yylex(void);
extern map<string,int> kbase;
char str[10001];
char str1[10001];
char str2[10001];
char str3[10001];
char str4[10001];
char str6[10001];
//char *exp1 = NULL;
//char *exp2 = NULL;
//char *exp5 = NULL;
//char exp3[10001];
//char exp4[10001];
//char exp6[10001];
char final_string[10001];

void connect(char[],char[])
{
}
void yyerror(const char *str)
{
}

int yywrap()
{
	return 1;
}


char* remove_implies(char *exp1, char *exp2)
{
	char new_exp[10001];
	strcpy(str,(const char*)"(");
	strcat(str,exp1);
	strcat(str,(const char*)"|");
	strcat(str,exp2);
	strcat(str,(const char*)")");
	return str;
}

char* process_or(char *exp1, char *exp2)
{
	strcpy(str2,(const char*)"(");
	strcat(str2,exp1);
	strcat(str2,(const char*)"|");
	strcat(str2,exp2);
	strcat(str2,(const char*)")");
	return str2;
}

char* process_and(char *exp1, char *exp2)
{
    strcpy(str3,(const char*)"(");
	strcat(str3,exp1);
	strcat(str3,(const char*)"&");
	strcat(str3,exp2);
	strcat(str3,(const char*)")");
	return str3;
}

char* process_p(char *exp1)
{
    strcpy(str6,exp1);
	return str6;
}

char* move_negation_inside(char *exp1)
{
	if(exp1[0] == '(')
	{
		if(exp1[1] == '~')
		{
			int l = strlen(exp1);
			strcpy(str1,exp1+2);
			str1[l-3] = '\0';
		}
		else
		{
			int top = -1;
			int i = 1;
			while(1)
			{
				if((exp1[i] == '|') || (exp1[i] == '&'))
				{
					if(top == -1)
						break;
				}
				else if(exp1[i] == '(')
				{
					top++;
				}
				else if(exp1[i] == ')')
				{
					top--;
				}
				i++;
			}

			strcpy(str1,(const char*)"(");
			strcat(str1,(const char*)"(");
			strcat(str1,(const char*)"~");
			strcat(str1,exp1+1);
			str1[i+2] = ')';
			str1[i+3] = '\0';
			if(exp1[i] == '&')
				strcat(str1,(const char*)"|");
			else
				strcat(str1,(const char*)"&");

			strcat(str1,(const char*)"(");
			strcat(str1,(const char*)"~");
			strcat(str1,exp1+i+1);
			strcat(str1,(const char*)")");
		}
	}
	else
	{
		strcpy(str1,(const char*)"(");
		strcat(str1,(const char*)"~");
		strcat(str1,exp1);
		strcat(str1,(const char*)")");
	}
	return str1;
}

char* move_negation(char *exp)
{
    if(exp[0] != '(')
	{
        strcpy(str4,(const char*)"(");
		strcat(str4,(const char*)"~");
		strcat(str4,exp);
		strcat(str4,(const char*)")");
        return str4;
	}
	else
	{
		if(exp[1] != '~')
		{
            int top = -1;
			int i = 1;
			int l = strlen(exp);
			char op;
			while(1)
			{
				if((exp[i] == '|') || (exp[i] == '&'))
				{
					if(top == -1)
						break;
				}
				else if(exp[i] == '(')
				{
					top++;
				}
				else if(exp[i] == ')')
				{
					top--;
				}
				i++;
			}
            op = exp[i];
            char *exp3 = (char*)malloc(sizeof(char)*10001);
			char *exp4 = (char*)malloc(sizeof(char)*10001);
			strcpy(exp3,exp+1);
			exp3[i-1] = '\0';
            strcpy(exp4,exp+i+1);
			int g = strlen(exp4);
			exp4[g-1] = '\0';
			char *exp1 = (char*)malloc(sizeof(char)*10001);
			char *exp2 = (char*)malloc(sizeof(char)*10001);
			strcpy(exp1, move_negation(exp3));
			strcpy(exp2, move_negation(exp4));
			strcpy(str4,(const char*)"(");
			strcat(str4,exp1);
			if(op == '|')
				strcat(str4,(const char*)"&");
			else
				strcat(str4,(const char*)"|");
			strcat(str4,exp2);
			strcat(str4,(const char*)")");
			free(exp1);
			exp1 = NULL;
			free(exp2);
			exp2 = NULL;
            free(exp3);
            free(exp4);
            exp3 = NULL;
            exp4 = NULL;
			return str4;
		}
		else if(exp[1] == '~')
		{
			char op = '~';
			char *exp6 = (char*)malloc(sizeof(char)*10001);
			int l = strlen(exp);
			strcpy(exp6,exp+2);
			exp6[l-3] = '\0';
			char *exp5 = (char*)malloc(sizeof(char)*10001);
			strcpy(exp5, move_negation(exp6));
			if(exp5[0] == '(')
			{
				int len = strlen(exp5);
				strcpy(str4,exp5+2);
				str4[len-3] = '\0';
			}
			else
			{
				strcpy(str4,(const char*)"(");
				strcat(str4,(const char*)"~");
				strcat(str4,exp5);
				strcat(str4,(const char*)")");
			}
			free(exp5);
			exp5 = NULL;
            free(exp6);
           	exp6 = NULL;
			return str4;
		}
	}
}


%}

%token PREDICATE
%token IMPLIES
%token OBRACE
%token EBRACE
%token AND
%token OR
%token NEGATE
%token WORD
%token HASH
%%
term:
	expression
    {

                 kbase.insert(pair<string,int>($$,1));
    }
	|
    term HASH expression
    {
    }
    ;
expression:
	OBRACE expression AND expression EBRACE
	{
		char *val = NULL;
		val = (char*)process_and($2,$4);
		strcpy($$,val);
        strcpy(final_string,$$);
	}
	|
	OBRACE expression OR expression EBRACE
	{
		char *val = NULL;
		val = (char*)process_or($2,$4);
		strcpy($$,val);
        strcpy(final_string,$$);
	}
	|
	OBRACE NEGATE expression EBRACE
	{
		char *val = NULL;
		val = (char*)move_negation($3);
		strcpy($$,val);
        strcpy(final_string,$$);
	}
	|
	OBRACE expression IMPLIES expression EBRACE
	{
		char *val = NULL;
		char *val1 = NULL;
		//char *val1 = (char*)malloc(sizeof(char)*1001);
		//char *val2 = (char*)malloc(sizeof(char)*1001);
		val1 = (char*)move_negation($2);
		val = (char*)remove_implies(val1,$4);
		strcpy($$,val);
        strcpy(final_string,$$);
	}
	|
	PREDICATE
    {
		char *val = NULL;
		val = (char*)process_p($1);
		strcpy($$,val);
        strcpy(final_string,$$);
	}
    ;
%%
