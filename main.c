// superCLUSTERagilisticexpialidocious.cpp : Defines the entry point for the console application.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consts.h"
#include "commands_parser.h"

int main(int argc, char* argv[])
{
	// vars
	char* input;
	struct command cmd;
	int i = 0;

	input = (char *) malloc(MAX_INPUT_SIZE);

	// Reading input
	scanf("%[^\n\r]s", input);
	cmd = parse(input);

	// Looping until getting quit
	printf("command was: %s\n\r", cmd.action);
	while(i < cmd.arguments_count) {
		printf("arguments %d is: %s\n\r", i+1, cmd.arguments[i]);
		i++;
	}

	// Exiting
	return 0;
}

