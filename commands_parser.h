#ifndef superCLUSTERagilisticexpialidoCOMMAND
#define superCLUSTERagilisticexpialidoCOMMAND

struct command {
	char* action;
	char arguments[100][100]; // TODO use the constants here
	char arguments_count;
};

struct command parse(char* input);
char* trim(char* input);


#endif
