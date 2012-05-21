#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "commands_parser.h"

struct command parse(char* input) {
	struct command cmd;
	char* arg;
	int i = 0;

	input = trim(input);

	// Getting the command
	cmd.action = strtok(input, " ");

	// Getting arguments
	arg = strtok(NULL, " ");
	while(arg != NULL) {
		strcpy(cmd.arguments[i++], trim(arg));
		arg = strtok(NULL, " ");
	}

	cmd.arguments_count = i;

	return cmd;
}


char* trim(char* input) {
	int trimStart = 0;
	int trimEnd = strlen(input) - 1;
	int idx;
	char* output;
	
	while((trimStart < strlen(input)) && (isspace(input[trimStart]))) {
		trimStart++;
	}

	while((trimEnd > 0) && (isspace(input[trimEnd]))) {
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
