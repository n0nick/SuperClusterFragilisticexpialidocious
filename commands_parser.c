#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "consts.h"
#include "commands_parser.h"

command parse(char* input) {
	command cmd;
	char* arg;
	int i = 0;

	input = trim(input);

	/* getting the command */
	cmd.action = strtok(input, " ");

	/* getting arguments */
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
	char max_int_str[12];

	/* string representation of INT_MAX */
	itoa(INT_MAX, max_int_str, 10);

	/* 1. The string contains only digits */
	for(i = 0; i < strlen(arg); i++) {
		if((arg[i] < '0') || (arg[i] > '9')) { 
			valid = FALSE;
		}
	}

	/* 2. The number is bounded by (2^31 - 1) */
	num = atoi(arg);
	if((num == INT_MAX) && (strcmp(arg, max_int_str) != 0)) {
		valid = FALSE;
	}

	/* 3. The number is NON-NEGATIVE :), :| */
	if(num < 0) {
		valid = FALSE;
	}

	if (valid) {
		return num;
	} else {
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
		}
	} else {
		printf("Error: ID parameter is not a non-negative integer\n");
	}

	if (valid) {
		return num;
	} else {
		return INVALID_ARGUMENT;
	}
}

int valid_cluster_size(char* arg, int size) {
	int num;
	bool valid = FALSE;

	num = valid_integer(arg);

	if (num > INVALID_ARGUMENT) {
		if (num >= MIN_CLUSTER_SIZE) {
			valid = TRUE;
		}
	}
	
	if (!valid) {
		printf("Error: number of clusters parameter must be an integer type bigger than 1\n");
		return INVALID_ARGUMENT;
	}

	return num;
}

double valid_weight(char* arg) {
	int i;
	double num;
	bool valid = TRUE;
	bool gotDecimalPoint = FALSE;

	/* 1. The string contains only digits */
	for(i = 0; (i < strlen(arg)) && (valid == TRUE); i++) {
		if((gotDecimalPoint == FALSE) && (arg[i] == '.')) {
			gotDecimalPoint = TRUE;
		}
		else if((arg[i] < '0') || (arg[i] > '9')) {
			valid = FALSE;
		}
		
	}

	/* converting string --> double */
	num = atof(arg);

	/* the number is NON-NEGATIVE :), :| */
	if(num < 0) {
		valid = FALSE;
	}

	if (valid == TRUE) {
		return num;
	} else {
		printf("Error: weight paramteter is a non-negative double\n");
		return INVALID_ARGUMENT;
	}
}

bool valid_args_num(command cmd, int requiredArgs) {
	if (cmd.arguments_count != requiredArgs) {
		printf("Error: command %s must have %d parameters\n", cmd.action, requiredArgs);
		return FALSE;
	} else {
		return TRUE;
	}
}
