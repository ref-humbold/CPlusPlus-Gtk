CC = gcc -std=gnu99
CFLAGS =  -Wall -Wextra -pthread -fPIC -shared
CMPL = $(CC) $(CFLAGS)

all : libmemalc.so

clean :
	rm -f *.so

libmemalc.so : memalc.c
	$(CMPL) memalc.c -o libmemalc.so
