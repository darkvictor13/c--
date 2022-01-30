#ifndef USER_INPUT
#define USER_INPUT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/user_config.h"

/**
 * @brief Interage com o usuário para obter o caminho para o arquivo a ser
 * aberto
 *
 * @return char* ponteiro para um array na heap
 * que contém o nome do aquivo que o usuário deseja abrir
 * @pre stdin limpo para leitura
 * @post usuário escolheu um arquivo para análise léxica
 */
char * getFilenameFromUser();

#endif // USER_INPUT
