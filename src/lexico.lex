/**
  Arquivo de definição da linguagem C--, Um subconjunto da linguagem C

  Escrito em lex/flex esse arquivo tem como objetivo definir
  os tokens da linguagem, bem como as ações tomadas quando os mesmos são
  encontrados em um arquivo fonte. Sendo assim realizando a análise léxica.

  Documentação utilizada para gerar arquivo:
  - https://ftp.gnu.org/old-gnu/Manuals/flex-2.5.4/html_mono/flex.html
*/

/* Opções para o flex */
/* Armazena em yylineno qual linha do arquivo está sendo lida */
%option yylineno

/* Código c colocado no escopo global do programa */
%{
    #include <stdlib.h> // exit, EXIT_FAILURE
    #include <stdbool.h> // tipo bool
    #include <assert.h> // assert macro
    #include <errno.h>

    #include "sintatico.tab.h"

    #include "log_info/logging.h"
    #include "utils/user_input.h"
    #include "utils/utils.h"
    #include "tree/tree.h"

    extern char buffer[256];

    extern uint8_t is_open_block;
    extern uint8_t is_open_expression;
    extern bool have_error;
    extern treeNode sintax_tree[1000];
    extern int sintax_tree_size;
    extern int num_tabs;

    //#define LOGI(...) add(sintax_tree + sintax_tree_size, yytext, num_tabs); sintax_tree_size++; cmmLog (LOG_TYPE_INFO, LEXICAL_ANALYSIS, __VA_ARGS__)
    //#define LOGE(...) add(sintax_tree + sintax_tree_size, yytext, num_tabs); sintax_tree_size++; cmmLog (LOG_TYPE_ERROR, LEXICAL_ANALYSIS, __VA_ARGS__)
    #define LOGI(...) cmmLog (LOG_TYPE_INFO, LEXICAL_ANALYSIS, __VA_ARGS__)
    #define LOGE(...) cmmLog (LOG_TYPE_ERROR, LEXICAL_ANALYSIS, __VA_ARGS__)
%}

%x comment string_literal char_literal

/* ---------- */
/* Definições */
/* ---------- */

/* Define quais caracteres representam dígitos */
DIGIT [0-9]
/* Define quais caracteres representam letras maiúsculas ou minusculas */
LETTER [A-Za-z]
/* Define uma regra que aceita qualquer Digito ou Letra */
ALPHA_NUM ({DIGIT}|{LETTER})

/* Definição dos caracteres que são considerados espaço em branco */
BLANK [ \t]
/* Definição do caractere que é considerados quebra de linha */
ENTER [\n]
/* Define uma regra que aceita qualquer um BLANK ou um ENTER */
BLANK_ENTER ({BLANK}|{ENTER})
/* Define o início de um comentário de múltiplas linhas, utilizado em Start conditions */
COMMENT_MULTILINE_BEGIN "/*"
/* aceita comentários em uma linha */
COMMENT_SINGLE_LINE ("//".*)

/* ----------------- */
/* Classes de tokens */
/* ----------------- */
/* Token que aceita comandos para o preprocessador */
PREPROCESSOR_COMMAND "#"(.*)
/* Token que aceita todas as palavras chave reconhecidas pela linguagem */
KEYWORD_IF "if"
KEYWORD_ELSE "else"
KEYWORD_FOR "for"
KEYWORD_WHILE "while"
KEYWORD_RETURN "return"
KEYWORD_STRUCT "struct"
KEYWORD_CONST "const"
/* Token que aceita todos os tipos de dados da linguagem */
DATA_TYPE_INT "u"?"int"(("8"|"16"|"32"|"64")"_t")?
DATA_TYPE_FLOAT "float"|"double"
DATA_TYPE_CHAR "char"
DATA_TYPE_VOID "void"
/* Token que aceita símbolos de atribuição */
/* ASSIGNMENT "="|"+="|"-="|"*="|"/="|"%="|"<<="|">>="|"&="|"^="|"|=" */
ASSIGNMENT ("+"|"-"|"*"|"/"|"%"|"<<"|">>"|"&"|"|"|"^")?"="
/* Token que aceita os operadores aritméticos */
ARITHMETIC_OPERATOR "+""+"?|"-""-"?|"/"|"*"|"sizeof"|"["{INTEGER_LITERAL}"]"
/* Token que aceita os operadores relacionais */
RELATIONAL_OPERATOR "&&"|"||"|"!"|("="|"!")"="|("<"|">")"="?
/* Token que aceita o caractere de fim de expressão */
END_EXP ;
/* Token que aceita o caractere que é considerado inicio de um escopo */
BLOCK_BEGIN "{"
/* Token que aceita o caractere que é considerado fim de um escopo */
BLOCK_END "}"
/* Token que aceita o caractere que é considerado inicio de uma expressão */
PARENTESEIS_BEGIN "("
/* Token que aceita o caractere que é considerado fim de uma expressão */
PARENTESEIS_END ")"

