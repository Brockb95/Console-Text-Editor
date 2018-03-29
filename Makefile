#files: edit.h, edit.c, main.c
CC=gcc
LIBS=-lncurses

main: main.o edit.o
	$(CC) -o main main.o edit.o $(LIBS)
main.o: main.c
	$(CC) -c main.c 
edit.o: edit.c
	$(CC) -c edit.c
clean:
	rm -rf main *.o
