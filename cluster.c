#include <stdio.h>
#include <stdlib.h>
#include "consts.h"
#include "vertex.h"
#include "cluster.h"

int* random_ints(int arraySize, int max) {
	int i;	
	int* arr = (int*) malloc(sizeof(int) * arraySize);
	
	if (arr == NULL) { /* malloc failure */
		perror(ERROR_MALLOC);
	}
	else {
		for (i = 0; i < arraySize; i++) {
			arr[i] = rand() % max;
		}
	}

	return arr;
}

int cluster(vertex* vertices, int size, int clustersCount) {
	int* clusters;
	int success = FAILURE;

	clusters = random_ints(size, clustersCount);
	if (clusters != NULL) {
		success = print_clusters(vertices, size, clusters, clustersCount);
		free(clusters);
	}

	/* failure */
	return success;
}

int print_clusters(vertex* vertices, int size, int* clusters, int clustersCount) {
	int i;
	int printf_result;
	double score;

	if (size > 0) {
		printf_result = printf("%d vertices:\n", size);
		for (i = 0; i < size && printf_result >= 0; i++) {
			printf_result = printf("%s %d\n", vertices[i].name, clusters[i]);
		}

		if (printf_result >= 0) {
			score = clustering_score(vertices, size, clusters);
			printf_result = printf("The random clustering score for %d clusters is %f\n", clustersCount, score);
		}
	} else {
		printf_result = printf("\n");
	}

	if (printf_result < 0) {
		perror(ERROR_PRINTF);
		return FAILURE;
	} else {
		return SUCCESS;
	}
}

double clustering_score(vertex* vertices, int size, int* clusters) {
	
	double scoreInside = 0;
	double scoreOutside = 0;
	int i;
	edge* currEdge;

	for(i = 0; i < size; i++) {
		currEdge = vertices[i].edges;
		while(currEdge != NULL) {

			if (i < currEdge->vertexID) {
				if(clusters[i] == clusters[currEdge->vertexID]) {
					scoreInside += currEdge->weight;
				} else {
					scoreOutside += currEdge->weight;
				}
			}

			currEdge = currEdge->next;
		}
	}
	
	return (scoreInside - scoreOutside);
}
