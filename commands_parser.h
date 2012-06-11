#ifndef superCLUSTERagilisticexpialidoCOMMAND
#define superCLUSTERagilisticexpialidoCOMMAND

#define INT_MAX_STR (char *)"2147483647"

#define MAX_INPUT_SIZE 30
#define MIN_INPUT_SIZE 1
#define MAX_ARGUMENTS 3

#define INVALID_ARGUMENT -1

typedef struct command command;

struct command {
	char* action;
	char arguments[MAX_ARGUMENTS][MAX_INPUT_SIZE]; /* TODO use the constants here */
	char arguments_count;
};

command parse(char* input, int* success);
char* trim(char* input, int* success);
long int valid_integer(char* arg);
int validate_id(char* arg, int size, long int* num);
int validate_cluster_size(char* arg, long int* num);
int validate_weight(char* arg, double* num);
int validate_args_num(command cmd, int requiredArgs, bool* isvalid);

#endif
