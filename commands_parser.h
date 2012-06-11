#ifndef superCLUSTERagilisticexpialidoCOMMAND
#define superCLUSTERagilisticexpialidoCOMMAND

#define INT_MAX_STR (char *)"2147483647"

#define MAX_INPUT_SIZE 30
#define MIN_INPUT_SIZE 1
#define MAX_ARGUMENTS 3

#define INVALID_ARGUMENT -1

typedef struct command command;

struct command {
	char action[MAX_INPUT_SIZE];
	char arguments[MAX_ARGUMENTS][MAX_INPUT_SIZE];
	char arguments_count;
};

command parse(char* input, int* success);

long int valid_integer(char* arg);
long int valid_id(char* arg, int size, int* success);
long int valid_cluster_size(char* arg, int* success);
double valid_weight(char* arg, int* success);
bool valid_args_num(command cmd, int requiredArgs, int* success);

#endif
