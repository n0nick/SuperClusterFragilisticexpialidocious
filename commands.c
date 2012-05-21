#include <string.h>
#include <stdlib.h>
#include "consts.h"
#include "commands.h"

char* trim(char* input) {
	int trimStart = 0;
	int trimEnd = strlen(input) - 1;
	int idx;
	char* output;
	
	while((trimStart < strlen(input)) && (input[trimStart] == ' ')) {
		trimStart++;
	}

	while((trimEnd > 0) && (input[trimEnd] == ' ')) {
		trimEnd--;
	}

	output = (char *) malloc(trimEnd - trimStart + 1);
	idx = trimStart;
	while(idx <= trimEnd) {
		output[idx - trimStart] = input[idx];
		idx++;
	}
	output[idx - trimStart] = '\0';

	return output;
}
