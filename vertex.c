#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "vertex.h"
#include "consts.h"

vertex* add_vertex(vertex* currentArray, int* size, int* maxSize, char* name, int* success) {
	vertex* newArray;
	int i;
	int failIndex;

	*success = SUCCESS;

	if((*size) >= (*maxSize)) {
		/* re-allocate memory */
		(*maxSize) = (*maxSize) * VERTEX_ARRAY_SIZE_FACTOR;
		newArray = (vertex *) malloc((*maxSize) * sizeof(vertex));
		if (newArray == NULL) {
			perror(ERROR_MALLOC);
			*success = FAILURE;
		}

		/* copy current content */
		for(i = 0; i < (*size) && *success; i++) {
			newArray[i].degree = currentArray[i].degree;
			newArray[i].edges = currentArray[i].edges;
			newArray[i].id = currentArray[i].id;
			newArray[i].name = (char *) malloc(strlen(currentArray[i].name) + 1);
			if (newArray[i].name == NULL) {
				perror(ERROR_MALLOC);
				failIndex = i;
				*success = FAILURE;
			} else {
				strcpy(newArray[i].name, currentArray[i].name);
				free(currentArray[i].name);
			}
		}

		if (*success) {
			/* releasing old memory */
			free(currentArray);
		}
	} else {
		newArray = currentArray;
	}

	if (*success == SUCCESS) {
		/* initializing values */
		newArray[*size].id = *size;
		newArray[*size].degree = 0;
		newArray[*size].edges = NULL;
		newArray[*size].name = (char *) malloc(strlen(name) + 1);
		if (newArray[*size].name == NULL) {
			perror(ERROR_MALLOC);
			failIndex = *size;
			*success = FAILURE;
		}
		strcpy(newArray[*size].name, name);
		(*size)++;

		currentArray = newArray;
	}

	if (*success == FAILURE) {
		if (newArray != NULL) {
			for (i = 0; i < failIndex; i++) {
				free(newArray[i].name);
			}
			free(newArray);
		}
	}

	return currentArray;
}

int print_vertices(vertex* vertices, int size) {
	int i;
	int printf_result;

	printf_result = printf("%d vertices:\n", size);

	for(i = 0; i < size && printf_result >= 0; i++) {
		printf_result = printf("%d: %s\n", vertices[i].id, vertices[i].name);
	}

	if (printf_result < 0) {
		perror(ERROR_PRINTF);
		return FAILURE;
	} else {
		return SUCCESS;
	}
}

int print_edges(vertex* vertices, int size) {
	int i;
	edge* currEdge;
	int printf_result;

	printf_result = printf("edges:\n");

	for(i = 0; i < size && printf_result >= 0; i++) {
		currEdge = vertices[i].edges;
		while(currEdge != NULL && printf_result >= 0) {
			if (i > currEdge->vertexID) { /* to conform with supplied tests */
				printf_result = printf("%s %s %f\n", vertices[i].name, vertices[currEdge->vertexID].name, currEdge->weight);
			}
			currEdge = currEdge->next;
		}
	}

	if (printf_result < 0) {
		perror(ERROR_PRINTF);
		return FAILURE;
	} else {
		return SUCCESS;
	}
}

int print_degree(vertex* vertices, int id) {
	if (printf("%d\n", vertices[id].degree) < 0) {
		perror(ERROR_PRINTF);
		return FAILURE;
	} else {
		return SUCCESS;
	}
}

int print_by_name(vertex* vertices, char* name, int size) {
	int i;
	int printf_result = 0;
	bool found = FALSE;

	for(i = 0;  i < size && printf_result >= 0; i++) {
		if(strcmp(vertices[i].name, name) == 0) {
			printf_result = printf("%d\n", vertices[i].id);
			found = TRUE;
		}
	}

	if (printf_result >= 0) {
		if(found == FALSE) {
			printf_result = printf("Error: vertex name is not in the system\n");
		}
	}

	if (printf_result >= 0) {
		return SUCCESS;
	} else {
		perror(ERROR_PRINTF);
		return FAILURE;
	}
}

