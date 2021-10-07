#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include "interpreter.h"
//#define debug

struct instruction code[C_MAX];
extern 
void backpatch(list *l, int num)
{
  while(l!=NULL)
  {
    printf("%d ",l->num); 
      code[l->num].var = num;
      l = l->next;
  }
  putchar('\n');
}

static 
struct stack
{
  int data[D_MAX];
  int top;
}stack;

static 
int base(int leval, int base)
{
  int cb = base;
  while(leval > 0)
  {
    leval--;
    cb = stack.data[cb];
  }
  return cb;
}

static
int isTerminal(struct instruction i)
{
  if(i.var==0&&i.action==0)
    return 1;
  return 0;
}

static
void printStack()
{
  printf("     stack\n");
  for(int i=stack.top; i>=0; i--)
  {
    printf("     %d\n", stack.data[i]);
  }
}

static
void printInstruction(struct instruction i)
{
    switch(i.action)
    {
      case par_id:
        printf("par_id ");
        break;
      case lit:
        printf("lit ");
        break;
      case out:
        printf("out ");
        break;
      case in:
        printf("in ");
        break;
      case par:
        printf("par ");
        break;
      case end:
        printf("end ");
        break;
      case ret:
        printf("ret ");
        break;
      case dup:
        printf("dup ");
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
      case pop:
        printf("pop ");
        break;
    }
    printf("%d %d\n", i.lev, i.var);
}

extern
void interpreter()
{
    int ip = 0; //instruction pointer
    stack.top = 100;
    struct instruction i = code[ip];
    do
    {
      i = code[ip++];

#ifdef debug
      printf("%5d ",stack.top);
      printInstruction(i);
#endif
      switch((int)i.action)
      {
        case lit:
          stack.top = stack.top + 1;
          stack.data[stack.top] = i.var;
          break;
        case dup:
          stack.top = stack.top + 1;
          stack.data[stack.top] = stack.data[stack.top - 1];
          break;
        case pop:
          stack.top = stack.top - 1;
          break;
        case arr:
          stack.top = stack.top + i.var;
        case opr:
          {
            switch(i.var)
            {
              case ODD:
                stack.data[stack.top] = stack.data[stack.top] % 2;
                break;
              case INC:
                stack.data[stack.top] = stack.data[stack.top] + 1;
                break;
              case DEC:
                stack.top--;
                stack.data[stack.top] = stack.data[stack.top] - 1;
                break;
              case MOD:
                stack.top--;
                stack.data[stack.top] = stack.data[stack.top] % stack.data[stack.top + 1];
                break;
              case NOT:
                stack.data[stack.top] = stack.data[stack.top]==0? 1:0 ;
                break;
              case PLUS:
                stack.top--;
                stack.data[stack.top] = stack.data[stack.top] + stack.data[stack.top + 1];
                break;
              case MINUS:
                stack.top--;
                stack.data[stack.top] = stack.data[stack.top] - stack.data[stack.top + 1];
                break;
              case SLASH:
                stack.top--;
                stack.data[stack.top] = stack.data[stack.top] / stack.data[stack.top + 1];
                break;
              case TIMES:
                stack.top--;
                stack.data[stack.top] = stack.data[stack.top] * stack.data[stack.top + 1];
                break;
              case LES:
                stack.top--;
                stack.data[stack.top] = stack.data[stack.top] < stack.data[stack.top + 1];
                break;
              case LEQ:
                stack.top--;
                stack.data[stack.top] = stack.data[stack.top] <= stack.data[stack.top + 1];
                break;
              case GTR:
                stack.top--;
                stack.data[stack.top] = stack.data[stack.top] > stack.data[stack.top + 1];
                break;
              case GEQ:
                stack.top--;
                stack.data[stack.top] = stack.data[stack.top] >= stack.data[stack.top + 1];
                break;
              case EQL:
                stack.top--;
                stack.data[stack.top] = stack.data[stack.top] == stack.data[stack.top + 1];
                break;
              case NEQ:
                stack.top--;
                stack.data[stack.top] = stack.data[stack.top] != stack.data[stack.top + 1];
                break;
              case XOR:
                stack.top--;
                stack.data[stack.top] = stack.data[stack.top] ^ stack.data[stack.top + 1];
                break;
              case OR:
                stack.top--;
                stack.data[stack.top] = stack.data[stack.top] || stack.data[stack.top + 1];
                break;
              case AND:
                stack.top--;
                stack.data[stack.top] = stack.data[stack.top] && stack.data[stack.top + 1];
                break;
            }
          }
          break;
      case lod:
          ++stack.top;
          stack.data[stack.top] = stack.data[i.var];
          break;
      case sto:
          stack.data[i.var] = stack.data[stack.top];
          stack.top--;
          break;
      case jmp:
          ip = i.var;
          break;
      case jpc:
          if(stack.data[stack.top--] == 0)
            ip = i.var;
          break;
      case in:
          stack.top++;
          scanf("%d", &stack.data[stack.top]);
          break;
      case out:
          printf("%d\n", stack.data[stack.top--]);
          break;
      }
#ifdef debug
      printStack();
#endif
    }while(ip!=0 && !isTerminal(i));
}







