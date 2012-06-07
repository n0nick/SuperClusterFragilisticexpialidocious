#ifndef superCLUSTERagilisticexpialidoCOMMAND
#define superCLUSTERagilisticexpialidoCOMMAND

#define MAX_INPUT_SIZE 30
#define MIN_INPUT_SIZE 2
#define MAX_ARGUMENTS 3

#define INVALID_ARGUMENT -1

typedef struct command {
	char* action;
	char arguments[MAX_ARGUMENTS][MAX_INPUT_SIZE]; // TODO use the constants here
	char arguments_count;
};

struct command parse(char* input);
char* trim(char* input);
int valid_integer(char* arg);
int valid_id(char* arg, int size);
int valid_cluster_size(char* arg);
double valid_weight(char* arg);

#endif
