#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include "consts.h"
#include "commands_parser.h"

command parse(char* input, int* success) {
	command cmd;
	char* arg;
	char delims[] = " \f\n\r\t\v"; /* equivalent to C's isspace() */
	int i = 0;

	input = trim(input, success);

	if (*success == SUCCESS) {

		/* getting the command */
		cmd.action = strtok(input, delims);

		/* getting arguments */
		arg = strtok(NULL, delims);
		while(arg != NULL && *success == SUCCESS) {
			strcpy(cmd.arguments[i++], trim(arg, success));
			if (*success == SUCCESS) {
				arg = strtok(NULL, delims);
			}
		}
	}

	if (*success == SUCCESS) {
		cmd.arguments_count = i;
		free(input);
	}

	return cmd;
}


char* trim(char* input, int* success) {
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
	if (output != NULL) {
		idx = trimStart;
		while(idx <= trimEnd) {
			output[idx - trimStart] = input[idx];
			idx++;
		}
		output[idx - trimStart] = '\0';

		*success = SUCCESS;
	} else {
		perror(ERROR_MALLOC);
		*success = FAILURE;
	}

	return output;
}

long int valid_integer(char* arg) {
	int i;
	long int num;
	bool valid = TRUE;

	/* 1. The string contains only digits */
	for(i = 0; i < strlen(arg); i++) {
		if((arg[i] < '0') || (arg[i] > '9')) { 
			valid = FALSE;
		}
	}

	/* 2. The number is bounded by (2^31 - 1) */
	num = atoi(arg);
	if((num == LONG_MAX) && (strcmp(arg, INT_MAX_STR) != 0)) {
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

int validate_id(char* arg, int size, long int* num) {
	bool valid = FALSE;

	*num = valid_integer(arg);

	if (*num > INVALID_ARGUMENT) {
		if (*num < size) {
			valid = TRUE;
		} else {
			if (printf("Error: ID number is not in the system\n") < 0) {
				perror(ERROR_PRINTF);
				return FAILURE;
			}
		}
	} else {
		if (printf("Error: ID parameter is not a non-negative integer\n") < 0) {
			perror(ERROR_PRINTF);
			return FAILURE;
		}
	}

	if (!valid) {
		*num = INVALID_ARGUMENT;
	}

	return SUCCESS;
}

int validate_cluster_size(char* arg, long int* num) {
	bool valid = FALSE;

	*num = valid_integer(arg);

	if (*num > INVALID_ARGUMENT) {
		if (*num >= MIN_CLUSTER_SIZE) {
			valid = TRUE;
		}
	}
	
	if (!valid) {
		if (printf("Error: number of clusters parameter must be an integer type bigger than 1\n") < 0) {
			perror(ERROR_PRINTF);
			return FAILURE;
		}
		*num = INVALID_ARGUMENT;
	}

	return SUCCESS;
}

int validate_weight(char* arg, double* num) {
	int i;
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
	*num = atof(arg);

	/* the number is NON-NEGATIVE :), :| */
	if(*num < 0) {
		valid = FALSE;
	}

	if (!valid) {
		if (printf("Error: weight parameter is not a non-negative double\n") < 0) {
			perror(ERROR_PRINTF);
			return FAILURE;
		}
		*num = INVALID_ARGUMENT;
	}

	return SUCCESS;
}

bool valid_args_num(command cmd, int requiredArgs, int* success) {
	*success = TRUE;

	if (cmd.arguments_count != requiredArgs) {
		if (printf("Error: command %s must have %d parameters\n", cmd.action, requiredArgs) < 0) {
			perror(ERROR_PRINTF);
			*success = FAILURE;
		}
		return FALSE;
	} else {
		return TRUE;
	}
}
