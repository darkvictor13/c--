/*
    Arquivo de configuraição para a linguagem c--
    Colocar mais info importante aqui
*/

/* Opcoes para o flex */
%option yylineno 

/* Código c colocado no escopo global do programa */
%{
#include <stdlib.h> // exit, EXIT_FAILURE, atexit
#include <math.h>
#include <assert.h>

#include "headers/token_definitions.h"
#include "log_info/logging.h"

void exitFunction(void);

%}

/* Definições*/
DIGIT       [0-9]
LETTER      [A-Za-z]
ALPHA_NUM   ({DIGIT}|{LETTER})

BLANK       [ \t]
BLANK_ENTER ({BLANK}|\n)

/* Classes de tokens */

KEYWORD     "long"|"short"|"if"|"else"|"const"|"for"|"while"|"struct"
DATA_TYPE   "int"|"float"|"double"|"char"
END_EXP     ;
ASSIGNMENT  =

/* valores constantes para expressões */
INTEGER_LITERAL {DIGIT}+
FLOAT_LITERAL {INTEGER_LITERAL}"."{INTEGER_LITERAL}
STRING_LITERAL \".*\"
CHAR_LITERAL "'"."'"

/* aceita comentários em uma ou mais linhas */
COMENT (("//".*)|("/*"("*/"|(.|"\n")*)))

ID ({LETTER})({LETTER}|{DIGIT}|_)*

/* Erros a serem identificados */
INVALID_STRING_LITERAL (\".*)
INVALID_CHAR_LITERAL   (\'.*)

%% // separador para a segunda parte do arquivo
 /* Nessa parte define-se as ações a serem tomadas
    quando encontrar uma expressão regular definida acima
 */

{KEYWORD} {
    doLog (
        LOG_TYPE_INFO,
        "Palavra reservada [%s]",
        yytext
    );
}

{DATA_TYPE} {
    doLog (
        LOG_TYPE_INFO,
        "Tipo de dado encontrado [%s]",
        yytext
    );
}

{ASSIGNMENT} {
    doLog (
        LOG_TYPE_INFO,
        "Caractere de atribuição [=] encontrado"
    );
}

{END_EXP} {
    doLog (
        LOG_TYPE_INFO,
        "Caractere de fim de expressão [;] encontrado"
    );
}

{INTEGER_LITERAL} {
    doLog (
        LOG_TYPE_INFO,
        "Valor inteiro [%s] encontrado",
        yytext
    );
}

{FLOAT_LITERAL} {
    doLog (
        LOG_TYPE_INFO,
        "Valor ponto flutuante [%s] encontrado",
        yytext
    );
}

{CHAR_LITERAL} {
    doLog (
        LOG_TYPE_INFO,
        "Caractere literal [%c] encontrado",
        yytext[1]
    );
}

{STRING_LITERAL} {
    doLog (
        LOG_TYPE_INFO,
        "String literal [%s] encontrado",
        yytext
    );
}

{COMENT} {
    doLog (
        LOG_TYPE_INFO,
        "Cometário [%s] encontrado",
        yytext
    );
}

{ID} {
    doLog (
        LOG_TYPE_INFO,
        "Identificador [%s] encontrado",
        yytext
    );
}

{BLANK}+ /* Elimina espaços em branco e \n */

 /* Erros */
{INVALID_STRING_LITERAL} {
    doLog (
        LOG_TYPE_ERROR,
        "Aspas duplas abertas mas não fechadas string [%s] inválida",
        yytext
    );
}

{INVALID_CHAR_LITERAL} {
    doLog (
        LOG_TYPE_ERROR,
        "Aspas simples abertas mas não fechadas string [%s] inválida",
        yytext
    );
}

. { /* Qualquer caractere que nao foi definido antes */
    doLog (
        LOG_TYPE_ERROR,
        "Caractere [%c] não reconhecido pela linguagem,",
        yytext[0]
    );
}

%%

void exitFunction(void) {
    printf("Programa encerrado\n");
}

int main(int argc,char** argv) {
    assert(0 < argc && argc < 3);
    atexit(exitFunction);

    if (argc == 2) {
        yyin = fopen(argv[1], "r");
    }else {
        yyin = stdin;
    }

    yylex();
    return EXIT_SUCCESS;
}
