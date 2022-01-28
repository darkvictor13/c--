#include "user_input.h"

char * getFilenameFromUser() {
    char *buffer;
	const char default_value[] = "../input_files/falha.c";
	buffer = malloc(strlen(default_value) + 1);
	strcpy(buffer, default_value);
	return buffer;
}
