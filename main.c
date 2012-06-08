#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consts.h"
#include "command_names.h"
#include "commands_parser.h"
#include "vertex.h"
#include "cluster.h"

int main(int argc, char* argv[])
{
	/* definitions */
	struct vertex* vertices;
	char* input;
	command cmd;
	int size = 0;
	int maxSize = VERTEX_ARRAY_INITIAL_SIZE;
	int countEdges = 0;
	bool quit = FALSE;
	long int id, id1, id2, count;
	int ch;
	double weight;
	double totalWeights = 0;

	/* initialize values */
	vertices = (struct vertex *) malloc(VERTEX_ARRAY_INITIAL_SIZE * sizeof(struct vertex));
	input = (char *) malloc(MAX_INPUT_SIZE);
	srand(23);

	while (!quit) {
		scanf("%[^\n]*", input);
		
		if(strlen(input) < MIN_INPUT_SIZE) {
			printf("Error: command must have at least one character\n");
		}
		else if (strlen(input) > MAX_INPUT_SIZE) {
			printf("Error: command length must be less than or equal to 30 characters\n");
		} else {

			cmd = parse(input);

			/* quit */
			if (strcmp(cmd.action, COMMAND_QUIT) == 0) {
				if (valid_args_num(cmd, 0)) {
					quit = TRUE;
				}
			}
			
			/* add vertex */
			else if (strcmp(cmd.action, COMMAND_ADD_VERTEX) == 0) {
				if (valid_args_num(cmd, 1)) {
					if(size >= MAX_VERTICES) {
						printf("Error: cannot add vertex - too many vertices\n");
					} else {
						vertices = add_vertex(vertices, &size, &maxSize, cmd.arguments[0]);
					}
				}
			}

			/* print degree */
			else if(strcmp(cmd.action, COMMAND_PRINT_DEGREE) == 0) {
				if (valid_args_num(cmd, 1)) {
					id = valid_id(cmd.arguments[0], size);
					if (id > INVALID_ARGUMENT) { /* valid id value */
						print_degree(vertices, atoi(cmd.arguments[0]));
					}
				}
			}

			/* add edge */
			else if(strcmp(cmd.action, COMMAND_ADD_EDGE) == 0) {
				if (valid_args_num(cmd, 3)) {
					id1 = valid_id(cmd.arguments[0], size);
					if(id1 > INVALID_ARGUMENT) {
						id2 = valid_id(cmd.arguments[1], size);
						if (id2 > INVALID_ARGUMENT) {
							weight = valid_weight(cmd.arguments[2]);
							if (weight > INVALID_ARGUMENT) {
								if ((totalWeights + weight) > MAX_TOTAL_WEIGHTS) {
									printf("Error: sum of edges weight must be less than 1000\n");
								} else {
									add_edge(vertices, id1, id2, weight, &countEdges, &totalWeights);
								}
							}
						}
					}
				}
			}

			/* remove edge */
			else if(strcmp(cmd.action, COMMAND_REMOVE_EDGE) == 0) {
				if (valid_args_num(cmd, 2)) {
					id1 = valid_id(cmd.arguments[0], size);				
					if(id1 > INVALID_ARGUMENT) {
						id2 = valid_id(cmd.arguments[1], size);
						if (id2 > INVALID_ARGUMENT) {
							remove_edge(vertices, id1, id2, &countEdges, &totalWeights);
						}
					}
				}
			}

			/* id by name */
			else if(strcmp(cmd.action, COMMAND_ID_BY_NAME) == 0) {
				if (valid_args_num(cmd, 1)) {
					print_by_name(vertices, cmd.arguments[0], size);
				}
			}

			/* print */
			else if(strcmp(cmd.action, COMMAND_PRINT) == 0) {
				if (valid_args_num(cmd, 0)) {
					print_vertices(vertices, size);
					if(countEdges > 0) {
						print_edges(vertices, size);
					}
				}
			}

			/* cluster */
			else if(strcmp(cmd.action, COMMAND_CLUSTER) == 0) {
				if (valid_args_num(cmd, 1)) {
					count = valid_cluster_size(cmd.arguments[0]);
					if (count > INVALID_ARGUMENT) {
						cluster(vertices, size, count);
					}
				}
			}
			
			/* unknown command */
			else {
				printf("Error: command not found\n");
			}
		}

		while ((ch = getchar()) != EOF && ch != '\n'); /* cleaning the buffer */
	}

	return 0;
}
