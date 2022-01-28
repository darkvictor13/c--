#include "logging.h"

const char * typeToMessage(logType type) {
	if (type == LOG_TYPE_INFO) {
		return "INFO";
	}else if (type == LOG_TYPE_ERROR) {
		return "ERROR";
	}
	return "WARNING";
}

void doLog(logType type, const char* format, ...) {
	if (type > LOG_LEVEL) {
		return ;
	}
	if (type == LOG_TYPE_ERROR){
		have_error = true;
	}
    va_list args;
    va_start(args, format);

    printf("[%s]: ", typeToMessage(type));
    vprintf(format, args);
	printf(" na linha [%d]\n", yylineno);

    va_end (args);
}