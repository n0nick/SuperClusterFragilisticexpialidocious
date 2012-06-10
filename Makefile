CFLAGS = -Wall -ansi -pedantic-errors
CC = gcc

ex2 : main.o commands_parser.o vertex.o cluster.o
	$(CC) main.o commands_parser.o vertex.o cluster.o -o Ex2

main.o : main.c consts.h command_names.h
	$(CC) $(CFLAGS)	-c main.c

commands_parser.o : commands_parser.h commands_parser.c consts.h
	$(CC) $(CFLAGS)	-c commands_parser.c

vertex.o : vertex.h vertex.c consts.h
	$(CC) $(CFLAGS)	-c vertex.c

cluster.o : cluster.h cluster.c vertex.h
	$(CC) $(CFLAGS)	-c cluster.c

clean :
	rm Ex2 main.o commands_parser.o vertex.o cluster.o
