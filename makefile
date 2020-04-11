CC = gcc
FLAGS = -g -o
CFLAGS = -g -Wall 
EXECUTABLE = tenis


build: BST.o files.o lists.o queue.o stack.o miscellaneous.o
	$(CC) BST.o files.o stack.o miscellaneous.o lists.o queue.o tenis.c $(FLAGS) $(EXECUTABLE)

BST.o: BST.c
files.o: files.c
lists.o: lists.c
queue.o: queue.c
stack.o: stack.c
miscellaneous.o: miscellaneous.c


clean:
	rm *.o tenis