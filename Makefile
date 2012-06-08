CFLAGS = -Wall -ansi -pedantic-errors
CC = gcc

ex2 : main.o commands_parser.o vertex.o cluster.o

main.o : main.c consts.h command_names.h
	$(CC) $(CFLAGS)	-c main.c

commands_parser.o : consts.h commands_parser.h
	$(CC) $(CFLAGS)	-c commands_parser.c

vertex.o : consts.h vertex.h
	$(CC) $(CFLAGS)	-c vertex.c

cluster.o : vertex.h cluster.h
	$(CC) $(CFLAGS)	-c cluster.c

clean :
	rm ex2 main.o commands_parser.o vertex.o cluster.o
