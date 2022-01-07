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
	const char *type_message = typeToMessage(type);
    va_list args;
    va_start(args, format);

    printf("[%s]: ", type_message);
    vprintf(format, args);

	if (type == LOG_TYPE_ERROR) {
		exit(EXIT_FAILURE);
	}

    va_end (args);
}