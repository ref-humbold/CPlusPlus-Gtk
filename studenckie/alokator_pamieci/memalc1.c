#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>

/** struktura informacyjna bloku */
struct block
{
	size_t alloc_length;
	size_t total_length;
	struct block *next_bl;
	struct block *prev_bl;
	struct block *next_fbl;
	struct block *prev_fbl;
} __attribute__ (( aligned (16) ));

/** struktura informacyjna areny (obszaru) */
struct arena
{
	size_t alloc_length;
	size_t total_length;
	struct arena *next_ar;
	struct arena *prev_ar;
	struct block *block_list;
	struct block *freeblock_list;
} __attribute__ (( aligned (16) ));

/** struktura informująca o znalezionej arenie i bloku */
struct mem_found
{
	struct arena *ap;
	struct block *bp;
};

/** ilość wolnej przestrzeni */
long long int free_space = 0LL;

/** wskaźnik na listę aren */
struct arena *arena_list = NULL;

/** mutex */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/* ---------- FUNKCJE WYPISUJĄCE PAMIĘĆ ---------- */

/**
Funkcja wypisująca na standardowe wyjście zawartość pamięci
*/
void print_all_memory_fcn()
{
	struct arena *ar_ptr = arena_list;
	
	if(arena_list != NULL)
	{
		printf("-------------------------\nALL MEMORY (free space = %lld):\n", free_space);
	}
	
	while(ar_ptr != NULL)
	{
		struct block *bl_ptr = ar_ptr->block_list;
		
		if(bl_ptr == NULL)
		{
			if(ar_ptr->alloc_length == 0)
			{
				printf("  %p - free arena at %p -> total = %d\n", ar_ptr, (void*)ar_ptr+32, ar_ptr->total_length);
			}
			else
			{
				printf("  %p - arena at %p -> alloc = %d, total = %d\n", ar_ptr, (void*)ar_ptr+32, ar_ptr->alloc_length, ar_ptr->total_length);
			}
		}
		else
		{
			printf("  %p - arena at %p -> total = %d:\n", ar_ptr, (void*)ar_ptr+32, ar_ptr->total_length);
			
			while(bl_ptr != NULL)
			{
				if(bl_ptr->alloc_length == 0)
				{
					printf("    %p - free block at %p -> total = %d\n", bl_ptr, (void*)bl_ptr+32, bl_ptr->total_length);
				}
				else
				{
					printf("    %p - block at %p -> alloc = %d, total = %d\n", bl_ptr, (void*)bl_ptr+32, bl_ptr->alloc_length, bl_ptr->total_length);
				}
				
				bl_ptr = bl_ptr->next_bl;
			}
		}
		
		ar_ptr = ar_ptr->next_ar;
	}
	
	if(arena_list != NULL)
	{
		printf("-------------------------\n");
	}
}

/**
Funkcja wypisująca na standardowe wyjście zawartość pamięci
*/
void print_free_memory_fcn()
{
	struct arena *ar_ptr = arena_list;
	
	if(arena_list != NULL)
	{
		printf("-------------------------\nFREE MEMORY (free space = %lld):\n", free_space);
	}
	
	while(ar_ptr != NULL)
	{
		struct block *fbl_ptr = ar_ptr->freeblock_list;
		
		if(fbl_ptr == NULL)
		{
			if(ar_ptr->alloc_length == 0)
			{
				printf("  %p - free arena at %p -> total = %d\n", ar_ptr, (void*)ar_ptr+32, ar_ptr->total_length);
			}
		}
		else
		{
			printf("  %p - arena at %p -> total = %d:\n", ar_ptr, (void*)ar_ptr+32, ar_ptr->total_length);
			
			while(fbl_ptr != NULL)
			{
				printf("    %p - free block at %p -> total = %d, prev = %p, next = %p\n", fbl_ptr, (void*)fbl_ptr+32, fbl_ptr->total_length, fbl_ptr->prev_fbl, fbl_ptr->next_fbl);
				fbl_ptr = fbl_ptr->next_fbl;
			}
		}
		
		ar_ptr = ar_ptr->next_ar;
	}
	
	if(arena_list != NULL)
	{
		printf("-------------------------\n");
	}
}

/* ---------- FUNKCJE OPERUJĄCE NA PAMIĘCI ---------- */

/**
Funkcja przydzielająca pamięć o zadanym rozmiarze
@param size rozmiar
*/
void *malloc_fcn(size_t size)
{	
	
}

/**
Funkcja przydzielająca kolejne kawałki pamięci o zadanym rozmiarze
@param count liczba kawałków
@param size rozmiar pojedynczego kawałka
*/
void *calloc_fcn(size_t count, size_t size)
{
	
}

/**
Funkcja dokonująca zmiany rozmiaru już przydzielonego obszaru
@param ptr wskaźnik na przydzialony obszar
@param size nowy rozmiar obszaru
*/
void *realloc_fcn(void *ptr, size_t size)
{
	
}

/* ---------- FUNKCJE UDOSTĘPNIANE NA ZEWNĄTRZ ---------- */

extern void *malloc(size_t size)
{
	pthread_mutex_lock(&mutex);
	/* printf("MALLOC - %d\n", size); */
	
	void *adr = malloc_fcn(size);
	
	/* printf("\tMALLOC - %p\n", adr); */
	pthread_mutex_unlock(&mutex);
	
	return adr;
}

extern void *calloc(size_t count, size_t size)
{
	pthread_mutex_lock(&mutex);
	/* printf("CALLOC - %d, %d\n", count, size); */
	
	void *adr = calloc_fcn(count, size);
	
	/* printf("\tCALLOC - %p\n", adr); */
	pthread_mutex_unlock(&mutex);
	
	return adr;
}

extern void *realloc(void *ptr, size_t size)
{
	pthread_mutex_lock(&mutex);
	/* printf("REALLOC - %p, %d\n", ptr, size); */
	
	void *adr = realloc_fcn(ptr, size);
	
	/* printf("\tREALLOC - %p\n", adr); */
	pthread_mutex_unlock(&mutex);
	
	return adr;
}

extern void free(void *ptr)
{
	pthread_mutex_lock(&mutex);
	/* printf("FREE - %p\n", ptr); */
	free_fcn(ptr);
	/* printf("\tFREE\n"); */
	pthread_mutex_unlock(&mutex);
}

extern void print_all_memory()
{
	pthread_mutex_lock(&mutex);
	print_all_memory_fcn();
	pthread_mutex_unlock(&mutex);
}

extern void print_free_memory()
{
	pthread_mutex_lock(&mutex);
	print_free_memory_fcn();
	pthread_mutex_unlock(&mutex);
}

int main(int argc, char *argv[])
{
	
	return 0;
}

