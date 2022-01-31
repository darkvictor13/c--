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

#include "headers/token_definitions.h"
#include "log_info/logging.h"
#include "utils/user_input.h"
#include "utils/utils.h"

char buffer[256]; /// utilizado para armazenar temporariamente trechos de tokens

uint8_t is_open_block = 0; /// conta a quantidade de {}
uint8_t is_open_expression = 0; /// conta a quantidade de ()

bool have_error = false; /// guarda se houve algum erro durante a execução do processo

/**
 * @brief Últimas verificações léxicas após terminado o input de tokens
 *
 * @pre leitura de tokens encerrada
 * @post deixa a variável global have_error em seu estado final
 */
void lastVerify(const char * filename);
/**
 * @brief Função chamada ao encerrar o programa,
 * informando o usuário e realizando as limpezas necessárias
 *
 * Deve ser passada para função atexit
 * @pre leitura de tokens encerrada
 * @post deixa a variável global have_error em seu estado final
 */
void exitFunction(void);
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
KEYWORD "if"|"else"|"const"|"for"|"while"|"struct"
/* Token que aceita todos os tipos de dados da linguagem */
DATA_TYPE "int"|"float"|"double"|"char"
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
EXPRESSION_BEGIN "("
/* Token que aceita o caractere que é considerado fim de uma expressão */
EXPRESSION_END ")"

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

{ID} {
    doLog (
        LOG_TYPE_INFO,
        "Identificador [%s] encontrado",
        yytext
    );
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

void lastVerify(const char * filename) {
    if (is_open_block) {
        doLog(LOG_TYPE_ERROR, "Fim de arquivo antes de fechar o escopo {...");
    }
    if (is_open_expression > 0) {
        doLog(LOG_TYPE_ERROR, "Fim de arquivo antes de fechar a expressão (...");
    }
    printf (
        "\n%s ao executar a análise léxica no arquivo [%s]\n",
        have_error? "Falha" : "Sucesso",
        filename
    );
}

void exitFunction(void) {
    // não foi usado printf devido a possíveis falhas
	puts("Encerrando o compilador c--");
}

/// função main copiada para o main.c
int main(int argc, char * const argv[]) {
    // garante que o usuário passou 0 ou 1 argumentos
    assert(0 < argc && argc < 3);
    // configura função chamada ao sair do programa
    atexit(exitFunction);

    char *filename; /// caminho para o arquivo a ser analisado
    if (argc == 2) {
        filename = argv[1];
    }else {
        filename = getFilenameFromUser();
    }
    FILE *file_ptr = fopen(filename, "r");
	if (file_ptr == NULL) {
		printf("Falha ao abrir o arquivo de entrada\n");
		return EXIT_FAILURE;
	}
	yyin = file_ptr;

    yylex();
    lastVerify(filename);
    return (have_error? EXIT_FAILURE : EXIT_SUCCESS);
}