#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "safe_funcs.h"

void safe_printf(char* str, ...) {
	va_list argp;
	va_start(argp, str);

	int result;

	result = vprintf(str, argp);

	va_end(argp);

	if (result < 0) {
		//...
		perror("Error: standard function printf has failed\n");
		exit(1);
	}
}