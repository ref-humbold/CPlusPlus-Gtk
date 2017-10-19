CC = gcc -std=gnu99
CFLAGS = -pthread -fPIC -shared -Wall -Wextra

all : libmemalc.so

clean :
	rm -f *.so

libmemalc.so : memalc.c
	$(CC) $(CFLAGS) memalc.c -o libmemalc.so

