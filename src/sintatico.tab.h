/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SRC_SINTATICO_TAB_H_INCLUDED
# define YY_YY_SRC_SINTATICO_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOKEN_PREPROCESSOR_COMMAND = 258, /* TOKEN_PREPROCESSOR_COMMAND  */
    TOKEN_KEYWORD_IF = 259,        /* TOKEN_KEYWORD_IF  */
    TOKEN_KEYWORD_ELSE = 260,      /* TOKEN_KEYWORD_ELSE  */
    TOKEN_KEYWORD_FOR = 261,       /* TOKEN_KEYWORD_FOR  */
    TOKEN_COMMA = 262,             /* TOKEN_COMMA  */
    TOKEN_KEYWORD_WHILE = 263,     /* TOKEN_KEYWORD_WHILE  */
    TOKEN_KEYWORD_RETURN = 264,    /* TOKEN_KEYWORD_RETURN  */
    TOKEN_KEYWORD_STRUCT = 265,    /* TOKEN_KEYWORD_STRUCT  */
    TOKEN_KEYWORD_CONST = 266,     /* TOKEN_KEYWORD_CONST  */
    TOKEN_DATA_TYPE_INT = 267,     /* TOKEN_DATA_TYPE_INT  */
    TOKEN_DATA_TYPE_FLOAT = 268,   /* TOKEN_DATA_TYPE_FLOAT  */
    TOKEN_DATA_TYPE_CHAR = 269,    /* TOKEN_DATA_TYPE_CHAR  */
    TOKEN_DATA_TYPE_VOID = 270,    /* TOKEN_DATA_TYPE_VOID  */
    TOKEN_ASSIGNMENT = 271,        /* TOKEN_ASSIGNMENT  */
    TOKEN_ARITHMETIC_OPERATOR = 272, /* TOKEN_ARITHMETIC_OPERATOR  */
    TOKEN_RELATIONAL_OPERATOR = 273, /* TOKEN_RELATIONAL_OPERATOR  */
    TOKEN_END_EXP = 274,           /* TOKEN_END_EXP  */
    TOKEN_BLOCK_BEGIN = 275,       /* TOKEN_BLOCK_BEGIN  */
    TOKEN_BLOCK_END = 276,         /* TOKEN_BLOCK_END  */
    TOKEN_PARENTESEIS_BEGIN = 277, /* TOKEN_PARENTESEIS_BEGIN  */
    TOKEN_PARENTESEIS_END = 278,   /* TOKEN_PARENTESEIS_END  */
    TOKEN_INTEGER_LITERAL = 279,   /* TOKEN_INTEGER_LITERAL  */
    TOKEN_FLOAT_LITERAL = 280,     /* TOKEN_FLOAT_LITERAL  */
    TOKEN_STRING_LITERAL = 281,    /* TOKEN_STRING_LITERAL  */
    TOKEN_CHAR_LITERAL = 282,      /* TOKEN_CHAR_LITERAL  */
    TOKEN_ID = 283                 /* TOKEN_ID  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_SRC_SINTATICO_TAB_H_INCLUDED  */
