#include "user_input.h"

char * getFilenameFromUser() {
    char *buffer;
#if USE_TERMINAL
	buffer = malloc(9);
	strcpy(buffer, "terminal");
#else
	const char default_value[] = "../input_files/falha.txt";
	buffer = malloc(strlen(default_value) + 1);
	strcpy(buffer, default_value);
#endif
	return buffer;
}
