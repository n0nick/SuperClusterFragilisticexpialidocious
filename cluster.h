#ifndef superCLUSTERagilisticexpialidoCLUSTER
#define superCLUSTERagilisticexpialidoCLUSTER

void cluster(vertex* vertices, int size, int clustersCount, int* success);

int* random_ints(int arraySize, int max);
void print_clusters(vertex* vertices, int size, int* clusters, int clustersCount, int* success);
double clustering_score(vertex* vertices, int size, int* clusters);

#endif
