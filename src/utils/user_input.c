#include "user_input.h"

#include <ctype.h>

char * getFilenameFromUser() {
	const char default_value[] = "../input_files/falha.c";
	char buffer[64];
    char *ret;

	printf("Deseja entrar com o caminho para o arquivo o qual será feita a análise léxica? [Y/n] ");

	const char user_input = getchar();
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result" 
	scanf("%*[^\n]%*c"); //limpeza do buffer
#pragma GCC diagnostic pop 

	if (tolower(user_input) == 'n') {
		printf("Utilizando arquivo default: %s\n\n", default_value);
		ret = (char *)malloc(sizeof(default_value));
		strcpy(ret, default_value);
	}else {
		printf("Caminho para o arquivo: ");
		if (!scanf("%s%*c", buffer)) {
			printf("Falha na leitura do teclado\n");
			exit(EXIT_FAILURE);
		}
		printf("Utilizando arquivo passado pelo usuário: %s\n\n", buffer);

		ret = (char *)malloc(strlen(buffer) + 1);
		strcpy(ret, buffer);
	}

	return ret;
}
