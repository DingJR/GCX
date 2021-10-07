%{
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "parse.h"
#include "error_handle.h"

#define YY_INPUT(buf,result,max_size)  {\
    result = GetNextChar(buf); \
    if ( result <= 0) \
       {result = YY_NULL;}}
//int yywrap(void *);

#define print(x) printf("%s\n",x)
%}
positive_number [0-9]+
negative_number "-"[0-9][0-9]*
float_number [0-9]+\.[0-9]+
crlf  [\n]
comment "//"[^\n]*
ident [A-Za-z]([A-Za-z]|[0-9])*

%%
[\t]+ {BeginToken(yytext);}
" " {BeginToken(yytext);}
{crlf}        {BeginToken(yytext);}
"func"  {BeginToken(yytext); return FUNCSYM;}
"int"  {BeginToken(yytext); return INTSYM;}
"end"  {BeginToken(yytext); return ENDSYM;}
"bool"  {BeginToken(yytext); return BOOLSYM;}
"char"  {BeginToken(yytext); return CHARSYM;}
"const"  {BeginToken(yytext); return CONSTSYM;}
"if"  {BeginToken(yytext); return IFSYM;}
"then"  {BeginToken(yytext); return THENSYM;}
"else"  {BeginToken(yytext); return ELSESYM;}
"while"  {BeginToken(yytext); return WHILESYM;}
"write"  {BeginToken(yytext); return WRITESYM;}
"read"  {BeginToken(yytext);return READSYM;}
"true"  {BeginToken(yytext); return BOOLVALUE;}
"false"  {BeginToken(yytext); return BOOLVALUE;}
"odd"  {BeginToken(yytext); return ODD;}
"repeat"  {BeginToken(yytext); return REPEATSYM;}
"until"  {BeginToken(yytext); return UNTILSYM;}
"break"  {BeginToken(yytext); return BREAKSYM;}
"exit"  {BeginToken(yytext); return EXITSYM;}
"do"  {BeginToken(yytext); return DOSYM;}
"case"  {BeginToken(yytext); return CASESYM;}
"continue"  {BeginToken(yytext); return CONTINUESYM;}
"switch"  {BeginToken(yytext); return SWITCHSYM;}
"return"  {BeginToken(yytext); return RETURNSYM;}
"for"  {BeginToken(yytext); return FORSYM;}
{positive_number}  {BeginToken(yytext); yylval.number = atoi(yytext);
                    return NUMBER;}
{negative_number}  {BeginToken(yytext); yylval.number = -1 * atoi(yytext + 1);
                    return NUMBER;}
{float_number} {BeginToken(yytext); //yylval.number = atof(yytext);
               return FLOATSYM;}
{ident}       {BeginToken(yytext); yylval.ident = (char*)malloc(strlen(yytext) + 1);
               strcpy(yylval.ident, yytext);
                return IDENT;}
{comment}     {BeginToken(yytext);}
"/*"([^\*]|(\*)*[^\*/])*(\*)*"*/" {BeginToken(yytext);}
"++" {BeginToken(yytext); return INC;}
"+" {BeginToken(yytext); return PLUS;}
"--" {BeginToken(yytext); return DEC;}
"-" {BeginToken(yytext); return MINUS;}
"%" {BeginToken(yytext); return MOD;}
"^" {BeginToken(yytext); return XOR;}
"*" {BeginToken(yytext); return TIMES;}
"/" {BeginToken(yytext); return SLASH;}
"<" {BeginToken(yytext); return LES;}
">" {BeginToken(yytext); return GTR;}
"<=" {BeginToken(yytext); return LEQ;}
">=" {BeginToken(yytext); return GEQ;}
"==" {BeginToken(yytext); return EQL;}
"!=" {BeginToken(yytext); return NEQ;}
"||" {BeginToken(yytext); return OR;}
"&&" {BeginToken(yytext); return AND;}
"!" {BeginToken(yytext); return NOT;}
"=" {BeginToken(yytext); return BECOME;}
";" {BeginToken(yytext); return SEMICOLON;}
":" {BeginToken(yytext); return COLON;}
"," {BeginToken(yytext); return COMMA;}
"(" {BeginToken(yytext); return LPAREN;}
")" {BeginToken(yytext); return RPAREN;}
"{" {BeginToken(yytext); return LBPAREN;}
"}" {BeginToken(yytext); return RBPAREN;}
"[" {BeginToken(yytext); return LMPAREN;}
"]" {BeginToken(yytext); return RMPAREN;}


%%
 
int yywrap()
{
   return 1;
}

/*
void redictInput(FILE *input)
{BeginToken(yytext); 
  int ret = getc(yyin);
  printf ("%c", ret);
  return ret;
}

int yywrap(void* a)
{
  return 1;
}
*/
