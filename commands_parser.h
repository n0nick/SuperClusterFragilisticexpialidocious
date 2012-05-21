#ifndef superCLUSTERagilisticexpialidoCOMMAND
#define superCLUSTERagilisticexpialidoCOMMAND

#define MAX_INPUT_SIZE 100
#define MAX_ARGUMENTS 100

struct command {
	char* action;
	char arguments[MAX_INPUT_SIZE][MAX_ARGUMENTS]; // TODO use the constants here
	char arguments_count;
};

struct command parse(char* input);
char* trim(char* input);


#endif
