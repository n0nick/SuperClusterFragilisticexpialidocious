#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include "consts.h"
#include "commands_parser.h"

command parse(char* text, int* success) {
	command cmd;
	char* arg;
	char delims[] = " \f\n\r\t\v"; /* equivalent to C's isspace() */
	int i = 0;

	text = trim(text, success);

	if (*success == SUCCESS) {

		/* getting the command */
		cmd.action = strtok(text, delims);

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
	}

	return cmd;
}


char* trim(char* text, int* success) {
	int trimStart = 0;
	int trimEnd = strlen(text) - 1;
	int idx;
	char* trimmed;
	
	while((trimStart < strlen(text)) && (isspace(text[trimStart]))) {
		trimStart++;
	}

	while((trimEnd > 0) && (isspace(text[trimEnd]))) {
		trimEnd--;
	}

	trimmed = (char *) malloc(trimEnd - trimStart + 1);
	if (trimmed != NULL) {
		idx = trimStart;
		while(idx <= trimEnd) {
			trimmed[idx - trimStart] = text[idx];
			idx++;
		}
		trimmed[idx - trimStart] = '\0';

		*success = SUCCESS;
	} else {
		perror(ERROR_MALLOC);
		*success = FAILURE;
	}

	return trimmed;
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

long int valid_id(char* arg, int size, int* success) {
	bool valid = FALSE;
	long int id = valid_integer(arg);

	*success = SUCCESS;

	if (id > INVALID_ARGUMENT) {
		if (id < size) {
			valid = TRUE;
		} else {
			if (printf("Error: ID number is not in the system\n") < 0) {
				perror(ERROR_PRINTF);
				*success = FAILURE;
			}
		}
	} else {
		if (printf("Error: ID parameter is not a non-negative integer\n") < 0) {
			perror(ERROR_PRINTF);
			*success = FAILURE;
		}
	}

	if (!valid) {
		id = INVALID_ARGUMENT;
	}

	return id;
}

long int valid_cluster_size(char* arg, int* success) {
	bool valid = FALSE;
	long int cluster_size = valid_integer(arg);

	*success = SUCCESS;

	if (cluster_size > INVALID_ARGUMENT) {
		if (cluster_size >= MIN_CLUSTER_SIZE) {
			valid = TRUE;
		}
	}
	
	if (!valid) {
		if (printf("Error: number of clusters parameter must be an integer type bigger than 1\n") < 0) {
			perror(ERROR_PRINTF);
			*success = FAILURE;
		}
		cluster_size = INVALID_ARGUMENT;
	}

	return cluster_size;
}

double valid_weight(char* arg, int* success) {
	int i;
	double weight;
	bool valid = TRUE;
	bool gotDecimalPoint = FALSE;

	*success = SUCCESS;

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
	weight = atof(arg);

	/* the number is NON-NEGATIVE :), :| */
	if (weight < 0) {
		valid = FALSE;
	}

	if (!valid) {
		if (printf("Error: weight parameter is not a non-negative double\n") < 0) {
			perror(ERROR_PRINTF);
			*success = FAILURE;
		}
		weight = INVALID_ARGUMENT;
	}

	return weight;
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
