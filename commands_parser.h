#ifndef superCLUSTERagilisticexpialidoCOMMAND
#define superCLUSTERagilisticexpialidoCOMMAND

#define INT_MAX_STR (char *)"2147483647"

#define MAX_INPUT_SIZE 30
#define MIN_INPUT_SIZE 2
#define MAX_ARGUMENTS 3

#define INVALID_ARGUMENT -1

typedef struct command command;

struct command {
	char* action;
	char arguments[MAX_ARGUMENTS][MAX_INPUT_SIZE]; /* TODO use the constants here */
	char arguments_count;
};

command parse(char* input);
char* trim(char* input);
long int valid_integer(char* arg);
long int valid_id(char* arg, int size);
long int valid_cluster_size(char* arg);
double valid_weight(char* arg);
bool valid_args_num(command cmd, int requiredArgs);

#endif
