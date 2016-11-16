$CC = gcc
$CFLAGS = -pthread -fPIC -shared -std=gnu99 -Wall -Wextra

all : libmemalc.so

clean :
	rm -f *.o

libmemalc.so : memalc.c
	$(CC) $(CFLAGS) memalc.c -o libmemalc.so

