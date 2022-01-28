/**
    Arquivo de configuração para a linguagem c--
    
    Documentação utilizada para gerar arquivo:
        - https://ftp.gnu.org/old-gnu/Manuals/flex-2.5.4/html_mono/flex.html#SEC7
*/

/* Opções para o flex */
%option yylineno

/* Código c colocado no escopo global do programa */
%{
#include <stdlib.h> // exit, EXIT_FAILURE, atexit
#include <stdbool.h> // tipo bool
#include <assert.h> // assert macro
#include <math.h>

#include "headers/token_definitions.h"
#include "log_info/logging.h"
#include "utils/user_input.h"
#include "utils/utils.h"

char buffer[255];

uint8_t is_open_block = 0;
uint8_t is_open_expression = 0;

bool have_error;

void exitFunction(const char * filename);
%}
%x comment string_literal char_literal id

/* ---------- */
/* Definições */
/* ---------- */

/* Define quais caracteres representam digitos */
DIGIT [0-9]
/* Define quais caracteres representam letras maiusculas ou minusculas */
LETTER [A-Za-z]
/* Define uma regra que aceita qualquer Digito ou Letra */
ALPHA_NUM ({DIGIT}|{LETTER})

/* Definição dos caracteres que são considerados espaço em branco */
BLANK [ \t]
/* Definição do caractere que é considerados quebra de linha */
ENTER [\n]
/* Define uma regra que aceita qualquer um BLANK ou um ENTER */
BLANK_ENTER ({BLANK}|{ENTER})

/* ----------------- */
/* Classes de tokens */
/* ----------------- */
PREPROCESSOR_COMMAND "#"(.*)
KEYWORD "if"|"else"|"const"|"for"|"while"|"struct"
DATA_TYPE "int"|"float"|"double"|"char"
ASSIGNMENT "="|"+="|"-="|"*="|"/="|"%="|"<<="|">>="|"&="|"^="|"|="
ARITHMETIC_OPERATOR "+""+"?|"-""-"?|"/"|"*"|"sizeof"|"["{INTEGER_LITERAL}"]"
RELATIONAL_OPERATOR "&&"|"||"|"!"|("="|"!")"="|("<"|">")"="?
END_EXP ;
/* Definição do caractere que é considerado inicio de um escopo */
BLOCK_BEGIN "{"
/* Definição do caractere que é considerado fim de um escopo */
BLOCK_END "}"
/* Definição do caractere que é considerado inicio de uma expressão */
EXPRESSION_BEGIN "("
/* Definição do caractere que é considerado fim de uma expressão */
EXPRESSION_END ")"

/* valores constantes para expressões */
INTEGER_LITERAL {DIGIT}+
FLOAT_LITERAL {INTEGER_LITERAL}"."{INTEGER_LITERAL}
STRING_LITERAL_BEGIN \"
CHAR_LITERAL \'\\?.

/* aceita comentários em uma linha */
COMMENT_MULTILINE_BEGIN "/*"
COMMENT_SINGLE_LINE ("//".*)

ID_BEGIN ({LETTER})


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

{BLANK_ENTER}+ /* Elimina espaços em branco e \n */

{PREPROCESSOR_COMMAND} {
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

{ARITHMETIC_OPERATOR} {
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
    if (is_open_block) {
        doLog (
            LOG_TYPE_INFO,
            "Caractere de fim de escopo [}] encontrado"
        );
    }else {
        doLog (
            LOG_TYPE_ERROR,
            "Caractere de fim de expressão [}] encontrado, sem correspondente [{]"
        );
    }
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
    if (is_open_expression) {
        doLog (
            LOG_TYPE_INFO,
            "Caractere de fim de expressão [)] encontrado"
        );
    }else {
        doLog (
            LOG_TYPE_ERROR,
            "Caractere de fim de expressão [)] encontrado, sem correspondente [(]"
        );
    }
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

{CHAR_LITERAL} {
    _strncpy(buffer, yytext + 1, yyleng - 1);
    BEGIN(char_literal);
}
<char_literal>\' {
    doLog (
        LOG_TYPE_INFO,
        "Caractere [%s] encontrado",
        buffer
    );
    BEGIN(INITIAL);
}

<char_literal>. {
    doLog (
        LOG_TYPE_ERROR,
        "char literal mal formado [%s]",
        buffer
    );
    BEGIN(INITIAL);
    yyless(1); // devolve para o input o caractere lido
}

{STRING_LITERAL_BEGIN} BEGIN(string_literal);
<string_literal>\" {
    doLog (
        LOG_TYPE_INFO,
        "String literal [%s] encontrado",
        buffer
    );
    BEGIN(INITIAL);
}

<string_literal>{ENTER} {
    doLog (
        LOG_TYPE_ERROR,
        "String literal mal formada [%s]",
        buffer
    );
    BEGIN(INITIAL);
}

<string_literal>[^\\\n\"]+ {
    _strncpy(buffer, yytext, yyleng);
}

{ID_BEGIN} {
    buffer[0] = yytext[0];
    BEGIN(id);
    doLog (
        LOG_TYPE_INFO,
        "Identificador [%s] encontrado",
        yytext
    );
}

<id>({LETTER}|{DIGIT}|_)* {

}

 /* Qualquer caractere que não foi definido antes deve lançar um erro */
. {
    doLog (
        LOG_TYPE_ERROR,
        "Caractere [%c] não reconhecido pela linguagem,",
        yytext[0]
    );
}

%% /* separador para a terceira parte do arquivo */
/*
    Aqui temos mais definições C
    para serem colocadas no final do arquivo main.c
*/

void exitFunction(const char * filename) {
    if (is_open_block) {
        doLog(LOG_TYPE_ERROR, "Fim de arquivo antes de fechar o escopo {...");
    }
    if (is_open_expression > 0) {
        doLog(LOG_TYPE_ERROR, "Fim de arquivo antes de fechar a expressão (...");
    }
    printf (
        "%s ao executar a análise léxica no arquivo [%s]\nEncerrando o compilador\n",
        have_error? "Falha" : "Sucesso",
        filename
    );
}

int main(int argc,char** argv) {
    assert(0 < argc && argc < 3);

    char *filename;
    if (argc == 2) {
        filename = argv[1];
    }else {
        filename = getFilenameFromUser();
    }
#if USE_TERMINAL
    if (!strcmp(filename, "terminal")) {
        yyin = stdin;
    }else {
        yyin = fopen(filename, "r");
    }
#else
    yyin = fopen(filename, "r");
#endif

    yylex();
    exitFunction(filename);
    return (have_error? EXIT_FAILURE : EXIT_SUCCESS);
}