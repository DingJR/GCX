%{
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include "interpreter.h"
#include "list.h"
#include "error_handle.h"
extern struct instruction code[C_MAX];

#define YYERROR_VERBOSE 1
#define YYDEBUG 1
#define symbolTableMax 10000
#define symbolLenMax 20
#define procLevel 10

struct tableStruct
{
  char name[symbolLenMax]; //identifier name
  int adr;//variable address
};
int type; 
struct tableStruct table[symbolTableMax];
int procedure_table[3];
int tp; //table point
int cp; //code point
int errNum;
int addr;


void init();
int position(char *s);
void enter(char *s);
int yylex();
void printTableList();
void printCode();
void yyerror(const char*);

/**********************************
 *
 * interpreter function
 *
 **********************************/
int gen(enum act action, int lev, int var);
void interpreter();
void backpatch(list *l, int num);


/**********************************
 *
 * list function
 *
 **********************************/
list* merge(list* aList, list* bList);
list* makelist(int n);
list *list_nextlist(property* p);
list *property_truelist(property* p);
list *property_falselist(property* p);
int list_value(list *in);
property *construct(int num, list *truelist, list *falselist, list *nextlist);
int property_value(property* p);
%}

%defines
%union{
  char *ident;
  char letter;
  int  number;
}

%token CASESYM FORSYM SWITCHSYM BREAKSYM CONTINUESYM EXITSYM DOSYM REPEATSYM UNTILSYM 
%token IFSYM THENSYM WHILESYM WRITESYM READSYM RETURNSYM ENDSYM
%token INTSYM FLOATSYM BOOLSYM CHARSYM CONSTSYM FUNCSYM
%token SEMICOLON COLON LPAREN RPAREN LBPAREN RBPAREN LMPAREN RMPAREN COMMENT COMMA
%token INC DEC ODD MOD PLUS MINUS SLASH TIMES LES LEQ GTR GEQ EQL NEQ BECOME XOR OR AND NOT 
%token <ident> IDENT
%token <number> NUMBER
%token <letter> LETTER

%type <number> get_code_addr
%type <number> id term factor if
%nonassoc IFX
%nonassoc ELSESYM


%left OR XOR
%left AND
%left NOT ODD
%left LES LEQ GTR GEQ EQL NEQ
%left PLUS MINUS 
%left SLASH TIMES MOD
%left IDENT NUMBER LETTER BOOLVALUE


%%
program :
        stmts
get_code_addr: {$$ = cp;};
stmts: stmts SEMICOLON
       stmt 
      |stmts error SEMICOLON stmt
      |stmt
if: IFSYM 
    term
    get_code_addr
    {
@1;
      gen(jpc, 0, 0);}
    stmts
    {
      code[$3].var = cp;
      $$=$3;}

stmt: assignment
    | if %prec IFX ENDSYM
    | if 
      ELSESYM
      get_code_addr
      {
        gen(jmp, 0, 0);
        code[$1].var = cp;}
      stmt
      {
        code[$3].var = cp;}
      ENDSYM
    | REPEATSYM
      get_code_addr
      stmts
      UNTILSYM
      term
      {
        gen(jpc, 0, $2);}
    | WRITESYM 
      term 
      {
          gen(out, 0, 0);
      }
    | READSYM 
      id
      {
        gen(in, 0, 0);
        if($2!=0){
          gen(sto, 0, table[$2].adr);
        } else {
          gen(sto, 0, table[tp].adr);
        }
      }
    | FORSYM
      LPAREN
      stmt
      SEMICOLON
      get_code_addr
      term
      get_code_addr
      {
        gen(jpc, 0, 0);}
      get_code_addr
      {
        gen(jmp, 0, 0);}
      SEMICOLON
      get_code_addr
      assignment
      {
        gen(jmp, 0, $5); 
        code[$9].var = cp;}
      RPAREN
      LBPAREN
      stmts
      RBPAREN
      {
        gen(jmp, 0, $12);
        code[$7].var = cp;}
