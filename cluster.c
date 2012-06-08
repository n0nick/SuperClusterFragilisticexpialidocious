#include <stdio.h>
#include <stdlib.h>
#include "cluster.h"
#include "vertex.h"

int* random_ints(int arraySize, int max) {
	int i;	
	int* arr = (int*) malloc(sizeof(int) * arraySize);
	
	for(i = 0; i < arraySize; i++) {
		arr[i] = max * rand() / (RAND_MAX + 1.0);
	}
	
	return arr;
}

void cluster(vertex* vertices, int size, int clustersCount) {
	int* clusters;

	clusters = random_ints(size, clustersCount);
	print_clusters(vertices, size, clusters, clustersCount);
}

void print_clusters(vertex* vertices, int size, int* clusters, int clustersCount) {
	int i;
	double score;

	if (size > 0) {
		printf("%d vertices:\n", size);
		for (i = 0; i < size; i++) {
			printf("%s %d\n", vertices[i].name, clusters[i]);
		}

		score = clustering_score(vertices, size, clusters);
		printf("The random clustering score of %d clusters is %f\n", clustersCount, score);
	} else {
		printf("\n");
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
