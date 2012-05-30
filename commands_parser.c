#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "consts.h"
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

int valid_integer(char* arg) {
	int i;
	int num;
	bool valid = TRUE;

	// 1. The string contains only digits
	for(i = 0; i < strlen(arg); i++) {
		if((arg[i] < '0') || (arg[i] > '9')) { 
			valid = FALSE;
		}
	}

	// 2. The number is bounded by (2^31 - 1)
	num = atoi(arg);
	if((num == MAX_INT) && (strcmp(arg, MAX_INT_STR) != 0)) {
		valid = FALSE;
	}

	// 3. The number is NON-NEGATIVE :), :|
	if(num < 0) {
		valid = FALSE;
	}

	if (valid) {
		return num;
	} else {
		printf("Error: ID parameter is not a non-negative integer\n");
		return INVALID_ARGUMENT;
	}
}

int valid_id(char* arg, int size) {
	int num;
	bool valid = FALSE;

	num = valid_integer(arg);

	if (num > INVALID_ARGUMENT) {
		if (num < size) {
			valid = TRUE;
		} else {
			printf("Error: ID number is not in the system\n");
			return INVALID_ARGUMENT;
		}
	}

	return num;
}

int valid_cluster_size(char* arg, int size) {
	int num;
	bool valid = FALSE;

	num = valid_integer(arg);

	if (num > INVALID_ARGUMENT) {
		if (num >= MIN_CLUSTER_SIZE) {
			valid = TRUE;
		} else {
			printf("Error: ID number is not in the system\n");
			return INVALID_ARGUMENT;
		}
	}

	return num;
}