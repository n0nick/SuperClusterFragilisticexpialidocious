#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "vertex.h"


struct vertex* add_vertex(struct vertex* currentArray, int* size, int* maxSize, char* name) {
	struct vertex* newArray;
	int i;

	if((*size) >= (*maxSize)) {
		// re-allocate memory
		(*maxSize) = (*maxSize) * VERTEX_ARRAY_SIZE_FACTOR;
		newArray = (struct vertex *) malloc((*maxSize) * sizeof(struct vertex));

		// copy current content
		for(i = 0; i < (*size); i++) {
			newArray[i].degree = currentArray[i].degree;
			newArray[i].edges = currentArray[i].edges;
			newArray[i].id = currentArray[i].id;
			newArray[i].name = (char *) malloc(strlen(currentArray[i].name) + 1);
			strcpy(newArray[i].name, currentArray[i].name);

			free(currentArray[i].name);
		}

		// releasing old memory
		free(currentArray);
	} else {
		newArray = currentArray;
	}

	// initializing values
	newArray[*size].id = *size;
	newArray[*size].degree = 0;
	newArray[*size].name = (char *) malloc(strlen(name) + 1);
	strcpy(newArray[*size].name, name);
	(*size)++;

	currentArray = newArray;
	return currentArray;
}

void print_vertices(struct vertex* vertices, int size) {
	int i;
	printf("%d vertices:\n", size);
	for(i = 0; i < size; i++) {
		printf("%d: %s\n", vertices[i].id, vertices[i].name);
	}
}

// @pre id < vertices.size
void print_degree(struct vertex* vertices, int id) {
	printf("%d\n", vertices[id].degree);
}

void print_by_name(struct vertex* vertices, char* name, int size) {
	int i;
	for(i = 0;  i < size; i++) {
		if(strcmp(vertices[i].name, name) == 0) {
			printf("%d\n", vertices[i].id);
		}
	}
}