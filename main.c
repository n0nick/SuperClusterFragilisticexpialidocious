// main.c : Defines the entry point for the console application.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consts.h"
#include "command_names.h"
#include "commands_parser.h"
#include "vertex.h"

int main(int argc, char* argv[])
{
	// definitions
	struct vertex* vertices;
	char* input;
	struct command cmd;
	int size = 0;
	int maxSize = VERTEX_ARRAY_INITIAL_SIZE;
	int i = 0;
	bool quit = FALSE;
	int id;
	int ch;

	// initialize values
	vertices = (struct vertex *) malloc(VERTEX_ARRAY_INITIAL_SIZE * sizeof(struct vertex));
	input = (char *) malloc(MAX_INPUT_SIZE);

	while (!quit) {
		scanf("%[^\n]*", input);
		
		if(strlen(input) < MIN_INPUT_SIZE) {
			printf("Error: command must have at least one character\n");
		}
		else if (strlen(input) > MAX_INPUT_SIZE) {
			printf("Error: command length must be less than or equal to 30 characters\n");
		} else {

			cmd = parse(input);

			// quit
			if (strcmp(cmd.action, COMMAND_QUIT) == 0) {
				quit = TRUE;
			}
			
			// add vertex
			else if (strcmp(cmd.action, COMMAND_ADD_VERTEX) == 0) {
				vertices = add_vertex(vertices, &size, &maxSize, cmd.arguments[0]);
			}

			// print degree
			else if(strcmp(cmd.action, COMMAND_PRINT_DEGREE) == 0) {
				id = valid_id(cmd.arguments[0], size);
				if (id > INVALID_ARGUMENT) { // valid id value
					print_degree(vertices, atoi(cmd.arguments[0]));
				}
			}

			// add edge

			// remove edge

			// id by name
			else if(strcmp(cmd.action, COMMAND_ID_BY_NAME) == 0) {
				print_by_name(vertices, cmd.arguments[0], size);
			}

			// print
			else if(strcmp(cmd.action, COMMAND_PRINT) == 0) {
				print_vertices(vertices, size);
			}

			// cluster
			
			// unknown command
			else {
				printf("Error: command not found\n");
			}
		}

		while ((ch = getchar()) != EOF && ch != '\n'); // Cleaning the buffer
	}

	return 0;
}
