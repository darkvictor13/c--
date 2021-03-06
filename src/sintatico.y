/*
    Analisador sintático da linguagem C--
*/
%{
#include <stdio.h>
#include <stdlib.h> // exit, EXIT_FAILURE
#include <stdbool.h> // tipo bool
#include <assert.h> // assert macro
#include <errno.h>
#include <string.h>

#include "log_info/logging.h"
#include "utils/user_input.h"
#include "utils/utils.h"

#define LOGI(...) cmmLog (LOG_TYPE_INFO, SINTATIC_ANALYSIS, __VA_ARGS__)
#define LOGE(...) cmmLog (LOG_TYPE_ERROR, SINTATIC_ANALYSIS, __VA_ARGS__)

extern FILE *yyin;
extern int yylex();
extern char* yytext;
extern int yyleng;

char buffer[256]; /// utilizado para armazenar temporariamente trechos de tokens

uint8_t is_open_block = 0; /// conta a quantidade de {}
uint8_t is_open_expression = 0; /// conta a quantidade de ()

bool have_error = false; /// guarda se houve algum erro durante a execução do processo

void yyerror(const char *s);

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

#define ADD(TEXT) add(sintax_tree + sintax_tree_size, TEXT, num_tabs); sintax_tree_size++;
%}

%token TOKEN_PREPROCESSOR_COMMAND
%token TOKEN_KEYWORD_IF
%token TOKEN_KEYWORD_ELSE
%token TOKEN_KEYWORD_FOR
%token TOKEN_KEYWORD_WHILE
%token TOKEN_KEYWORD_RETURN
%token TOKEN_KEYWORD_STRUCT
%token TOKEN_KEYWORD_CONST
%token TOKEN_DATA_TYPE_INT
%token TOKEN_DATA_TYPE_FLOAT
%token TOKEN_DATA_TYPE_CHAR
%token TOKEN_DATA_TYPE_VOID
%token TOKEN_ASSIGNMENT
%token TOKEN_ARITHMETIC_OPERATOR
%token TOKEN_RELATIONAL_OPERATOR
%token TOKEN_END_EXP
%token TOKEN_BLOCK_BEGIN
%token TOKEN_BLOCK_END
%token TOKEN_PARENTESEIS_BEGIN
%token TOKEN_PARENTESEIS_END
%token TOKEN_INTEGER_LITERAL
%token TOKEN_FLOAT_LITERAL
%token TOKEN_STRING_LITERAL
%token TOKEN_CHAR_LITERAL
%token TOKEN_ID

/// Símbolo inicial da gramática
%start programa

%%

programa:
    | TOKEN_PREPROCESSOR_COMMAND programa
    | definition programa
    ;

data_type:
    TOKEN_DATA_TYPE_INT
    | TOKEN_DATA_TYPE_FLOAT
    | TOKEN_DATA_TYPE_CHAR
    | TOKEN_KEYWORD_CONST TOKEN_DATA_TYPE_INT
    | TOKEN_KEYWORD_CONST TOKEN_DATA_TYPE_FLOAT
    | TOKEN_KEYWORD_CONST TOKEN_DATA_TYPE_CHAR
    | TOKEN_DATA_TYPE_VOID
    ;

keyword:
	TOKEN_KEYWORD_IF
	| TOKEN_KEYWORD_ELSE
	| TOKEN_KEYWORD_CONST
	| TOKEN_KEYWORD_FOR
	| TOKEN_KEYWORD_WHILE
	| TOKEN_KEYWORD_RETURN
	| TOKEN_KEYWORD_STRUCT
	;

segure_token:
    keyword
    | data_type
    | TOKEN_END_EXP
    ;

literal:
    TOKEN_INTEGER_LITERAL
    | TOKEN_FLOAT_LITERAL
    | TOKEN_CHAR_LITERAL
    | TOKEN_STRING_LITERAL
    ;

definition: data_type TOKEN_ID definition_variable_function
    ;

definition_variable_function:
    variable
    | function
    ;

complete_variable:
    data_type TOKEN_ID variable
    ;

variable:
    TOKEN_ASSIGNMENT literal TOKEN_END_EXP
    | TOKEN_ARITHMETIC_OPERATOR TOKEN_END_EXP
    | TOKEN_END_EXP
    ;

function:
    TOKEN_PARENTESEIS_BEGIN TOKEN_PARENTESEIS_END TOKEN_END_EXP 
    | TOKEN_PARENTESEIS_BEGIN TOKEN_PARENTESEIS_END TOKEN_BLOCK_BEGIN exp TOKEN_BLOCK_END 
    | error segure_token
    ;

exp:
    | complete_variable exp
    | atribuition exp
    | ifel exp
    | for exp
    | while exp
    //| return
    ;

for:
    TOKEN_KEYWORD_FOR TOKEN_PARENTESEIS_BEGIN atribuition TOKEN_END_EXP conditional TOKEN_END_EXP math_expression TOKEN_PARENTESEIS_END TOKEN_BLOCK_BEGIN exp TOKEN_BLOCK_END
    | TOKEN_KEYWORD_FOR TOKEN_PARENTESEIS_BEGIN complete_variable TOKEN_END_EXP conditional TOKEN_END_EXP math_expression TOKEN_PARENTESEIS_END TOKEN_BLOCK_BEGIN exp TOKEN_BLOCK_END
    | error segure_token
    ;

while:
    TOKEN_KEYWORD_WHILE TOKEN_PARENTESEIS_BEGIN conditional TOKEN_PARENTESEIS_END TOKEN_BLOCK_BEGIN exp TOKEN_BLOCK_END
    | error segure_token
    ;

atribuition:
    TOKEN_ID TOKEN_ASSIGNMENT math_expression TOKEN_END_EXP
    ;

value:
    TOKEN_ID
    | TOKEN_INTEGER_LITERAL
    | TOKEN_FLOAT_LITERAL
    ;

math_expression:
    | value
    | TOKEN_PARENTESEIS_BEGIN math_expression TOKEN_PARENTESEIS_END math_expression
    | math_expression TOKEN_ARITHMETIC_OPERATOR math_expression
    ;

ifel:
    TOKEN_KEYWORD_IF TOKEN_PARENTESEIS_BEGIN conditional TOKEN_PARENTESEIS_END TOKEN_BLOCK_BEGIN exp TOKEN_BLOCK_END
    | TOKEN_KEYWORD_IF TOKEN_PARENTESEIS_BEGIN conditional TOKEN_PARENTESEIS_END TOKEN_BLOCK_BEGIN exp TOKEN_BLOCK_END TOKEN_KEYWORD_ELSE TOKEN_BLOCK_BEGIN exp TOKEN_BLOCK_END
    | error segure_token
    ;

conditional:
    value
    | value TOKEN_RELATIONAL_OPERATOR value
    ;

%%
void yyerror(const char *s) {
    LOGE("Token [%s] inesperado", yytext);
}

void lastVerify(const char * filename) {
    if (is_open_block) {
        LOGE("Fim do programa antes de fechar o escopo {...");
    }
    if (is_open_expression > 0) {
        LOGE("Fim do programa antes de fechar a expressão (...");
    }
    printf (
        "\n%s ao compilar o arquivo [%s]\n",
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

    yyparse();
    lastVerify(filename);
    return have_error? EXIT_FAILURE : EXIT_SUCCESS;
}