/* valores constantes para expressões */
/* Token que aceita valores inteiros literais */
INTEGER_LITERAL {DIGIT}+
/* Token que aceita valores reais literais */
FLOAT_LITERAL {INTEGER_LITERAL}"."{INTEGER_LITERAL}
/* Token que aceita strings literais, utilizado em Start conditions*/
STRING_LITERAL_BEGIN \"
/* Token que aceita valores de caracteres literais, utilizado em Start conditions*/
CHAR_LITERAL \'\\?.

/* Token que aceita identificadores da linguagem (nomes de funções, variáveis) */
ID ({LETTER})({ALPHA_NUM}|_)*

%% /* separador para a segunda parte do arquivo */
 /*
    Nessa parte define-se as ações a serem tomadas
    quando encontrar uma das classes de tokens previamente
    definidas
 */

 /* Elimina comentários de múltiplas linhas */
{COMMENT_MULTILINE_BEGIN} BEGIN(comment);
<comment>[^("*"|"\")]*
<comment>"*"+[^*/\n]*
<comment>"\n"
<comment>"*"+"/" BEGIN(INITIAL);

{COMMENT_SINGLE_LINE} /* elimina resto da linha do cometário */

{BLANK_ENTER}+

{PREPROCESSOR_COMMAND} {
    LOGI (
        "Comando para o preprocessador [%s]",
        yytext
    );
	return TOKEN_PREPROCESSOR_COMMAND;
}

{KEYWORD_IF} {
    LOGI (
        "Palavra reservada [%s]",
        yytext
    );
	return TOKEN_KEYWORD_IF;
}

{KEYWORD_ELSE} {
    LOGI (
        "Palavra reservada [%s]",
        yytext
    );
	return TOKEN_KEYWORD_ELSE;
}

{KEYWORD_CONST} {
    LOGI (
        "Palavra reservada [%s]",
        yytext
    );
	return TOKEN_KEYWORD_CONST;
}

{KEYWORD_RETURN} {
    LOGI (
        "Palavra reservada [%s]",
        yytext
    );
	return TOKEN_KEYWORD_RETURN;
}

{KEYWORD_STRUCT} {
    LOGI (
        "Palavra reservada [%s]",
        yytext
    );
	return TOKEN_KEYWORD_STRUCT;
}

{KEYWORD_FOR} {
    LOGI (
        "Palavra reservada [%s]",
        yytext
    );
	return TOKEN_KEYWORD_FOR;
}

{KEYWORD_WHILE} {
    LOGI (
        "Palavra reservada [%s]",
        yytext
    );
	return TOKEN_KEYWORD_WHILE;
}

{DATA_TYPE_INT} {
    LOGI (
        "Tipo de dado inteiro encontrado [%s]",
        yytext
    );
	return TOKEN_DATA_TYPE_INT;
}

{DATA_TYPE_FLOAT} {
    LOGI (
        "Tipo de dado ponto flutuante encontrado [%s]",
        yytext
    );
	return TOKEN_DATA_TYPE_FLOAT;
}

{DATA_TYPE_CHAR} {
    LOGI (
        "Tipo de caractere encontrado [%s]",
        yytext
    );
	return TOKEN_DATA_TYPE_CHAR;
}

{DATA_TYPE_VOID} {
    LOGI (
        "Tipo de caractere encontrado [%s]",
        yytext
    );
	return TOKEN_DATA_TYPE_VOID;
}

{ASSIGNMENT} {
    LOGI (
        "Expressão de atribuição [%s] encontrada",
        yytext
    );
	return TOKEN_ASSIGNMENT;
}

{ARITHMETIC_OPERATOR} {
    LOGI (
        "Operador aritmético [%s] encontrado",
        yytext
    );
	return TOKEN_ARITHMETIC_OPERATOR;
}

{RELATIONAL_OPERATOR} {
    LOGI (
        "Operador relacional [%s] encontrado",
        yytext
    );
	return TOKEN_RELATIONAL_OPERATOR;
}

{END_EXP} {
    LOGI (
        "Caractere de fim de expressão [;] encontrado"
    );
	return TOKEN_END_EXP;
}

{BLOCK_BEGIN} {
    LOGI (
        "Caractere de início de escopo [{] encontrado"
    );
    is_open_block++;
    return TOKEN_BLOCK_BEGIN;
}

{BLOCK_END} {
    if (is_open_block) {
        LOGI (
            "Caractere de fim de escopo [}] encontrado"
        );
    }else {
        LOGE (
            "Caractere de fim de expressão [}] encontrado, sem correspondente [{]"
        );
    }
    is_open_block--;
	return TOKEN_BLOCK_END;
}

{PARENTESEIS_BEGIN} {
    LOGI (
        "Caractere de início de expressão [(] encontrado"
    );
    is_open_expression++;
	return TOKEN_PARENTESEIS_BEGIN;
}

{PARENTESEIS_END} {
    if (is_open_expression) {
        LOGI (
            "Caractere de fim de expressão [)] encontrado"
        );
    }else {
        LOGE (
            "Caractere de fim de expressão [)] encontrado, sem correspondente [(]"
        );
    }
    is_open_expression--;
	return TOKEN_PARENTESEIS_END;
}

{INTEGER_LITERAL} {
    LOGI (
        "Valor inteiro [%s] encontrado",
        yytext
    );
	return TOKEN_INTEGER_LITERAL;
}

{FLOAT_LITERAL} {
    LOGI (
        "Valor ponto flutuante [%s] encontrado",
        yytext
    );
	return TOKEN_FLOAT_LITERAL;
}

{CHAR_LITERAL} {
    _strncpy(buffer, yytext + 1, yyleng - 1);
    BEGIN(char_literal);
}
<char_literal>\' {
    LOGI (
        "Caractere [%s] encontrado",
        buffer
    );
    BEGIN(INITIAL);
	return TOKEN_CHAR_LITERAL;
}

<char_literal>. {
    LOGE (
        "char literal mal formado [%s]",
        buffer
    );
    BEGIN(INITIAL);
    yyless(1); // devolve para o input o caractere lido
}

{STRING_LITERAL_BEGIN} BEGIN(string_literal);
<string_literal>\" {
    LOGI (
        "String literal [%s] encontrado",
        buffer
    );
    BEGIN(INITIAL);
	return TOKEN_STRING_LITERAL;
}

<string_literal>{ENTER} {
    LOGE (
        "String literal mal formada [%s]",
        buffer
    );
    BEGIN(INITIAL);
}

<string_literal>[^\\\n\"]+ {
    _strncpy(buffer, yytext, yyleng);
}

{ID} {
    LOGI (
        "Identificador [%s] encontrado",
        yytext
    );
	return TOKEN_ID;
}

 /* Qualquer caractere que não foi definido antes deve lançar um erro */
. {
    LOGE (
        "Caractere [%c] não reconhecido pela linguagem,",
        yytext[0]
    );
}

%% /* separador para a terceira parte do arquivo */
/*
    Aqui temos mais definições C
    para serem colocadas no final do arquivo main.c
*/
