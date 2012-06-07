#ifndef superCLUSTERagilisticexpialidociouVERTEX
#define superCLUSTERagilisticexpialidociouVERTEX

#define VERTEX_ARRAY_INITIAL_SIZE 2
#define VERTEX_ARRAY_SIZE_FACTOR 2

#define MAX_VERTICES 100
#define MAX_WEIGHT 100
#define MAX_TOTAL_WEIGHTS 1000

struct edge {
	unsigned int vertexID;
	double weight;
	struct edge* next;
	struct edge* prev;
};

struct vertex {
	unsigned int id;
	char* name;
	unsigned int degree;
	struct edge* edges;
};

struct vertex* add_vertex(struct vertex* currentArray, int* size, int* maxSize, char* name);
void print_vertices(struct vertex* vertices, int size);
void print_degree(struct vertex* vertices, int id);
void print_by_name(struct vertex* vertices, char* name, int size);
void print_edges(struct vertex* vertices, int size);

void add_edge(struct vertex* vertices, int id1, int id2, double weight, int* countEdges, double* totalWeights);
void remove_edge(struct vertex* vertices, int id1, int id2, int* countEdges, double* totalWeights);
void add_one_edge(struct vertex* vertexFrom, struct vertex* vertexTo, double weight);
int remove_one_edge(struct vertex* vertexFrom, struct vertex* vertexTo);

#endif
