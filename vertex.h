#ifndef superCLUSTERagilisticexpialidociouVERTEX
#define superCLUSTERagilisticexpialidociouVERTEX

#define VERTEX_ARRAY_INITIAL_SIZE 2
#define VERTEX_ARRAY_SIZE_FACTOR 2

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
	struct edge edges;
};

struct vertex* add_vertex(struct vertex* currentArray, int* size, int* maxSize, char* name);
void print_vertices(struct vertex* vertices, int size);
void print_degree(struct vertex* vertices, int id);
void print_by_name(struct vertex* vertices, char* name, int size);

void add_edge(struct vertex* vertices, int id1, int id2, float weight);
void remove_edge(struct vertex* vertices, int id1, int id2);

#endif
