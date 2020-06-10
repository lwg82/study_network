CC := gcc
CFLAGS := -g -Wall

hello:hello.o
	$(CC) hello.o -o hello

hello.o:hello.c
	$(CC) $(CFLAGS) -c hello.c

clean:
	rm -rf hello.o hello


