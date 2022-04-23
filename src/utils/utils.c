#include "utils.h"

void _strncpy(char * dest, const char *src, const uint8_t qnt) {
    strncpy(dest, src, qnt);
    if (!dest[qnt]) {
        dest[qnt] = '\0';
    }
}
