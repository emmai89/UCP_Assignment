CC = gcc
CFLAGS = -Wall -pedantic -ansi -g
OBJ = spellChecker.o fileIO.o LinkedList.o stringArrayStuff.o main.o
EXEC = spellCheck

spellCheck : $(OBJ) check.o        # ckeck.o is not with the rest of the objects
	$(CC) $(OBJ) check.o -o $(EXEC)  # because the .c is not available

main.o: main.c spellChecker.c
	$(CC) -c main.c $(CFLAGS)

spellChecker.o: spellChecker.c spellChecker.h fileIO.h check.h
	$(CC) -c spellChecker.c $(CFLAGS)

LinkedList.o : LinkedList.c LinkedList.h
	$(CC) -c LinkedList.c $(CFLAGS)

fileIO.o : fileIO.c fileIO.h LinkedList.h
	$(CC) -c fileIO.c $(CFLAGS)

stringArraystuff.o: stringArraystuff.c stringArraystuff.h LinkedList.h
	$(CC) -c stringArraystuff.c $(CFLAGS)

clean:
	rm -f $(EXEC) $(OBJ)

val:
	valgrind --leak-check=full ./spellCheck test.txt

test:
	./spellCheck test.txt
