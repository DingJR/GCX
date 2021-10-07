#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "parse.h"
#define C_MAX 100000
#define D_MAX 100000
enum act{end, lit, pop, lod, sto, cal, ret, arr, jmp, jpc, opr, dup, in, out, par, par_id};
struct instruction
{
  enum act action;
  int lev;
  int var;
};
extern void interpreter();
extern void backpatch(list *l, int num);
#endif 
