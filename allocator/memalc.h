#ifndef MEMALC_H
#define MEMALC_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>

void * malloc(size_t size);

void * calloc(size_t count, size_t size);

void * realloc(void * ptr, size_t size);

void free(void * ptr);

void print_all_memory();

void print_free_memory();

#endif
