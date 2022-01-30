#ifndef LOGGING
#define LOGGING

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../headers/user_config.h"

extern int yylineno;
extern bool have_error;

// TODO always inline
/**
 * @brief Transforma o número de um tipo de mensagem
 * em uma palavra para ser impressa
 * 
 * @param type o tipo da mensagem
 * @return const char* palavra correspondente ao tipo
 */
const char * typeToMessage(logType type);

/**
 * @brief Imprime no terminal a mensagem de log
 * 
 * @param type tipo de Mensagem q foi passada, ver logType
 * @param format string de formatação semelhante a recebida pelo printf
 * @param ... n argumentos, interpretados pela string de formatação
 * @pre Nenhuma
 * @post Mensagem de Log impressa no terminal
 */
void doLog(logType type, const char* format, ...);

#endif // LOGGING
