#include "utils.h"

void _strncpy(char * dest, const char *src, const uint8_t qnt) {
    memcpy(dest, src, qnt);
	dest[qnt] = '\0';
}
