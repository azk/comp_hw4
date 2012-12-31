%{
    #include "shared.h"
    #include "coins.tab.hpp"
%}
%option noyywrap

whitespace	([\t\n ])

%%

")"	return LP;
"("	return RP;
"{"	return LC;
"}"	return RC;
";"	return SC;
"="	return ASSIGN;
[+]	return PLUS;
[-]	return MINUS;
[*]	return MULT;
[/]	return DIV;
"<="	return SE;
">="	return GE;
"=="	return EQ;
"!="	return NEQ;
">"	return GT;
"<"	return ST;
"and"	return AND;
"or"	return OR;
"int"	return INT;
"NIS"	return NIS;
"AGORA"	return AGORA;
"print"	return PRINT;
"input"	return INPUT;
"true"	return TRUE;
"false"	return FALSE;
"if"	return IF;
"else"	return ELSE;
"while"	return WHILE;
"break"	return BREAK;
"not"	return NOT;
"bool"	return BOOL;
[a-zA-Z]+      {strcpy(yylval.name,yytext); return ID;}
\"[^"]*\"      {strcpy(yylval.name,yytext); return STRING;}
([1-9][0-9]*)|0	{yylval.number = atoi(yytext);return NUM;}
{whitespace}	;
"//"[^\n]*\n	; // Comments

%%

