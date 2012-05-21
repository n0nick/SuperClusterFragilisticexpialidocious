#ifndef superCLUSTERagilisticexpialidociouSTRUCTS
#define superCLUSTERagilisticexpialidociouSTRUCTS

struct edge {
	unsigned int vertexID;
	double weight;
	edge* next;
	edge* prev;
}

struct vertex {
	unsigned int id;
	char* name;
	unsigned int degree;
	edge edges;
}

#endif
