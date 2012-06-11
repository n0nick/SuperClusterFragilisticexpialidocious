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
	int size = 0;
	int maxSize = VERTEX_ARRAY_INITIAL_SIZE;
	double totalWeights = 0;
	int countEdges = 0;

	char input[MAX_INPUT_SIZE + 1 + 1];
	int ch;
	command cmd;
	long int id, id1, id2, count;
	double weight;
	bool valid_args;

	int i;
	int success;
	bool quit = FALSE;

	int printf_result = 0;

	/* initialize values */
	srand(23);
	vertices = (struct vertex *) malloc(VERTEX_ARRAY_INITIAL_SIZE * sizeof(struct vertex));
	if (vertices == NULL) {
		perror(ERROR_MALLOC);
		return EXIT_FAILURE;
	}

	while (!quit) {
		/* main input loop */
		i = 0;
		while ((ch = getchar()) != '\n' && ch != EOF &&
				i < (MAX_INPUT_SIZE + 1)) {
			input[i++] = ch;
		}
		input[i] = '\0';

		if (ch != '\n' && ch != EOF) { /* clear input buffer */
			while ((ch = getchar()) != EOF && ch != '\n');
		}

		if(strlen(input) < MIN_INPUT_SIZE) {
			printf_result = printf("Error: command must have at least one character\n");
		}
		else if (strlen(input) > MAX_INPUT_SIZE) {
			printf_result = printf("Error: command length must be less than or equal to 30 characters\n");
		} else {

			cmd = parse(input, &success);
			if (success == FAILURE) {
				/* TODO free everything */
				return EXIT_FAILURE;
			}

			/* quit */
			if (strcmp(cmd.action, COMMAND_QUIT) == 0) {
				if (validate_args_num(cmd, 0, &valid_args) == SUCCESS) {
					if (valid_args) {
						quit = TRUE;
					}
				} else {
					/* TODO free everything */
				}
			}

			/* add vertex */
			else if (strcmp(cmd.action, COMMAND_ADD_VERTEX) == 0) {
				if (validate_args_num(cmd, 1, &valid_args) == SUCCESS) {
					if (valid_args) {
						if(size >= MAX_VERTICES) {
							printf_result = printf("Error: cannot add vertex - too many vertices\n");
						} else {
							vertices = add_vertex(vertices, &size, &maxSize, cmd.arguments[0], &success);
							if (success == FAILURE) {
								/* TODO free everyting */
							}
						}
					}
				} else {
					/* TODO free everything */
				}
			}

			/* print degree */
			else if(strcmp(cmd.action, COMMAND_PRINT_DEGREE) == 0) {
				if (validate_args_num(cmd, 1, &valid_args) == SUCCESS) {
					if (valid_args) {
						if (validate_id(cmd.arguments[0], size, &id) == SUCCESS) {
							if (id > INVALID_ARGUMENT) { /* valid id value */
								if (print_degree(vertices, atoi(cmd.arguments[0])) == FAILURE) {
									/* TODO free everything */
								}
							}
						} else {
							/* TODO free everything */
						}
					}
				} else {
					/* TODO free everything */
				}
			}

			/* add edge */
			else if(strcmp(cmd.action, COMMAND_ADD_EDGE) == 0) {
				if (validate_args_num(cmd, 3, &valid_args) == SUCCESS) {
					if (valid_args) {
						if (validate_id(cmd.arguments[0], size, &id1) == SUCCESS) {
							if(id1 > INVALID_ARGUMENT) {
								if (validate_id(cmd.arguments[1], size, &id2) == SUCCESS) {
									if (id2 > INVALID_ARGUMENT) {
										if (validate_weight(cmd.arguments[2], &weight) == SUCCESS) {
											if (weight > INVALID_ARGUMENT) {
												/* validate weight value */
												if (weight >= MAX_WEIGHT) {
													printf_result = printf("Error: weight parameter must be less than 100\n");
												}
												else if ((totalWeights + weight) > MAX_TOTAL_WEIGHTS) {
													printf_result = printf("Error: sum of edges weight must be less than 1000\n");
												} else {
													if (add_edge(vertices, id1, id2, weight, &countEdges, &totalWeights) == FAILURE) {
														/* TODO free everything */
													}
												}
											}
										} else {
											/* TODO free everything */
										}
									}
								} else {
									/* TODO free everything */
								}
							}
						} else {
							/* TODO free everything */
						}
					}
				} else {
					/* TODO free everything */
				}
			}

			/* remove edge */
			else if(strcmp(cmd.action, COMMAND_REMOVE_EDGE) == 0) {
				if (validate_args_num(cmd, 2, &valid_args) == SUCCESS) {
					if (valid_args) {
						if (validate_id(cmd.arguments[0], size, &id1) == SUCCESS) {
							if(id1 > INVALID_ARGUMENT) {
								if (validate_id(cmd.arguments[1], size, &id2) == SUCCESS) {
									if (id2 > INVALID_ARGUMENT) {
										if (remove_edge(vertices, id1, id2, &countEdges, &totalWeights) == FAILURE) {
											/* TODO free everything */
										}
									}
								} else {
									/* TODO free everything */
								}
							}
						} else {
							/* TODO free everything */
						}
					}
				} else {
					/* TODO free everything */
				}
			}

			/* id by name */
			else if(strcmp(cmd.action, COMMAND_ID_BY_NAME) == 0) {
				if (validate_args_num(cmd, 1, &valid_args) == SUCCESS) {
					if (valid_args) {
						if (print_by_name(vertices, cmd.arguments[0], size) == FAILURE) {
							/*TODO free everything */
						}
					}
				} else {
					/* TODO free everything */
				}
			}

			/* print */
			else if(strcmp(cmd.action, COMMAND_PRINT) == 0) {
				if (validate_args_num(cmd, 0, &valid_args) == SUCCESS) {
					if (valid_args) {
						if (print_vertices(vertices, size) == SUCCESS) {
							if(countEdges > 0) {
								if (print_edges(vertices, size) == FAILURE) {
									/* TODO free everything */
								}
							}
						} else {
							/* TODO free everything */
						}
					}
				} else {
					/* TODO free everything */
				}
			}

			/* cluster */
			else if(strcmp(cmd.action, COMMAND_CLUSTER) == 0) {
				if (validate_args_num(cmd, 1, &valid_args) == SUCCESS) {
					if (valid_args) {
						if  (validate_cluster_size(cmd.arguments[0], &count) == SUCCESS) {
							if (count > INVALID_ARGUMENT) {
								cluster(vertices, size, count);
							}
						} else {
							/* TODO free everything */
						}
					}
				} else {
					/* TODO free everything */
				}
			}

			/* unknown command */
			else {
				printf_result = printf("Error: command not found\n");
			}
		}

		if (printf_result < 0) {
			perror(ERROR_PRINTF);
			/* TODO free everything */
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}
