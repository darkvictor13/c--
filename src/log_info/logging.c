#include "logging.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const logTypeInfo typeToInfo(logType type) {
    logTypeInfo ret;

    switch (type) {
        case LOG_TYPE_INFO:
            strcpy(ret.text, "INFO");
            strcpy(ret.color, COLOR_GREEN);
            break;
        case LOG_TYPE_ERROR:
            strcpy(ret.text, "ERRO");
            strcpy(ret.color, COLOR_RED);
            break;
        case LOG_TYPE_WARNING:
            strcpy(ret.text, "WARNING");
            strcpy(ret.color, COLOR_YELLOW);
            break;
        default:
            printf("Erro ao passar tipo da mensagem na func: [%s]\n", __func__);
            exit(EXIT_FAILURE);
    }

    return ret;
}

const char * compilerStageToText(compilerStage stage) {
    switch (stage) {
        case LEXICAL_ANALYSIS:
            return "LÉXICO";
        case SINTATIC_ANALYSIS:
            return "SINTÁTICO";
        case SEMANTIC_ANALYSIS:
            return "SEMÂNTICO";
        default:
            printf("Erro ao passar estágio do compilador na func: [%s]\n", __func__);
            return NULL;
    }
}

void cmmLog(logType type, compilerStage stage, const char* format, ...) {
    if (type > LOG_LEVEL) {
        return ;
    }
    if (type == LOG_TYPE_ERROR) {
        have_error = true;
    }
    va_list args;
    va_start(args, format);

    const logTypeInfo type_info = typeToInfo(type);
    const char *stage_text = compilerStageToText(stage);

    printf(type_info.color);
    printf("[%s %s]: ", type_info.text, stage_text);
    printf(COLOR_DEFAULT);
    vprintf(format, args);
    printf(" na linha [%d]\n", yylineno);

    va_end (args);
}