int add_edge(vertex* vertices, int id1, int id2, double weight, int* countEdges, double* totalWeights) {

	bool valid;
	vertex* v1;
	vertex* v2;
	edge* currEdge;
	int printf_result = 0;

	valid = TRUE;

	/* no edges between the same vertex */
	if (id1 == id2) {
		printf_result = printf("Error: edge must be between two different vertices\n");
		valid = FALSE;
	}

	if (valid == TRUE && printf_result >= 0) {
		v1 = &(vertices[id1]);
		v2 = &(vertices[id2]);

		/* check to see if vertex already exists */
		if (v1->degree < v2->degree) {
			currEdge = v1->edges;
		} else {
			currEdge = v2->edges;
		}
		while (currEdge != NULL && printf_result >= 0) {
			if ((currEdge->vertexID == v1->id) ||
				(currEdge->vertexID == v2->id)) {
					printf_result = printf("Error: edge is in the graph\n");
					valid = FALSE;
			}
			currEdge = currEdge->next;
		}
	}

	if (printf_result >= 0) {
		if (valid == TRUE) {
			if ((add_one_edge(v1, v2, weight) == SUCCESS) &&
				(add_one_edge(v2, v1, weight) == SUCCESS)) {
					/* count edge */
					*countEdges = *countEdges + 1;
					*totalWeights = *totalWeights + weight;
					v1->degree++;
					v2->degree++;
					return SUCCESS;
			}
		}
	} else {
		perror(ERROR_PRINTF);
	}

	return FAILURE;
}

int add_one_edge(vertex* vertexFrom, vertex* vertexTo, double weight) {

	/* current edge */
	edge* currEdge;

	/* build new edge */
	edge* newEdge;
	newEdge = (edge*) malloc(sizeof(edge));
	if (newEdge != NULL) {
		newEdge->vertexID = vertexTo->id;
		newEdge->weight = weight;
		newEdge->prev = NULL;

		currEdge = vertexFrom->edges;
		if(currEdge == NULL) { /* first edge */
			newEdge->next = NULL;
			vertexFrom->edges = newEdge;
		} else { /* attach to edges list */
			newEdge->next = currEdge;
			currEdge->prev = newEdge;
			vertexFrom->edges = newEdge;
		}
		return SUCCESS;
	} else {
		perror(ERROR_MALLOC);
		return FAILURE;
	}
}

int remove_edge(vertex* vertices, int id1, int id2, int* countEdges, double* totalWeights) {
	
	bool success;
	double removedWeight;
	vertex* v1;
	vertex* v2;

	v1 = &(vertices[id1]);
	v2 = &(vertices[id2]);

	success = ((remove_one_edge(v1, v2, &removedWeight)) && (remove_one_edge(v2, v1, &removedWeight)));

	if(!success) {
		if (printf("Error: edge is not in the graph\n") < 0) {
			perror(ERROR_PRINTF);
			return FAILURE;
		}
	} else {
		/* count edge */
		*countEdges = *countEdges - 1;
		*totalWeights = *totalWeights - removedWeight;
		v1->degree--;
		v2->degree--;
	}

	return SUCCESS;
}

int remove_one_edge(vertex* vertexFrom, vertex* vertexTo, double* removedWeight) {

	bool didDelete;
	edge* currEdge;
	didDelete = FALSE;

	currEdge = vertexFrom->edges;
	while((currEdge != NULL) && (!didDelete)) {
		if(currEdge->vertexID == vertexTo->id) {

			/* first */
			if(currEdge->prev == NULL) {
				vertexFrom->edges = currEdge->next;
				if(currEdge->next != NULL) { /* first but not last */
					currEdge->next->prev = NULL;
				}
			}

			/* last */
			else if(currEdge->next == NULL) {
				currEdge->prev->next = NULL;
			}

			/* middle */
			else {
				currEdge->prev->next = currEdge->next;
				currEdge->next->prev = currEdge->prev;
			}

			didDelete = TRUE;
		}

		if(!didDelete) {
			currEdge = currEdge->next;
		}
	}

	if(didDelete) {
		*removedWeight = currEdge->weight;
		free(currEdge);
	}

	return (didDelete);
}
