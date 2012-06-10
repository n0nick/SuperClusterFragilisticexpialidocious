#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "vertex.h"
#include "consts.h"

vertex* add_vertex(vertex* currentArray, int* size, int* maxSize, char* name) {
	vertex* newArray;
	int i;

	if((*size) >= (*maxSize)) {
		/* re-allocate memory */
		(*maxSize) = (*maxSize) * VERTEX_ARRAY_SIZE_FACTOR;
		newArray = (vertex *) malloc((*maxSize) * sizeof(vertex));

		/* copy current content */
		for(i = 0; i < (*size); i++) {
			newArray[i].degree = currentArray[i].degree;
			newArray[i].edges = currentArray[i].edges;
			newArray[i].id = currentArray[i].id;
			newArray[i].name = (char *) malloc(strlen(currentArray[i].name) + 1);
			strcpy(newArray[i].name, currentArray[i].name);

			free(currentArray[i].name);
		}

		/* releasing old memory */
		free(currentArray);
	} else {
		newArray = currentArray;
	}

	/* initializing values */
	newArray[*size].id = *size;
	newArray[*size].degree = 0;
	newArray[*size].edges = NULL;
	newArray[*size].name = (char *) malloc(strlen(name) + 1);
	strcpy(newArray[*size].name, name);
	(*size)++;

	currentArray = newArray;
	return currentArray;
}

void print_vertices(vertex* vertices, int size) {
	int i;
	printf("%d vertices:\n", size);
	for(i = 0; i < size; i++) {
		printf("%d: %s\n", vertices[i].id, vertices[i].name);
	}
}

void print_degree(vertex* vertices, int id) {
	printf("%d\n", vertices[id].degree);
}

void print_edges(vertex* vertices, int size) {
	int i;
	edge* currEdge;
	printf("edges:\n");

	for(i = 0; i < size; i++) {
		currEdge = vertices[i].edges;
		while(currEdge != NULL) {
			if (i < currEdge->vertexID) {
				printf("%s %s %f\n", vertices[i].name, vertices[currEdge->vertexID].name, currEdge->weight);
			}
			currEdge = currEdge->next;
		}
	}
}

void print_by_name(vertex* vertices, char* name, int size) {
	int i;
	bool found = FALSE;
	for(i = 0;  i < size; i++) {
		if(strcmp(vertices[i].name, name) == 0) {
			printf("%d\n", vertices[i].id);
			found = TRUE;
		}
	}

	if(found == FALSE) {
		printf("Error: vertex name is not in the system\n");
	}
}

void add_edge(vertex* vertices, int id1, int id2, double weight, int* countEdges, double* totalWeights) {

	bool valid;
	vertex* v1;
	vertex* v2;
	edge* currEdge;

	valid = TRUE;

	/* no edges between the same vertex */
	if (id1 == id2) {
		printf("Error: edge must be between two different vertices\n");
		valid = FALSE;
	}

	if (valid == TRUE) {
		v1 = &(vertices[id1]);
		v2 = &(vertices[id2]);

		/* check to see if vertex already exists */
		if (v1->degree < v2->degree) {
			currEdge = v1->edges;
		} else {
			currEdge = v2->edges;
		}
		while (currEdge != NULL) {
			if ((currEdge->vertexID == v1->id) ||
				(currEdge->vertexID == v2->id)) {
					printf("Error: edge is in the graph\n");
					valid = FALSE;
			}
			currEdge = currEdge->next;
		}
	}

	if (valid == TRUE) {
		add_one_edge(v1, v2, weight);
		add_one_edge(v2, v1, weight);

		/* count edge */
		*countEdges = *countEdges + 1;
		*totalWeights = *totalWeights + weight;
		v1->degree++;
		v2->degree++;
	}

}

void add_one_edge(vertex* vertexFrom, vertex* vertexTo, double weight) {

	/* current edge */
	edge* currEdge;

	/* build new edge */
	edge* newEdge;
	newEdge = (edge*) malloc(sizeof(edge));
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
}

void remove_edge(vertex* vertices, int id1, int id2, int* countEdges, double* totalWeights) {
	
	bool success;
	double removedWeight;
	vertex* v1;
	vertex* v2;

	v1 = &(vertices[id1]);
	v2 = &(vertices[id2]);

	success = ((remove_one_edge(v1, v2, &removedWeight)) && (remove_one_edge(v2, v1, &removedWeight)));

	if(!success) {
		printf("Error: edge is not in the graph\n");
	} else {
		
		/* count edge */
		*countEdges = *countEdges - 1;
		*totalWeights = *totalWeights - removedWeight;
		v1->degree--;
		v2->degree--;
	}
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