assignment: id BECOME term 
            {
            if($1==0){
             gen(sto, 0, table[tp].adr);
            } else {
             gen(sto, 0, table[$1].adr);
            }
            }

id: IDENT {
      int varPos = position($1);
      if(varPos)
      {
        $$ = varPos;}
      else{
        enter($1);
        $$ = 0;
      }}
term : term LES term
     {
      gen(opr, 0, LES);}
    |  term GTR term
     {
      gen(opr, 0, GTR);}
    |  term NEQ term
     {
      gen(opr, 0, NEQ);}
    |  term EQL term
     {
      gen(opr, 0, EQL);}
    |  term LEQ term
     {
      gen(opr, 0, LEQ);}
    |  term GEQ term
     {
      gen(opr, 0, GEQ);}
    |  term TIMES term
     {
      gen(opr, 0, TIMES);}
    |  term SLASH term
     {
      gen(opr, 0, SLASH );}
    |  term MOD term
     {
      gen(opr, 0, MOD);}
    |  term MINUS term
     {
      gen(opr, 0, MINUS );}
    |  term PLUS term
     {
      gen(opr, 0, PLUS);}
    |  term OR term
     {
      gen(opr, 0, OR);}
    |  term XOR term
     {
      gen(opr, 0, XOR);}
    |  term AND term
     {
      gen(opr, 0, AND);}
     | factor
factor: id
        {
        if($1==0)
        {
          char temp[1000];
          strcpy(temp, "Not Defined Identifier ");
          strcat(temp, table[tp].name);
          yyerror(temp);
        }
        else
         gen(lod, 0, table[$1].adr);
        }
       | NUMBER
         {
         gen(lit, 0, $1); }
%%

void init()
{
    tp = 0;
    cp = 0;
    errNum = 0;
}

void enter(char *currentSymbol)
{
    tp = tp + 1;
    table[tp].adr = tp;
    strcpy(table[tp].name, currentSymbol);
}

void printTableList()
{
    for(int i=1; i<=tp; i++)
    {
          printf("  %d variable %s ", i, table[i].name);
          printf("addr=%d\n", table[i].adr);
          break;
    }
}

void printCode()
{
  printf("\nassemble code\n");
  for(int i=0; i < cp; i++)
  {
    printf("%5d ",i);
    switch(code[i].action)
    {
      case lit:
        printf("lit ");
        break;
      case par:
        printf("par ");
        break;
      case par_id:
        printf("par_id ");
        break;
      case ret:
        printf("ret ");
        break;
      case out:
        printf("out ");
        break;
      case in:
        printf("in ");
        break;
      case dup:
        printf("dup ");
        break;
      case pop:
        printf("pop ");
        break;
      case lod:
        printf("lod ");
        break;
      case sto:
        printf("sto ");
        break;
      case jmp:
        printf("jmp ");
        break;
      case arr:
        printf("arr ");
        break;
      case jpc:
        printf("jpc ");
        break;
      case cal:
        printf("cal ");
        break;
      case opr:
        printf("opr ");
        break;
    }
    printf("%d %d\n", code[i].lev, code[i].var);
  }
}
void yyerror(const char* a){
  PrintError(a);
  errNum += 1;
}

int gen(enum act action, int lev, int var)
{
    struct instruction i ;
    i.action = action;
    i.lev = 0;
    i.var = var;
    code[cp++] = i;
    return 0;
}

int position(char *s)
{
    int i = tp;
    while(strcmp(table[i].name, s) != 0 && i > 0) i--;
    return i;
}

int main(int argv, char**args)
{
  init();
  extern FILE* file;
  FILE* fp_handle = fopen(args[1], "r");
  file = fp_handle;
  //yyin = fp;
/*
extern int yydebug;
yydebug = 5;
*/
  yyparse();
  if(errNum == 0)
  {
    printCode();
    interpreter();
  }

  fclose(file);
  return 0;
}









