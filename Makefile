CC = gcc
CFLAGS = -Wall -Wextra
OBJ = main.o hash_table.o menu.o

all: main

main: $(OBJ)
	$(CC) -o main $(OBJ)

main.o: main.c hash_table.h menu.h
	$(CC) $(CFLAGS) -c main.c

hash_table.o: hash_table.c hash_table.h
	$(CC) $(CFLAGS) -c hash_table.c

menu.o: menu.c menu.h hash_table.h
	$(CC) $(CFLAGS) -c menu.c

clean:
	rm -f *.o main
