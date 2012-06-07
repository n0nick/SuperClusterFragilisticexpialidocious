void cluster(struct vertex* vertices, int size, int clustersCount);

int* random_ints(int arraySize, int max);
void print_clusters(struct vertex* vertices, int size, int* clusters, int clustersCount);
double clustering_score(struct vertex* vertices, int size, int* clusters);