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
    struct arena *arena_adr;
    struct block *block_adr;
};

/** ilość wolnej przestrzeni */
long long int free_space = 0LL;

/** wskaźnik na listę aren */
struct arena *arena_list = NULL;

/** mutex */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

--/* ---- ------OGÓLNE FUNKCJE POMOCNICZE ---- ----*/

/**
Funkcja określająca faktyczny rozmiar pamięci do przydzielenia
@param size rozmiar zadeklarowany
*/
size_t normalise(size_t size)
{
    size_t TRH = 4*getpagesize();
    
    return size+64 > TRH ? ( (size+31+TRH)&( ~(TRH-1) ) )-32 : ( (size+15)&(~15) );
}

/**
Funkcja wyszukująca arenę i blok przypisane do podanego wskaźnika
@param ptr wskaźnik do odszukania
@return wskaźniki do areny i bloku pamięci
*/
struct memory_found find_pointer(void *ptr)
{
    struct memory_found mf;
    struct arena *ar_ptr = arena_list;
    
    mf.arena_adr = NULL;
    mf.block_adr = NULL;
    
    while(ar_ptr != NULL)
    {
        if( (void*)ar_ptr+32 == ptr && ar_ptr->alloc_length > 0 && ar_ptr->block_list == NULL )
        {
            mf.arena_adr = ar_ptr;
            return mf;
        }
        else if( (void*)ar_ptr+32<ptr && ar_ptr->block_list != NULL && ( (void*)(ar_ptr->next_ar) > ptr || (void*)(ar_ptr->next_ar) == NULL ) )
        {    
            struct block *bl_ptr = ar_ptr->block_list;
            
                while(bl_ptr != NULL)
                {
                    if( (void*)bl_ptr+32 == ptr && bl_ptr->alloc_length > 0 )
                    {
                        mf.arena_adr = ar_ptr;
                        mf.block_adr = bl_ptr;
                        
                        return mf;
                    }
                    else if( ( (void*)bl_ptr+32 == ptr && bl_ptr->alloc_length == 0 ) || (void*)bl_ptr+32 > ptr )
                    {
                        return mf;
                    }
                
                    bl_ptr = bl_ptr->next_bl;
                }
                
            return mf;
        }
        else if( (void*)ar_ptr+32 > ptr )
        {
            return mf;
        }
        
        ar_ptr = ar_ptr->next_ar;
    }
    
    return mf;
}

--/* ---- ------FUNKCJE WYPISUJĄCE PAMIĘĆ ---- ----*/

/**
Funkcja wypisująca na standardowe wyjście zawartość pamięci
*/
void print_all_memory_fcn()
{
    struct arena *ar_ptr = arena_list;
    
    if(arena_list != NULL)
    {
        --printf("-----------------------\nALL MEMORY (free space = %lld):\n", free_space);
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
        --printf("-----------------------\n");
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
        --printf("-----------------------\nFREE MEMORY (free space = %lld):\n", free_space);
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
        --printf("-----------------------\n");
    }
}

--/* ---- ------OPERUJĄCE NA PAMIĘCI FUNKCJE POMOCNICZE ---- ----*/

