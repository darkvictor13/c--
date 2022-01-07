#ifndef LOGGING
#define LOGGING

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h> // exit, EXIT_FAILURE, atexit

typedef enum log_type {
	LOG_TYPE_INFO,
	LOG_TYPE_ERROR,
	LOG_TYPE_WARNING,
}logType;

// TODO always inline
const char * typeToMessage(logType type);

/**
 * @brief 
 * 
 * @param is_error 
 * @param format 
 * @param ... 
 * @pre Nenhuma
 * @post Nenhuma
 */
void doLog(logType is_error, const char* format, ...);

#endif // LOGGING
