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
	vertex* vertices;
	int size = 0;
	int maxSize = VERTEX_ARRAY_INITIAL_SIZE;
	double totalWeights = 0;
	int edges_count = 0;
	edge* currEdge;
	edge* nextEdge;

	char input[MAX_INPUT_SIZE + 1 + 1];
	int ch;
	command cmd;
	long int id, id1, id2, count;
	double weight;

	int i;
	int success = SUCCESS;
	int printf_result = 0;
	bool quit = FALSE;

	/* initialize values */
	srand(23);
	vertices = (vertex *) malloc(VERTEX_ARRAY_INITIAL_SIZE * sizeof(vertex));
	if (vertices == NULL) {
		perror(ERROR_MALLOC);
		return EXIT_FAILURE;
	}

	while (!quit) {
		/* main input loop */
		i = 0;
		while ((ch = getchar()) != '\n' && ch != EOF &&
				i < (MAX_INPUT_SIZE + 1)) { /* +1 to identify long commands */
			input[i++] = ch;
		}
		input[i] = '\0';

		if (ch != '\n' && ch != EOF) { /* clear input buffer */
			while ((ch = getchar()) != EOF && ch != '\n');
		}

		if (ch == EOF) { /* got EOF, quit */
			perror(ERROR_GETCH);
			success = FAILURE;

		} else {
			/* validate command length */
			if (strlen(input) < MIN_INPUT_SIZE) {
				printf_result = printf("Error: command must have at least one character\n");
			}
			else if (strlen(input) > MAX_INPUT_SIZE) {
				printf_result = printf("Error: command length must be less than or equal to 30 characters\n");
			} else {
				/* parse command and process it */
				cmd = parse(input, &success);

				if (success == SUCCESS) {

					/* action: quit */
					if (strcmp(cmd.action, COMMAND_QUIT) == 0) {
						if (valid_args_num(cmd, 0, &success) && success) {
							quit = TRUE;
						}
					}

					/* action: add vertex */
					else if (strcmp(cmd.action, COMMAND_ADD_VERTEX) == 0) {
						if (valid_args_num(cmd, 1, &success) && success) {
							if(size >= MAX_VERTICES) {
								printf_result = printf("Error: cannot add vertex - too many vertices\n");
							} else {
								vertices = add_vertex(vertices, &size, &maxSize, cmd.arguments[0], &success);
							}
						}
					}

					/* action: print degree */
					else if(strcmp(cmd.action, COMMAND_PRINT_DEGREE) == 0) {
						if (valid_args_num(cmd, 1, &success) && success) {
							id = valid_id(cmd.arguments[0], size, &success);
							if (success && id > INVALID_ARGUMENT) { /* valid id value */
								print_degree(vertices, atoi(cmd.arguments[0]), &success);
							}
						}
					}

					/* action: add edge */
					else if(strcmp(cmd.action, COMMAND_ADD_EDGE) == 0) {
						if (valid_args_num(cmd, 3, &success) && success) {
							id1 = valid_id(cmd.arguments[0], size, &success);
							if (success && id1 > INVALID_ARGUMENT) {
								id2 = valid_id(cmd.arguments[1], size, &success);
								if (success && id2 > INVALID_ARGUMENT) {
									weight = valid_weight(cmd.arguments[2], &success);
									if (success && weight > INVALID_ARGUMENT) {
										/* validate weight value */
										if (weight >= MAX_WEIGHT) {
											printf_result = printf("Error: weight parameter must be less than 100\n");
										}
										else if ((totalWeights + weight) > MAX_TOTAL_WEIGHTS) {
											printf_result = printf("Error: sum of edges weight must be less than 1000\n");
										} else {
											add_edge(vertices, id1, id2, weight, &edges_count, &totalWeights, &success);
										}
									}
								}
							}
						}
					}

					/* action: remove edge */
					else if(strcmp(cmd.action, COMMAND_REMOVE_EDGE) == 0) {
						if (valid_args_num(cmd, 2, &success) && success) {
							id1 = valid_id(cmd.arguments[0], size, &success);
							if (success && id1 > INVALID_ARGUMENT) {
								id2 = valid_id(cmd.arguments[1], size, &success);
								if (success && id2 > INVALID_ARGUMENT) {
									remove_edge(vertices, id1, id2, &edges_count, &totalWeights, &success);
								}
							}
						}
					}

					/* action: id by name */
					else if(strcmp(cmd.action, COMMAND_ID_BY_NAME) == 0) {
						if (valid_args_num(cmd, 1, &success) && success) {
							print_by_name(vertices, cmd.arguments[0], size, &success);
						}
					}

					/* action: print */
					else if(strcmp(cmd.action, COMMAND_PRINT) == 0) {
						if (valid_args_num(cmd, 0, &success) && success) {
							if (size > 0) {
								print_vertices(vertices, size, &success);
								if (success && edges_count > 0) {
									print_edges(vertices, size, &success);
								}
							} else {
								printf_result = printf("\n");
							}
						}
					}

					/* action: cluster */
					else if(strcmp(cmd.action, COMMAND_CLUSTER) == 0) {
						if (valid_args_num(cmd, 1, &success) && success) {
							count = valid_cluster_size(cmd.arguments[0], &success);
							if (success && count > INVALID_ARGUMENT) {
								cluster(vertices, size, count, &success);
							}
						}
					}

					/* unknown command */
					else {
						printf_result = printf("Error: command not found\n");
					}
				}
			}
		}

		/* handle errors */
		if (printf_result < 0) { /* printf error occurred */
			perror(ERROR_PRINTF);
			success = FAILURE;
		}

		if (success == FAILURE) { /* if failure detected, quit loop */
			quit = TRUE;
		}
	}

	/* free everything */
	for (i = 0; i < size; i++) {
		currEdge = vertices[i].edges;
		while (currEdge != NULL) {
			nextEdge = currEdge->next;
			free(currEdge);
			currEdge = nextEdge;
		}
		free(vertices[i].name);
	}
	free(vertices);

	if (success == FAILURE) {
		return EXIT_FAILURE;
	} else {
		return EXIT_SUCCESS;
	}
}
