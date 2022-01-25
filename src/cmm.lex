/*
    Arquivo de configuraição para a linguagem c--
    Colocar mais info importante aqui
*/

/* Opcoes para o flex */
%option yylineno 

/* Código c colocado no escopo global do programa */
%{
#include <stdlib.h> // exit, EXIT_FAILURE, atexit
#include <stdbool.h> // tipo bool
#include <assert.h> // assert macro
#include <math.h>

#include "headers/token_definitions.h"
#include "log_info/logging.h"

uint8_t is_open_block = 0;
uint8_t is_open_expression = 0;
char buffer[255];
char *buffer_ptr;

void exitFunction(void);
%}
%x comment string_literal char_literal

/* Definições*/
DIGIT [0-9]
LETTER [A-Za-z]
ALPHA_NUM ({DIGIT}|{LETTER})

BLANK [ \t]
ENTER [\n]
BLANK_ENTER ({BLANK}|{ENTER})
BLOCK_BEGIN "{"
BLOCK_END "}"
EXPRESSION_BEGIN "("
EXPRESSION_END ")"

/* Classes de tokens */

PREPROCESSOR_COMAND "#"(.*)
KEYWORD "if"|"else"|"const"|"for"|"while"|"struct"
DATA_TYPE "int"|"float"|"double"|"char"
ARITMETIC_OPERATOR "+""+"?|"-""-"?|"/"|"*"|"sizeof"|"["{INTEGER_LITERAL}"]"
RELATIONAL_OPERATOR "&&"|"||"|"!"|("="|"!")"="|("<"|">")"="?
END_EXP ;
ASSIGNMENT "="|"+="|"-="|"*="|"/="|"%="|"<<="|">>="|"&="|"^="|"|="

/* valores constantes para expressões */
INTEGER_LITERAL {DIGIT}+
FLOAT_LITERAL {INTEGER_LITERAL}"."{INTEGER_LITERAL}
STRING_LITERAL_BEGIN \"
CHAR_LITERAL_BEGIN \'

/* aceita comentários em uma linha */
COMENT ("//"|"/*")

ID ({LETTER})({LETTER}|{DIGIT}|_)*

%% // separador para a segunda parte do arquivo
 /* Nessa parte define-se as ações a serem tomadas
    quando encontrar uma expressão regular definida acima
 */

{COMENT} BEGIN(comment);
<comment>[^*\n]*
<comment>"*"+[^*/\n]*
<comment>{BLANK_ENTER}+
<comment>"*"+"/" BEGIN(INITIAL);

{BLANK_ENTER}+ /* Elimina espaços em branco e \n */

{PREPROCESSOR_COMAND} {
    doLog (
        LOG_TYPE_INFO,
        "Comando para o preprocessador [%s]",
        yytext
    );
}

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
        "Expressão de atribuição [%s] encontrada",
        yytext
    );
}

{ARITMETIC_OPERATOR} {
    doLog (
        LOG_TYPE_INFO,
        "Operador aritmético [%s] encontrado",
        yytext
    );
}

{RELATIONAL_OPERATOR} {
    doLog (
        LOG_TYPE_INFO,
        "Operador relacional [%s] encontrado",
        yytext
    );
}

{END_EXP} {
    doLog (
        LOG_TYPE_INFO,
        "Caractere de fim de expressão [;] encontrado"
    );
}

{BLOCK_BEGIN} {
    doLog (
        LOG_TYPE_INFO,
        "Caractere de início de escopo [{] encontrado"
    );
    is_open_block++;
}

{BLOCK_END} {
    doLog (
        LOG_TYPE_INFO,
        "Caractere de fim de escopo [}] encontrado"
    );
    is_open_block--;
}

{EXPRESSION_BEGIN} {
    doLog (
        LOG_TYPE_INFO,
        "Caractere de início de expressão [(] encontrado"
    );
    is_open_expression++;
}

{EXPRESSION_END} {
    doLog (
        LOG_TYPE_INFO,
        "Caractere de fim de expressão [)] encontrado"
    );
    is_open_expression--;
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

{CHAR_LITERAL_BEGIN} BEGIN(char_literal);
<char_literal>.\' {
    doLog (
        LOG_TYPE_INFO,
        "Caractere [%s] encontrado",
        yytext[0]
    );
    BEGIN(INITIAL);
}
<char_literal>\\.\' {
    char temp[2];
    strncpy(yytext, temp, 2);
    doLog (
        LOG_TYPE_INFO,
        "Caractere [%s] encontrado",
        temp
    );
    BEGIN(INITIAL);
}

{STRING_LITERAL_BEGIN} BEGIN(string_literal);

{ID} {
    doLog (
        LOG_TYPE_INFO,
        "Identificador [%s] encontrado",
        yytext
    );
}

 /* Erros */
. { /* Qualquer caractere que nao foi definido antes */
    doLog (
        LOG_TYPE_ERROR,
        "Caractere [%c] não reconhecido pela linguagem,",
        yytext[0]
    );
}

%%

void exitFunction(void) {
    if (is_open_block > 0) {
        doLog(LOG_TYPE_ERROR, "Fim de arquivo antes de fechar o escopo {...");
    }
    if (is_open_expression > 0) {
        doLog(LOG_TYPE_ERROR, "Fim de arquivo antes de fechar a expressão (...");
    }
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
