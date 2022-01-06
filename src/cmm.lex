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

/* Classes de tokens */
/*["if"|else|const|for|while|struct]*/
KEYWORD     [if]
DATA_TYPE   (int|long|short|float|double|char)
END_EXP     ;
ASSIGNMENT  =

/* valores constantes para expressões */
INTEGER_LITERAL {DIGIT}+
FLOAT_LITERAL {INTEGER_LITERAL}"."{INTEGER_LITERAL}
STRING_LITERAL \".*\"
CHAR_LITERAL "'"."'"

/* aceita comentarios em uma ou mais linhas */
COMENT ("//".*"\n"*|("/*"("*/"|(.|"\n")*)))

ID ({LETTER})({LETTER}|{DIGIT}|_)*


%% // separador para a segunda parte do arquivo
 /* Nessa parte define-se as ações a serem tomadas
    quando encontrar uma expressão regular definida acima
 */

KEYWORD {
    printf("palavra reservada %s\n", yytext);
}

DATA_TYPE {
}

{ASSIGNMENT} {
	TokenType t = TOKEN_ASSIGNMENT;
    printf("TODO\n");
}

{END_EXP} {
    printf("TODO EXP\n");
}

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

{COMENT} {
    printf("Comentário = %s\n", yytext);
}

{ID} {
    printf("An identifier: %s\n", yytext);
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
