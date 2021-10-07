#include <stdio.h>
#include "list.h"

extern 
property *construct(int num, list *truelist, list *falselist, list *nextlist)
{
  property *temp = (property*)malloc(sizeof(property));
  temp->falselist = falselist;
  temp->truelist = truelist;
  temp->nextlist = nextlist;
  temp->num = num;
  return temp;
}

extern 
list *property_truelist(property* p)
{
  if(p==NULL)return NULL;
  return p->truelist;
}

extern 
list *property_falselist(property* p)
{
  if(p==NULL)return NULL;
  return p->falselist;
}

extern 
list *list_nextlist(property* p)
{
  if(p==NULL)return NULL;
  list* temp = p->nextlist;
  free(p);
  return temp;
}

extern 
int property_value(property* p)
{
  if(p==NULL)return 0;
   return p->num;
}

extern 
list* merge(list* aList, list* bList)
{
  if(aList==NULL)return bList;
  if(bList==NULL)return aList;
  while(aList->next!=NULL)
    aList = aList->next;
  aList->next = bList;
  return aList;
}

extern 
list* makelist(int n)
{
  if(n==0)return NULL;
  list *temp = (list*)malloc(sizeof(list));
  temp->next = NULL;
  temp->num = n;
  return temp;
}

extern 
int list_value(list* in)
{
  if(in==NULL)return 0;
  return in->num;
}

extern 
list *next(list* in)
{
  if(in==NULL)return NULL;
  return in->next;
}

