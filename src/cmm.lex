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
void exitFunction(void);
%}

/* Definições*/
DIGIT       [0-9]
LETTER      [A-Za-z]
ALPHA_NUM   ({DIGIT}|{LETTER})

BLANK       [ \t\n]
END_EXP     ;
ASSIGNMENT  =

/* Classes de tokens */
ID       ({LETTER})({LETTER}|{DIGIT}|_)*

/* valores constantes para expressões */
INTEGER_LITERAL  {DIGIT}+
FLOAT_LITERAL    {INTEGER_LITERAL}"."{INTEGER_LITERAL}
STRING_LITERAL   """.*"""
CHAR_LITERAL     "'"."'"

COMENT   "//".*"\n"


%% // separador para a segunda parte do arquivo
 /* Nessa parte define-se as ações a serem tomadas
    quando encontrar uma expressão regular definida acima
 */

{INTEGER_LITERAL} {
    printf("An integer: %s (%d)\n", yytext, atoi(yytext));
}

{FLOAT_LITERAL} {
    printf("A float: %s (%g)\n", yytext, atof(yytext));
}

{CHAR_LITERAL} {
    printf("CHAR = %c\n", yytext[1]);
}

{STRING_LITERAL} {
    printf("string lida = %s\n", yytext);
}

{ASSIGNMENT} {
	TokenType t = TOKEN_ASSIGNMENT;
    printf("TODO\n");
}

{END_EXP} {
    printf("TODO EXP\n");
}

{COMENT} {
    char buffer[yyleng-3];

    int index_remover_inicio = 2;
    while ( yytext[index_remover_inicio] == ' ' ||
            yytext[index_remover_inicio] == '\t') {
    
        index_remover_inicio++;
    }

    const int buffer_len = yyleng - index_remover_inicio;

    strncpy(buffer, yytext + index_remover_inicio, buffer_len);
    buffer[buffer_len-1] = 0;
    printf("Comentário = %s\n", buffer);
}

{ID} {
    printf("An identifier: %s\n", yytext);
}

"+"|"-"|"*"|"/" {
    printf("An operator: %s\n", yytext);
}

{BLANK}+ /* Elimina espaços em branco e \n */

. { /* Qualquer caractere que nao foi definido antes */
    printf("ERRO: caractere inválido [%c] na linha [%d]\n",
            yytext[0], yylineno);
    exit(EXIT_FAILURE);
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
