#ifndef LOGGING
#define LOGGING

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../headers/user_config.h"

extern int yylineno;
extern bool have_error;

typedef struct log_type_info {
    char text[8];
    char color[8];
}logTypeInfo;

typedef enum compiler_stage {
    LEXICAL_ANALYSIS,
    SINTATIC_ANALYSIS,
    SEMANTIC_ANALYSIS
}compilerStage;

#define COLOR_RED       "\e[1;31m"
#define COLOR_GREEN     "\e[1;32m"
#define COLOR_YELLOW    "\e[1;33m"
#define COLOR_DEFAULT   "\e[0m"

/**
 * @brief Transforma o número de um tipo de mensagem
 * em uma palavra para ser impressa e a cor da mensagem, ver logTypeInfo
 *
 * @param type o tipo da mensagem
 * @return const char* palavra correspondente ao tipo
 */
const logTypeInfo typeToInfo(logType type);

/**
 * @brief A partir da definição do estágio do compilador retorna o texto
 * correspondente
 *
 * @param stage Estágio em que o compilador está, ver compilerStage 
 * @return const char* Representação textual do stage
 * @pre Nenhuma
 * @post Nenhuma
 */
const char * compilerStageToText(compilerStage stage);

/**
 * @brief Imprime no terminal a mensagem de log da análise léxica
 *
 * @param type tipo de Mensagem q foi passada, ver logType
 * @param format string de formatação semelhante a recebida pelo printf
 * @param stage estágio que o compilador está, ver compilerStage
 * @param ... n argumentos, interpretados pela string de formatação
 * @pre Nenhuma
 * @post Mensagem de Log impressa no terminal,
 * caso tipo da mensagem seja de erro a flag have_error é ativada
 */
void cmmLog(logType type, compilerStage stage, const char* format, ...);

#endif // LOGGING
