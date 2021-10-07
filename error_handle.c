#include "error_handle.h"

FILE *file = NULL;
static int eof = 0;
static int nRow = 0;
static int nBuffer = 0;
static int lBuffer = 0;
static int nTokenStart = 0;
static int nTokenLength = 0;
static int nTokenNextStart = 0;
static int lMaxBuffer = 1000;
static char buffer[1000];

static
char PrintChar(char c) {
  if (isprint(c))
    return c;
  return '@';
}

static
char *PrintString(char *s) {
  static char buf[101];
  int i;
  int n = strlen(s);
  if (  n > 100  )
    n = 100;
  for (i=0; i<n; i++)
    buf[i] = PrintChar(s[i]);
  buf[i] = 0;
  return buf;
}

static
void PrintRow(void) {
  if (  nRow == 0  ) 
    fprintf(stdout, "*********************************\n"); 
  else 
    fprintf(stdout, "\n%6d |%.*s", nRow, lBuffer, buffer);
}

extern
void PrintError(const char *errorstring, ...) {
  static char errmsg[10000];
  PrintRow();
  va_list args;
  int start=nTokenStart;
  int end=start + nTokenLength - 1;
  int i;
  if (  eof  ) {
    fprintf(stdout, "...... !");
    for (i=0; i<lBuffer; i++)
      fprintf(stdout, ".");
    fprintf(stdout, "^-EOF\n");
  }
  else {
    fprintf(stdout, "...... !");
    for (i=0; i<start; i++)
      fprintf(stdout, ".");
    for (i=start; i<=end; i++)
      fprintf(stdout, "^");
    for (i=end+1; i<lBuffer; i++)
      fprintf(stdout, ".");
    fprintf(stdout, "   token%d:%d\n", start, end);
  }
  va_start(args, errorstring);
  vsprintf(errmsg, errorstring, args);
  va_end(args);
  fprintf(stdout, "Error: %s\n", errmsg);
}

static
int getNextLine() {
  char *p;
  nBuffer = 0;
  nTokenStart = -1;
  nTokenNextStart = 1;
  eof = 0;
  p = fgets(buffer, lMaxBuffer, file);
  if (  p == NULL  ) {
    if (  ferror(file)  )
      return -1;
    eof = 1;
    return 1;
  }
  nRow += 1;
  lBuffer = strlen(buffer);
  return 0;
}

extern
int GetNextChar(char *b) {
  int frc;
  if (  eof  )
    return 0;
  while (  nBuffer >= lBuffer  ) {
    frc = getNextLine();
    if (  frc != 0  )
      return 0;
    }
  b[0] = buffer[nBuffer];
  nBuffer += 1;
  return b[0]==0?0:1;
}

extern
void BeginToken(char *t) {
  nTokenStart = nTokenNextStart;
  nTokenLength = strlen(t);
  nTokenNextStart = nBuffer; // + 1;
  yylloc.first_line = nRow;
  yylloc.first_column = nTokenStart;
  yylloc.last_line = nRow;
  yylloc.last_column = nTokenStart + nTokenLength - 1;
}
