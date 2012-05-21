// superCLUSTERagilisticexpialidocious.cpp : Defines the entry point for the console application.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consts.h"
#include "commands.h"

int main(int argc, char* argv[])
{
	// vars
	char* input;
	char* currentPiece;
	char* command = (char *) malloc(MAX_INPUT_SIZE);
	char arguments[MAX_ARGUMENTS][MAX_INPUT_SIZE];
	int id = 0;
	int i = 0;

	input = (char *) malloc(MAX_INPUT_SIZE);

	// Reading input
	scanf("%[^\n\r]s", input);
	input = trim(input);

	// Getting the command
	command = strtok(input, " ");

	// Getting arguments
	currentPiece = strtok(NULL, " ");
	while(currentPiece != NULL) {
		strcpy(arguments[id++], trim(currentPiece));
		currentPiece = strtok(NULL, " ");
	}

	// Looping until getting quit
	printf("command was: %s\n\r", command);
	while(i < id) {
		printf("arguments %d is: %s\n\r", i+1, arguments[i]);
		i++;
	}

	// Exiting
	return 0;
}