/**
Funkcja przydzielająca pamięć bloku
@param ar_ptr wskaźnik na arenę
@param bl_ptr wskaźnik na blok
@param norm_size rozmiar do alokacji
@param user_size rozmiar użytkownika
@return wskaźnik do przydzielonego bloku
*/
void *alloc_to_block(struct arena *ar_ptr, struct block *bl_ptr, size_t norm_size, size_t user_size)
{                    
    if(bl_ptr->total_length >= norm_size+32+16)
    {
        struct block *new_block = (void*)bl_ptr+32+norm_size;
        
        if(bl_ptr->next_fbl != NULL)
        {
            bl_ptr->next_fbl->prev_fbl = new_block;
        }
    
        if(bl_ptr->prev_fbl != NULL)
        {
            bl_ptr->prev_fbl->next_fbl = new_block;
        }
        else
        {
            ar_ptr->freeblock_list = new_block;
        }
        
        if(bl_ptr->next_bl != NULL)
        {
            bl_ptr->next_bl->prev_bl = new_block;
        }
        
        new_block->alloc_length = 0;
        new_block->total_length = bl_ptr->total_length-norm_size-32;
        new_block->next_bl = bl_ptr->next_bl;
        new_block->prev_bl = bl_ptr;
        new_block->next_fbl = bl_ptr->next_fbl;
        new_block->prev_fbl = bl_ptr->prev_fbl;
        
        bl_ptr->alloc_length = user_size;
        bl_ptr->total_length = norm_size;
        bl_ptr->next_bl = new_block;
        bl_ptr->next_fbl = NULL;
        bl_ptr->prev_fbl = NULL;
        
        free_space = free_space-32-bl_ptr->total_length;
    }
    else
    {
        if(bl_ptr->next_fbl != NULL)
        {
            bl_ptr->next_fbl->prev_fbl = bl_ptr->prev_fbl;
        }
    
        if(bl_ptr->prev_fbl != NULL)
        {
            bl_ptr->prev_fbl->next_fbl = bl_ptr->next_fbl;
        }
        else
        {
            ar_ptr->freeblock_list = bl_ptr->next_fbl;
        }
        
        bl_ptr->alloc_length = user_size;
        bl_ptr->next_fbl = NULL;
        bl_ptr->prev_fbl = NULL;
        
        free_space = free_space-bl_ptr->total_length;
    }
    
    void *return_adr = (void*)bl_ptr+32;
    
    return return_adr;
}

--/* ---- ------FUNKCJE OPERUJĄCE NA PAMIĘCI ---- ----*/

/**
Funkcja zwalniająca pamięć spod danego wskaźnika
@param ptr wskaźnik
*/
void free_fcn(void *ptr)
{
    if(ptr == NULL || ptr < (void*)arena_list)
    {
        return;
    }
    
    struct memory_found found = find_pointer(ptr);
    struct arena *ar_ptr = found.arena_adr;
    struct block *bl_ptr = found.block_adr;
    
    if(ar_ptr == NULL && bl_ptr == NULL)
    {
        return;
    }
    
    if(bl_ptr == NULL)
    {
        ar_ptr->alloc_length = 0;
        free_space = free_space+ar_ptr->total_length;
    }
    else
    {
        struct block *back_fbl = NULL;
        struct block *forw_fbl = ar_ptr->freeblock_list;
        
        bl_ptr->alloc_length = 0;
        free_space = free_space+bl_ptr->total_length;
        
        while(forw_fbl != NULL && (void*)forw_fbl < (void*)bl_ptr)
        {
            back_fbl = forw_fbl;
            forw_fbl = forw_fbl->next_fbl;
        }
        
        if(forw_fbl != NULL && forw_fbl == bl_ptr->next_bl)
        {
            bl_ptr->alloc_length = 0;
            bl_ptr->total_length = bl_ptr->total_length+32+forw_fbl->total_length;
            bl_ptr->next_bl = forw_fbl->next_bl;
            bl_ptr->next_fbl = forw_fbl->next_fbl;
            bl_ptr->prev_fbl = forw_fbl->prev_fbl;
            free_space = free_space+32;
            
            if(forw_fbl->next_bl != NULL)
            {
                forw_fbl->next_bl->prev_bl = bl_ptr;
            }
            
            if(forw_fbl->next_fbl != NULL)
            {
                forw_fbl->next_fbl->prev_fbl = bl_ptr;
            }
            
            if(forw_fbl->prev_fbl != NULL)
            {
                forw_fbl->prev_fbl->next_fbl = bl_ptr;
            }
        }
        else if(forw_fbl != NULL)
        {
            bl_ptr->next_fbl = forw_fbl;
            forw_fbl->prev_fbl = bl_ptr;
        }
        else
        {
            bl_ptr->next_fbl = NULL;
        }
        
        if(back_fbl != NULL && back_fbl == bl_ptr->prev_bl)
        {
            back_fbl->alloc_length = 0;
            back_fbl->total_length = back_fbl->total_length+32+bl_ptr->total_length;
            back_fbl->next_bl = bl_ptr->next_bl;
            back_fbl->next_fbl = bl_ptr->next_fbl;
            free_space = free_space+32;
            
            if(bl_ptr->next_bl != NULL)
            {
                bl_ptr->next_bl->prev_bl = back_fbl;
            }
            
            if(bl_ptr->next_fbl != NULL)
            {
                bl_ptr->next_fbl->prev_fbl = back_fbl;
            }
        }
        else if(back_fbl != NULL)
        {
            bl_ptr->prev_fbl = back_fbl;
            back_fbl->next_fbl = bl_ptr;
        }
        else
        {
            bl_ptr->prev_fbl = NULL;
            ar_ptr->freeblock_list = bl_ptr;
        }
    }
    
    size_t TRH = 4*getpagesize();
    
    if(free_space > 2*TRH)
    {
        struct arena *del_ptr = arena_list;
        
        while(del_ptr != NULL)
        {
            if( del_ptr->alloc_length == 0 || (del_ptr->freeblock_list != NULL && del_ptr->freeblock_list->total_length == TRH-64) )
            {
                size_t ln = del_ptr->total_length;
                void *ptr = del_ptr;
                
                if(del_ptr->next_ar != NULL)
                {
                    del_ptr->next_ar->prev_ar = del_ptr->prev_ar;
                }
                
                if(del_ptr->prev_ar != NULL)
                {
                    del_ptr->prev_ar->next_ar = del_ptr->next_ar;
                }
                else
                {
                    arena_list = del_ptr->next_ar;
                }
                
                del_ptr = del_ptr->next_ar;
                free_space = free_space-ln;
                munmap(ptr, ln+32);
            }
            else
            {
                del_ptr = del_ptr->next_ar;
            }
        }
    }
    
    return;
}

