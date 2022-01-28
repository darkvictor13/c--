#ifndef UTILS
#define UTILS

#include <string.h>
#include <stdint.h>

/**
 * @brief Copia qnt caracteres de src para dest
 * 
 * Essa função é utilizada para garantir que a string é null terminated,
 * possui o caractere \0 no final, já que por padrão a std strncpy apenas
 * copia os bytes sem adicionar o \0
 * @param dest local de memória para onde os bytes serão copiados
 * @param src local de memória de onde vem os bytes a serem copiados
 * @param qnt Quantidade de bytes a serem copiados
 * @pre dest deve ter alocado no minimo qnt+1 bytes
 * @post qnt bytes de src copiados para dest
 */
void _strncpy(char * dest, const char *src, const uint8_t qnt);

#endif // UTILS
