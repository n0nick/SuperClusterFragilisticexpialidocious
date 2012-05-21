// superCLUSTERagilisticexpialidocious.cpp : Defines the entry point for the console application.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consts.h"
#include "commands_parser.h"

int main(int argc, char* argv[])
{
	char* input;
	struct command cmd;
	int i = 0;
	int quit = 0;

	input = (char *) malloc(MAX_INPUT_SIZE);

	while (!quit) {
		printf("Give me some input: ");
		if (fgets(input, MAX_INPUT_SIZE, stdin) != NULL) {
			cmd = parse(input);

			if (strcmp(cmd.action, COMMAND_QUIT) == 0) {
				quit = 1;
				printf("I quit!\n");
			} else {
				printf("Command was: %s\n", cmd.action);
				i = 0;
				while(i < cmd.arguments_count) {
					printf("Arguments %d was: %s\n", i+1, cmd.arguments[i]);
					i++;
				}
			}
		} else { // EOF received
			quit = 1;
		}
	}

	// Exiting
	printf("\nThank you, goodbye.\n");
	return 0;
}