/**
Funkcja przydzielająca pamięć o zadanym rozmiarze
@param size rozmiar
*/
void *malloc_fcn(size_t size)
{    
    if(size == 0)
    {
        return NULL;
    }

    void *return_adr;
    size_t norm_size = normalise(size), TRH = 4*getpagesize();
    struct arena *ar_forw_ptr = arena_list;
    struct arena *ar_back_ptr = NULL;
    
    if(norm_size+64 > TRH)
    {
        while(ar_forw_ptr != NULL)
        {            
            if(ar_forw_ptr->alloc_length == 0 && ar_forw_ptr->block_list == NULL && ar_forw_ptr->total_length >= norm_size)
            {
                ar_forw_ptr->alloc_length = size;
                
                free_space = free_space-ar_forw_ptr->total_length;
                
                return_adr = (void*)ar_forw_ptr+32;
                
                return return_adr;
            }
                    
            ar_back_ptr = ar_forw_ptr;
            ar_forw_ptr = ar_forw_ptr->next_ar;
        }
        
        void *map_adr = mmap(NULL, norm_size+32, (PROT_READ | PROT_WRITE), (MAP_ANONYMOUS | MAP_PRIVATE), -1, 0);
        struct arena *ar_ptr = map_adr;
        
        while(ar_back_ptr != NULL && ar_back_ptr > ar_ptr)
        {
            ar_forw_ptr = ar_back_ptr;
            ar_back_ptr = ar_back_ptr->prev_ar;
        }
            
        if(ar_back_ptr != NULL)
        {
            ar_back_ptr->next_ar = ar_ptr;
        }
        else
        {
            arena_list = ar_ptr;
        }
        
        if(ar_forw_ptr != NULL)
        {
            ar_forw_ptr->prev_ar = ar_ptr;
        }
        
        ar_ptr->alloc_length = size;
        ar_ptr->total_length = norm_size;
        ar_ptr->next_ar = ar_forw_ptr;
        ar_ptr->prev_ar = ar_back_ptr;
        ar_ptr->block_list = NULL;
        ar_ptr->freeblock_list = NULL;
        
        return_adr = (void*)ar_ptr+32;
        
        return return_adr;
    }
    else
    {
        while(ar_forw_ptr != NULL)
        {        
            if(ar_forw_ptr->freeblock_list != NULL)
            {
                struct block *fbl_ptr = ar_forw_ptr->freeblock_list;
                
                while(fbl_ptr != NULL)
                {                    
                    if(fbl_ptr->total_length >= norm_size)
                    {
                        return_adr = alloc_to_block(ar_forw_ptr, fbl_ptr, norm_size, size);
                        
                        return return_adr;
                    }
                    
                    fbl_ptr = fbl_ptr->next_fbl;
                }
            }
        
            ar_back_ptr = ar_forw_ptr;
            ar_forw_ptr = ar_forw_ptr->next_ar;
        }
        
        void *map_adr = mmap(NULL, TRH, (PROT_READ | PROT_WRITE), (MAP_ANONYMOUS | MAP_PRIVATE), -1, 0);
        struct arena *ar_ptr = map_adr;
        
        while(ar_back_ptr != NULL && ar_back_ptr > ar_ptr)
        {
            ar_forw_ptr = ar_back_ptr;
            ar_back_ptr = ar_back_ptr->prev_ar;
        }
            
        if(ar_back_ptr != NULL)
        {
            ar_back_ptr->next_ar = ar_ptr;
        }
        else
        {
            arena_list = ar_ptr;
        }
        
        if(ar_forw_ptr != NULL)
        {
            ar_forw_ptr->prev_ar = ar_ptr;
        }
        
        ar_ptr->alloc_length = TRH-32;
        ar_ptr->total_length = TRH-32;
        ar_ptr->next_ar = ar_forw_ptr;
        ar_ptr->prev_ar = ar_back_ptr;
        ar_ptr->block_list = adr+32;
        ar_ptr->freeblock_list = adr+32;
        
        map_adr = map_adr+32;
        
        struct block *bl_ptr = map_adr;
        
        bl_ptr->alloc_length = 0;
        bl_ptr->total_length = TRH-64;
        bl_ptr->next_bl = NULL;
        bl_ptr->prev_bl = NULL;
        bl_ptr->next_fbl = NULL;
        bl_ptr->prev_fbl = NULL;
        
        free_space = free_space+bl_ptr->total_length;
        
        return_adr = alloc_to_block(ar_ptr, bl_ptr, norm_size, size);
        
        return return_adr;
    }
}

