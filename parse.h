/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSE_H_INCLUDED
# define YY_YY_PARSE_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CASESYM = 258,
    FORSYM = 259,
    SWITCHSYM = 260,
    BREAKSYM = 261,
    CONTINUESYM = 262,
    EXITSYM = 263,
    DOSYM = 264,
    REPEATSYM = 265,
    UNTILSYM = 266,
    IFSYM = 267,
    THENSYM = 268,
    WHILESYM = 269,
    WRITESYM = 270,
    READSYM = 271,
    RETURNSYM = 272,
    ENDSYM = 273,
    INTSYM = 274,
    FLOATSYM = 275,
    BOOLSYM = 276,
    CHARSYM = 277,
    CONSTSYM = 278,
    FUNCSYM = 279,
    SEMICOLON = 280,
    COLON = 281,
    LPAREN = 282,
    RPAREN = 283,
    LBPAREN = 284,
    RBPAREN = 285,
    LMPAREN = 286,
    RMPAREN = 287,
    COMMENT = 288,
    COMMA = 289,
    INC = 290,
    DEC = 291,
    ODD = 292,
    MOD = 293,
    PLUS = 294,
    MINUS = 295,
    SLASH = 296,
    TIMES = 297,
    LES = 298,
    LEQ = 299,
    GTR = 300,
    GEQ = 301,
    EQL = 302,
    NEQ = 303,
    BECOME = 304,
    XOR = 305,
    OR = 306,
    AND = 307,
    NOT = 308,
    IDENT = 309,
    NUMBER = 310,
    LETTER = 311,
    IFX = 312,
    ELSESYM = 313,
    BOOLVALUE = 314
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 66 "parse.y" /* yacc.c:1909  */

  char *ident;
  char letter;
  int  number;

#line 120 "parse.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_PARSE_H_INCLUDED  */
