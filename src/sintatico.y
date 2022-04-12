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
#include "tree/tree.h"

#include "log_info/logging.h"
#include "utils/user_input.h"
#include "utils/utils.h"

#define LOGI(...) cmmLog (LOG_TYPE_INFO, SINTATIC_ANALYSIS, __VA_ARGS__)
#define LOGE(...) cmmLog (LOG_TYPE_ERROR, SINTATIC_ANALYSIS, __VA_ARGS__)
#define MAX_SIZE 1000

extern FILE *yyin;
extern int yylex();
extern char* yytext;
extern int yyleng;

char buffer[256]; /// utilizado para armazenar temporariamente trechos de tokens

int num_tabs = 0;

treeNode sintax_tree[MAX_SIZE];
int sintax_tree_size = 0;

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

add_tab: {num_tabs++;};

rm_tab: {num_tabs--;};

programa_token: {ADD("programa");};
definition_token: {ADD("definition");};
variable_token: {ADD("variable");};
function_token: {ADD("function");};
assignment_token: {ADD("assignment");};
data_type_token: {ADD("data type");};
literal_token: {ADD("literal");};
if_token: {ADD("if");};
else_token: {ADD("else");};
for_token: {ADD("for");};
while_token: {ADD("while");};

programa:
    | programa_token add_tab TOKEN_PREPROCESSOR_COMMAND rm_tab programa
    | programa_token add_tab definition rm_tab programa
    ;

data_type:
    data_type_token add_tab TOKEN_DATA_TYPE_INT rm_tab
    | data_type_token add_tab TOKEN_DATA_TYPE_FLOAT rm_tab
    | data_type_token add_tab TOKEN_DATA_TYPE_CHAR rm_tab
    | data_type_token add_tab TOKEN_KEYWORD_CONST TOKEN_DATA_TYPE_INT rm_tab
    | data_type_token add_tab TOKEN_KEYWORD_CONST TOKEN_DATA_TYPE_FLOAT rm_tab
    | data_type_token add_tab TOKEN_KEYWORD_CONST TOKEN_DATA_TYPE_CHAR rm_tab
    | data_type_token add_tab TOKEN_DATA_TYPE_VOID rm_tab
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
    literal_token add_tab TOKEN_INTEGER_LITERAL rm_tab
    | literal_token add_tab TOKEN_FLOAT_LITERAL rm_tab
    | literal_token add_tab TOKEN_CHAR_LITERAL rm_tab
    | literal_token add_tab TOKEN_STRING_LITERAL rm_tab
    ;

definition: definition_token add_tab data_type TOKEN_ID definition_variable_function rm_tab
    ;

definition_variable_function:
    variable_token add_tab variable rm_tab
    | function_token add_tab function rm_tab
    ;

complete_variable:
    data_type TOKEN_ID variable
    ;

variable:
    add_tab assignment_token TOKEN_ASSIGNMENT literal TOKEN_END_EXP rm_tab
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
    for_token add_tab TOKEN_KEYWORD_FOR TOKEN_PARENTESEIS_BEGIN atribuition TOKEN_END_EXP conditional TOKEN_END_EXP math_expression TOKEN_PARENTESEIS_END TOKEN_BLOCK_BEGIN exp TOKEN_BLOCK_END rm_tab
    | for_token add_tab TOKEN_KEYWORD_FOR TOKEN_PARENTESEIS_BEGIN complete_variable TOKEN_END_EXP conditional TOKEN_END_EXP math_expression TOKEN_PARENTESEIS_END TOKEN_BLOCK_BEGIN exp TOKEN_BLOCK_END rm_tab
    | error segure_token
    ;

while:
    while_token add_tab TOKEN_KEYWORD_WHILE TOKEN_PARENTESEIS_BEGIN conditional TOKEN_PARENTESEIS_END TOKEN_BLOCK_BEGIN exp TOKEN_BLOCK_END rm_tab
    | error segure_token
    ;

atribuition:
    assignment_token add_tab TOKEN_ID TOKEN_ASSIGNMENT math_expression TOKEN_END_EXP rm_tab
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
    if_token add_tab TOKEN_KEYWORD_IF TOKEN_PARENTESEIS_BEGIN conditional TOKEN_PARENTESEIS_END TOKEN_BLOCK_BEGIN exp TOKEN_BLOCK_END rm_tab
    | if_token add_tab TOKEN_KEYWORD_IF TOKEN_PARENTESEIS_BEGIN conditional TOKEN_PARENTESEIS_END TOKEN_BLOCK_BEGIN exp TOKEN_BLOCK_END rm_tab else_token add_tab TOKEN_KEYWORD_ELSE TOKEN_BLOCK_BEGIN exp TOKEN_BLOCK_END rm_tab
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
    if (!have_error) {
        const char prefix[] = "arvores_";
        const int size = strlen(prefix) + strlen(filename);
        char out_file_name[size + 1];
        strcpy(out_file_name, prefix);
        strcat(out_file_name, filename);
        FILE *file = fopen(out_file_name, "w");
        if (!fopen) {
            printf("Falha ao abrir arquivo %s\n", out_file_name);
            exit(EXIT_FAILURE);
        }
        print(file, sintax_tree, sintax_tree_size);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}
