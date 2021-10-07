#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include <stdlib.h>

typedef struct list
{
  int num;
  struct list *next;
}list;

typedef struct property
{
  int num;
  struct list *truelist;
  struct list *falselist;
  struct list *nextlist;
}property;

extern list* merge(list* aList, list* bList);
extern list* makelist(int n);
extern list *next(list* in);
extern int list_value(list* in);

extern property *construct(int num, list *truelist, list *falselist, list *nextlist);
extern list *list_nextlist(property* p);
extern list *property_truelist(property* p);
extern list * property_falselist(property* p);
extern int property_value(property* p);

#endif