/**
Funkcja przydzielająca kolejne kawałki pamięci o zadanym rozmiarze
@param count liczba kawałków
@param size rozmiar pojedynczego kawałka
*/
void *calloc_fcn(size_t count, size_t size)
{
    if(count == 0 || size == 0)
    {
        return NULL;
    }
    
    size_t norm_size = normalise(count*size);
    void *ret = malloc_fcn(count*size);    
    
    ret = memset(ret, 0, norm_size);
    
    return ret;
}

/**
Funkcja dokonująca zmiany rozmiaru już przydzielonego obszaru
@param ptr wskaźnik na przydzialony obszar
@param size nowy rozmiar obszaru
*/
void *realloc_fcn(void *ptr, size_t size)
{
    
}

--/* ---- ------FUNKCJE UDOSTĘPNIANE NA ZEWNĄTRZ ---- ----*/

void *malloc(size_t size)
{
    pthread_mutex_lock(&mutex);
    /* printf("MALLOC - %d\n", size); */
    
    void *adr = malloc_fcn(size);
    
    /* printf("\tMALLOC - %p\n", adr); */
    pthread_mutex_unlock(&mutex);
    
    return adr;
}

void *calloc(size_t count, size_t size)
{
    pthread_mutex_lock(&mutex);
    /* printf("CALLOC - %d, %d\n", count, size); */
    
    void *adr = calloc_fcn(count, size);
    
    /* printf("\tCALLOC - %p\n", adr); */
    pthread_mutex_unlock(&mutex);
    
    return adr;
}

void *realloc(void *ptr, size_t size)
{
    pthread_mutex_lock(&mutex);
    /* printf("REALLOC - %p, %d\n", ptr, size); */
    
    void *adr = realloc_fcn(ptr, size);
    
    /* printf("\tREALLOC - %p\n", adr); */
    pthread_mutex_unlock(&mutex);
    
    return adr;
}

void free(void *ptr)
{
    pthread_mutex_lock(&mutex);
    /* printf("FREE - %p\n", ptr); */
    free_fcn(ptr);
    /* printf("\tFREE\n"); */
    pthread_mutex_unlock(&mutex);
}

void print_all_memory()
{
    pthread_mutex_lock(&mutex);
    print_all_memory_fcn();
    pthread_mutex_unlock(&mutex);
}

void print_free_memory()
{
    pthread_mutex_lock(&mutex);
    print_free_memory_fcn();
    pthread_mutex_unlock(&mutex);
}

int main(int argc, char *argv[])
{
    
    return 0;
}

