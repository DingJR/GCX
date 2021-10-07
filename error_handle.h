#ifndef ERROR_HANDLE_H_
#define ERROR_HANDLE_H_

#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdarg.h>
#include "parse.h"
extern FILE *file;
extern int GetNextChar(char *b);
extern void BeginToken(char*);
extern void PrintError(const char *s, ...);

#endif
