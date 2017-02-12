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
    ssize_t length;
    struct block * next_bl;
    struct block * prev_bl;
    struct block * next_fbl;
    struct block * prev_fbl;
} __attribute__ (( aligned (16) ));

/** struktura informacyjna areny (obszaru) */
struct arena
{
    ssize_t length;
    struct arena * next_ar;
    struct arena * prev_ar;
    struct block * block_list;
    struct block * freeblock_list;
} __attribute__ (( aligned (16) ));

/** struktura informująca o znalezionej arenie i bloku */
struct mem_found
{
    struct arena * ap;
    struct block * bp;
};

/** ilość wolnej przestrzeni */
long long int free_space = 0;

/** wskaźnik na listę aren */
struct arena * arena_list = NULL;

/** mutex */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/*---------- OGÓLNE FUNKCJE POMOCNICZE ----------*/

/**
Funkcja określająca faktyczny rozmiar pamięci do przydzielenia
@param size rozmiar zadeklarowany
*/
ssize_t normalize(ssize_t size)
{
    ssize_t TRH = 4*getpagesize();
    
    return size+64 > TRH ? ( (size+31+TRH)&( ~(TRH-1) ) )-32 : ( (size+15)&(~15) );
}

/**
Funkcja wyliczająca wartość bezwzględną rozmiaru
@param size rozmiar
*/
ssize_t absval(ssize_t size)
{    
    return size < 0 ? -size : size;
}

/**
Funkcja wyszukująca arenę i blok przypisane do podanego wskaźnika
@param ptr wskaźnik do odszukania
*/
struct mem_found find_pointer(void * ptr)
{
    struct mem_found mf;
    struct arena * ar_ptr = arena_list;
    
    mf.ap = NULL;
    mf.bp = NULL;
    
    while(ar_ptr != NULL)
    {
        if( (void *)ar_ptr+32 == ptr && ar_ptr->length > 0 && ar_ptr->block_list == NULL )
        {
            mf.ap = ar_ptr;
            
            return mf;
        }
        else if( (void *)ar_ptr+32 < ptr && ar_ptr->block_list != NULL
            && ( (void *)(ar_ptr->next_ar) > ptr || (void *)(ar_ptr->next_ar) == NULL ) )
        {    
            struct block * bl_ptr = ar_ptr->block_list;
            
                while(bl_ptr != NULL)
                {
                    if( (void *)bl_ptr+32 == ptr && bl_ptr->length > 0 )
                    {
                        mf.ap = ar_ptr;
                        mf.bp = bl_ptr;
                        
                        return mf;
                    }
                    else if( ( (void *)bl_ptr+32 == ptr && bl_ptr->length < 0 ) || (void *)bl_ptr+32 > ptr )
                    {
                        return mf;
                    }
                
                    bl_ptr = bl_ptr->next_bl;
                }
                
            return mf;
        }
        else if( (void *)ar_ptr+32 > ptr )
        {
            return mf;
        }
        
        ar_ptr = ar_ptr->next_ar;
    }
    
    return mf;
}

/*---------- FUNKCJE WYPISUJĄCE PAMIĘĆ ----------*/

/** Funkcja wypisująca na standardowe wyjście zawartość pamięci */
void print_all_mem_fcn()
{
    struct arena * ar_ptr = arena_list;
    
    if(arena_list != NULL)
    {
        printf("-----------------------\nALL MEMORY (free space = %lld):\n", free_space);
    }
    
    while(ar_ptr != NULL)
    {
        struct block * bl_ptr = ar_ptr->block_list;
        
        if(bl_ptr == NULL)
        {
            if(ar_ptr->length < 0)
            {
                printf( "  %p - free", ar_ptr);
            }
            else
            {
                printf( "  %p - ", ar_ptr);
            }
            
            printf( "arena at %p -> length = %d\n", (void *)ar_ptr+32, absval(ar_ptr->length) );
        }
        else
        {
            printf( "  %p - arena at %p -> length = %d:\n", ar_ptr, (void *)ar_ptr+32, absval(ar_ptr->length) );
            
            while(bl_ptr != NULL)
            {
                if(bl_ptr->length < 0)
                {
                    printf( "    %p - free ", bl_ptr);
                }
                else
                {
                    printf( "    %p - ", bl_ptr);
                }
                
                printf( "block at %p -> length = %d\n", (void *)bl_ptr+32, absval(bl_ptr->length) );
                bl_ptr = bl_ptr->next_bl;
            }
        }
        
        ar_ptr = ar_ptr->next_ar;
    }
    
    if(arena_list != NULL)
    {
        printf("-----------------------\n");
    }
}

/** Funkcja wypisująca na standardowe wyjście zawartość pamięci */
void print_free_mem_fcn()
{
    struct arena * ar_ptr = arena_list;
    
    if(arena_list != NULL)
    {
        printf("-----------------------\nFREE MEMORY (free space = %lld):\n", free_space);
    }
    
    while(ar_ptr != NULL)
    {
        struct block * fbl_ptr = ar_ptr->freeblock_list;
        
        if(fbl_ptr == NULL)
        {
            if(ar_ptr->length < 0)
            {
                printf( "  %p - free arena at %p -> length = %d\n", ar_ptr, (void *)ar_ptr+32, absval(ar_ptr->length) );
            }
        }
        else
        {
            printf( "  %p - arena at %p -> length = %d:\n", ar_ptr, (void *)ar_ptr+32, absval(ar_ptr->length) );
            
            while(fbl_ptr != NULL)
            {
                printf("    %p - free block at %p -> length = %d, prev = %p, next = %p\n",
                    fbl_ptr, (void *)fbl_ptr+32, absval(fbl_ptr->length), fbl_ptr->prev_fbl, fbl_ptr->next_fbl);
                fbl_ptr = fbl_ptr->next_fbl;
            }
        }
        
        ar_ptr = ar_ptr->next_ar;
    }
    
    if(arena_list != NULL)
    {
        printf("-----------------------\n");
    }
}


/*---------- OPERUJĄCE NA PAMIĘCI FUNKCJE POMOCNICZE ----------*/

/**
Funkcja zapisująca pola struktury bloku
@param bl_ptr wskaźnik na blok
@param ln długość bloku
@param prevb wskaźnik na poprzedni blok
@param nextb wskaźnik na następny blok
@param prevf wskaźnik na poprzedni wolny blok
@param nextf wskaźnik na następny wolny blok
*/
void set_block_fds(struct block * bl_ptr, ssize_t ln, struct block * prevb, struct block * nextb,
    struct block * prevf, struct block * nextf)
{
    bl_ptr->length = ln;
    bl_ptr->prev_bl = prevb;
    bl_ptr->next_bl = nextb;
    bl_ptr->prev_fbl = prevf;
    bl_ptr->next_fbl = nextf;
}

/**
Funkcja zapisująca pola struktury areny
@param ar_ptr wskaźnik na blok
@param ln długość bloku
@param preva wskaźnik na poprzednią arenę
@param nexta wskaźnik na następną arenę
@param blist wskaźnik na pierszy blok listy
@param flist wskaźnik na pierszy wolny blok listy
*/
void set_arena_fds(struct arena * ar_ptr, ssize_t ln, struct arena * preva, struct arena * nexta,
    struct block * blist, struct block * flist)
{
    ar_ptr->length = ln;
    ar_ptr->prev_ar = preva;
    ar_ptr->next_ar = nexta;
    ar_ptr->block_list = blist;
    ar_ptr->freeblock_list = flist;
}

/**
Funkcja przepinająca wskaźniki wolnych bloków
@param ar_ptr wskaźnik na arenę
@param bl_ptr wskaźnik na blok
@param prev_of_next poprzedni wskaźnik dla następnego
@param next_of_prev następny wskaźnik dla poprzedniego
*/
void switch_fblock_ptrs(struct arena * ar_ptr, struct block * bl_ptr, struct block * prev_of_next,
    struct block * next_of_prev)
{
    if(bl_ptr->next_fbl != NULL)
    {
        bl_ptr->next_fbl->prev_fbl = prev_of_next;
    }
    
    if(ar_ptr != NULL)
    {
        if(bl_ptr->prev_fbl != NULL)
        {
            bl_ptr->prev_fbl->next_fbl = next_of_prev;
        }
        else
        {
            ar_ptr->freeblock_list = next_of_prev;
        }
    }
}

/**
Funkcja przepinająca wskaźniki bloków
@param ar_ptr wskaźnik na arenę
@param bl_ptr wskaźnik na blok
@param prev_of_next poprzedni wskaźnik dla następnego
@param next_of_prev następny wskaźnik dla poprzedniego
*/
void switch_block_ptrs(struct arena * ar_ptr, struct block * bl_ptr, struct block * prev_of_next,
    struct block * next_of_prev)
{
    if(bl_ptr->next_bl != NULL)
    {
        bl_ptr->next_bl->prev_bl = prev_of_next;
    }

    if(ar_ptr != NULL)
    {
        if(bl_ptr->prev_bl != NULL)
        {
            bl_ptr->prev_bl->next_bl = next_of_prev;
        }
        else
        {
            ar_ptr->block_list = next_of_prev;
        }
    }
}

/**
Funkcja przepinająca wskaźniki aren
@param ar_fw_ptr wskaźnik na następną arenę
@param ar_bk_ptr wskaźnik na poprzednią arenę
@param prev_of_fw poprzedni wskaźnik dla następnego
@param next_of_bk następny wskaźnik dla poprzedniego
*/
void switch_arena_ptrs(struct arena * ar_fw_ptr, struct arena * ar_bk_ptr, struct arena * prev_of_fw,
    struct arena * next_of_bk)
{
    if(ar_fw_ptr != NULL)
    {
        ar_fw_ptr->prev_ar = prev_of_fw;
    }
    
    if(ar_bk_ptr != NULL)
    {
        ar_bk_ptr->next_ar = next_of_bk;
    }
    else
    {
        arena_list = next_of_bk;
    }
}

/**
Funkcja przydzielająca pamięć bloku
@param ar_ptr wskaźnik na arenę
@param bl_ptr wskaźnik na blok
@param ln rozmiar do alokacji
@param will_be_free czy blok będzie wolny
*/
void * alloc_to_block(struct arena * ar_ptr, struct block * bl_ptr, ssize_t ln, int will_be_free)
{                    
    if(absval(bl_ptr->length) >= ln+32+16)
    {
        struct block * new_block = (void *)bl_ptr+32+ln;
        
        switch_fblock_ptrs(ar_ptr, bl_ptr, new_block, new_block);
        switch_block_ptrs(NULL, bl_ptr, new_block, NULL);
        
        set_block_fds(new_block, -(absval(bl_ptr->length)-ln-32), bl_ptr, bl_ptr->next_bl, bl_ptr->prev_fbl,
            bl_ptr->next_fbl);
        
        if(will_be_free == 0)
        {
            set_block_fds(bl_ptr, ln, bl_ptr->prev_bl, new_block, NULL, NULL);
            
            free_space = free_space-32-absval(bl_ptr->length);
        }
        else
        {
            set_block_fds(bl_ptr, ln, bl_ptr->prev_bl, new_block, bl_ptr->prev_fbl, new_block);
            
            free_space = free_space+absval(new_block->length);
        }
    }
    else
    {
        switch_fblock_ptrs(ar_ptr, bl_ptr, bl_ptr->prev_fbl, bl_ptr->next_fbl);
        set_block_fds(bl_ptr, ln, bl_ptr->prev_bl, bl_ptr->next_bl, NULL, NULL);
        
        free_space = free_space-absval(bl_ptr->length);
    }
    
    void * ret = (void *)bl_ptr+32;
    
    return ret;
}

/**
Funkcja przydzielająca pamięć areny
@param ar_back_ptr wskaźnik na poprzednią arenę
@param ar_forw_ptr wskaźnik na następną arenę
@param ln - rozmiar do alokacji
@param alc_block czy przydzielamy z blokami
*/
void * alloc_to_arena(struct arena * ar_back_ptr, struct arena * ar_forw_ptr, ssize_t ln, int alc_block)
{
    void * adr = mmap(NULL, ln, (PROT_READ | PROT_WRITE), (MAP_ANONYMOUS | MAP_PRIVATE), -1, 0);
    struct arena * ar_ptr = adr;
        
    while(ar_back_ptr != NULL && ar_back_ptr>ar_ptr)
    {
        ar_forw_ptr = ar_back_ptr;
        ar_back_ptr = ar_back_ptr->prev_ar;
    }
    
    switch_arena_ptrs(ar_forw_ptr, ar_back_ptr, ar_ptr, ar_ptr);
    
    if(alc_block == 0)
    {
        set_arena_fds(ar_ptr, ln-32, ar_back_ptr, ar_forw_ptr, NULL, NULL);
    }
    else
    {
        set_arena_fds(ar_ptr, ln-32, ar_back_ptr, ar_forw_ptr, adr+32, adr+32);
        adr = adr+32;
        
        struct block * bl_str=adr;
        
        set_block_fds(bl_str, -ln+64, NULL, NULL, NULL, NULL);
        
        free_space = free_space+absval(bl_str->length);
    }
    
    void * ret = (void *)ar_ptr+32;
    
    return ret;
}

/**
Funkcja dołączająca wolny blok
@param ar_ptr wskaźnik na arenę
@param fst_bl_ptr wskaźnik na blok, do którego przyłączamy
@param snd_fbl_ptr wskaźnik na wolny blok, który będziemy przyłączać
@param fst_free czy pierwszy blok jest wolny
*/
void concat_blocks(struct arena * ar_ptr, struct block * fst_bl_ptr, struct block * snd_fbl_ptr, int fst_free)
{    
    if(fst_bl_ptr != NULL && snd_fbl_ptr != NULL && fst_bl_ptr->next_bl == snd_fbl_ptr)
    {        
        if(fst_free == 0)
        {
            free_space = free_space+32+absval(fst_bl_ptr->length);
            
            set_block_fds(fst_bl_ptr, -( absval(fst_bl_ptr->length)+32+absval(snd_fbl_ptr->length) ),
                fst_bl_ptr->prev_bl, snd_fbl_ptr->next_bl, snd_fbl_ptr->prev_fbl, snd_fbl_ptr->next_fbl);
            
            switch_block_ptrs(NULL, snd_fbl_ptr, fst_bl_ptr, NULL);
            switch_fblock_ptrs(ar_ptr, snd_fbl_ptr, fst_bl_ptr, fst_bl_ptr);
        }
        else
        {
            free_space = free_space+32;
            
            set_block_fds(fst_bl_ptr, -( absval(fst_bl_ptr->length)+32+absval(snd_fbl_ptr->length) ),
                fst_bl_ptr->prev_bl, snd_fbl_ptr->next_bl, fst_bl_ptr->prev_fbl, snd_fbl_ptr->next_fbl);
            
            switch_block_ptrs(NULL, snd_fbl_ptr, fst_bl_ptr, NULL);
            switch_fblock_ptrs(NULL, snd_fbl_ptr, fst_bl_ptr, NULL);
        }
    }
    else if(fst_bl_ptr != NULL && snd_fbl_ptr != NULL)
    {
        fst_bl_ptr->next_fbl = snd_fbl_ptr;
        snd_fbl_ptr->prev_fbl = fst_bl_ptr;
    }
    else if(fst_bl_ptr != NULL && snd_fbl_ptr == NULL && fst_free == 0)
    {
        fst_bl_ptr->next_fbl = NULL;
    }
    else if(fst_bl_ptr == NULL && snd_fbl_ptr != NULL && fst_free != 0)
    {
        snd_fbl_ptr->prev_fbl = NULL;
        ar_ptr->freeblock_list = snd_fbl_ptr;
    }
    
    return;
}

/**
Funkcja powiększająca rozmiar i przesuwająca bloki
@param ar_ptr wskaźnik na arenę
@param rs_bl_ptr wskaźnik na blok powiększany
@param mv_bl_ptr wskaźnik na blok przesuwany
@param ln nowy rozmiar
*/
void * resize_and_move(struct arena * ar_ptr, struct block * rs_bl_ptr, struct block * mv_bl_ptr, ssize_t ln)
{
    if(absval(rs_bl_ptr->length)+32+absval(mv_bl_ptr->length) >= ln+32+16)
    {
        struct block * new_block = (void *)rs_bl_ptr+32+ln;
        struct block mvbl = (*mv_bl_ptr);
        
        switch_fblock_ptrs(ar_ptr, &mvbl, new_block, new_block);
        
        set_block_fds(new_block, -(absval(rs_bl_ptr->length)+absval(mvbl.length)-ln), rs_bl_ptr, mvbl.next_bl,
            mvbl.prev_fbl, mvbl.next_fbl);
        set_block_fds(rs_bl_ptr, ln, rs_bl_ptr->prev_bl, new_block, rs_bl_ptr->prev_fbl, new_block);
        
        free_space = free_space-absval(mvbl.length)+absval(new_block->length);
    }
    else
    {
        set_block_fds(rs_bl_ptr, absval(rs_bl_ptr->length)+32+absval(mv_bl_ptr->length), rs_bl_ptr->prev_bl,
            mv_bl_ptr->next_bl, rs_bl_ptr->prev_fbl, rs_bl_ptr->next_fbl);
        
        switch_block_ptrs(NULL, mv_bl_ptr, rs_bl_ptr, NULL);
        switch_fblock_ptrs(ar_ptr, mv_bl_ptr, mv_bl_ptr->prev_fbl, mv_bl_ptr->next_fbl);
    }
    
    void * ret = (void *)rs_bl_ptr+32;
    
    return ret;
}

/*---------- FUNKCJE OPERUJĄCE NA PAMIĘCI ----------*/

/**
Funkcja zwalniająca pamięć spod danego wskaźnika
@param ptr wskaźnik
*/
void free_fcn(void * ptr)
{
    if(ptr == NULL || ptr < (void *)arena_list)
    {
        return;
    }
    
    struct mem_found mf = find_pointer(ptr);
    struct arena * ar_ptr = mf.ap;
    struct block * bl_ptr = mf.bp;
    
    if(ar_ptr == NULL && bl_ptr == NULL)
    {
        return;
    }
    
    if(bl_ptr == NULL)
    {
        ar_ptr->length = -ar_ptr->length;
        free_space = free_space+absval(ar_ptr->length);
    }
    else
    {
        struct block * back_fbl = NULL;
        struct block * forw_fbl = ar_ptr->freeblock_list;
        
        bl_ptr->length = -bl_ptr->length;
        free_space = free_space+absval(bl_ptr->length);
        
        while(forw_fbl != NULL && (void *)forw_fbl < (void *)bl_ptr)
        {
            back_fbl = forw_fbl;
            forw_fbl = forw_fbl->next_fbl;
        }
        
        concat_blocks(ar_ptr, bl_ptr, forw_fbl, 0);
        concat_blocks(ar_ptr, back_fbl, bl_ptr, 1);
    }
    
    ssize_t TRH = 4*getpagesize();
    
    if(free_space > 2*TRH)
    {
        struct arena * del_ptr = arena_list;
        
        while(del_ptr != NULL)
        {
            if( del_ptr->length < 0
                || (del_ptr->freeblock_list != NULL && absval(del_ptr->freeblock_list->length) == TRH-64) )
            {
                ssize_t ln = absval(del_ptr->length);
                void * ptr = del_ptr;
                
                switch_arena_ptrs(del_ptr->next_ar, del_ptr->prev_ar, del_ptr->prev_ar, del_ptr->next_ar);
                
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
void * malloc_fcn(size_t size)
{    
    if(size == 0)
    {
        return NULL;
    }
    
    ssize_t norm_size = normalize(size), TRH = 4*getpagesize();
    struct arena * ar_forw_ptr = arena_list;
    struct arena * ar_back_ptr = NULL;
    
    if(norm_size+64 > TRH)
    {        
        while(ar_forw_ptr != NULL)
        {            
            if(ar_forw_ptr->length < 0 && ar_forw_ptr->block_list == NULL && absval(ar_forw_ptr->length) >= norm_size)
            {
                ar_forw_ptr->length = absval(ar_forw_ptr->length);
                
                free_space = free_space-absval(ar_forw_ptr->length);
                
                void * ret = (void *)ar_forw_ptr+32;
                
                return ret;
            }
                    
            ar_back_ptr = ar_forw_ptr;
            ar_forw_ptr = ar_forw_ptr->next_ar;
        }
        
        return alloc_to_arena(ar_back_ptr, ar_forw_ptr, norm_size+32, 0);
    }
    else
    {
        while(ar_forw_ptr != NULL)
        {        
            if(ar_forw_ptr->freeblock_list != NULL)
            {
                struct block * bl_ptr = ar_forw_ptr->freeblock_list;
                
                while(bl_ptr != NULL)
                {                    
                    if(absval(bl_ptr->length) >= norm_size)
                    {
                        void * ret = alloc_to_block(ar_forw_ptr, bl_ptr, norm_size, 0);
                        
                        return ret;
                    }
                    
                    bl_ptr = bl_ptr->next_fbl;
                }
            }
        
            ar_back_ptr = ar_forw_ptr;
            ar_forw_ptr = ar_forw_ptr->next_ar;
        }
        
        void * adr = alloc_to_arena(ar_back_ptr, ar_forw_ptr, TRH, 1);
        struct arena * ar_ptr = adr-32;
        struct block * bl_str = adr;
        
        return alloc_to_block(ar_ptr, bl_str, norm_size, 0);
    }
}

/**
Funkcja przydzielająca kolejne kawałki pamięci o zadanym rozmiarze
@param count liczba kawałków
@param size rozmiar pojedynczego kawałka
*/
void * calloc_fcn(size_t count, size_t size)
{
    if(count == 0 || size == 0)
    {
        return NULL;
    }
    
    size_t norm_size = normalize(count*size);
    void * ret = malloc_fcn(count*size);    
    ret = memset(ret, 0, norm_size);
    
    return ret;
}

/**
Funkcja tworząca całkowicie nowy blok i przenosząca do niego zawartość
@param ar_ptr wskaźnik na arenę
@param bl_ptr wskaźnik na blok
@param del_ptr wskaźnik do zwolnienia
@param ln nowy rozmiar
*/
void * alloc_and_move(struct arena * ar_ptr, struct block * bl_ptr, void * del_ptr, ssize_t ln)
{
    void * ret = malloc_fcn( absval(ln) );
    
    if(ar_ptr != NULL)
    {
        ret = memmove( ret, (void *)ar_ptr+32, absval(ar_ptr->length) );
    }
    else
    {
        ret = memmove( ret, (void *)bl_ptr+32, absval(bl_ptr->length) );
    }
    
    free_fcn(del_ptr);
    
    return ret;
}

/**
Funkcja dokonująca zmiany rozmiaru już przydzielonego obszaru
@param ptr wskaźnik na przydzialony obszar
@param size nowy rozmiar obszaru
*/
void * realloc_fcn(void * ptr, size_t size)
{
    if(ptr == NULL && size == 0)
    {
        return NULL;
    }
    
    if(ptr == NULL)
    {
        return malloc_fcn(size);
    }
    
    if(size == 0)
    {
        free_fcn(ptr);
        
        return NULL;
    }
    
    void * ret;
    ssize_t norm_size = normalize(size);
    struct mem_found mf = find_pointer(ptr);
    struct arena * ar_ptr = mf.ap;
    struct block * bl_ptr = mf.bp;
    
    if(ar_ptr == NULL && bl_ptr == NULL)
    {
        return NULL;
    }
    
    if(bl_ptr == NULL)
    {
        if(absval(ar_ptr->length) < norm_size)
        {
            alloc_and_move(ar_ptr, NULL, ptr, size);
        }
        else
        {
            ret = (void *)ar_ptr+32;
        }
    }
    else
    {
        if(norm_size+64 > 4*getpagesize())
        {
            ret = alloc_and_move(NULL, bl_ptr, ptr, size);
        }
        else if(absval(bl_ptr->length) >= norm_size+32+16)
        {            
            ret = alloc_to_block(ar_ptr, bl_ptr, norm_size, 1);
        }
        else if( norm_size>absval(bl_ptr->length) )
        {
            struct block * forw_bl = bl_ptr->next_bl;
            
            if(forw_bl != NULL && forw_bl->length < 0 && absval(bl_ptr->length)+32+absval(forw_bl->length) >= norm_size)
            {
                ret = resize_and_move(ar_ptr, bl_ptr, forw_bl, norm_size);
            }
            else
            {
                ret = alloc_and_move(NULL, bl_ptr, ptr, size);
            }
        }
        else
        {
            ret = (void *)bl_ptr+32;
        }
    }
    
    return ret;
}

/*---------- FUNKCJE UDOSTĘPNIANE NA ZEWNĄTRZ ----------*/

void * malloc(size_t size)
{
    pthread_mutex_lock(&mutex);
    /* printf("MALLOC - %d\n", size); */
    
    void * adr = malloc_fcn(size);
    
    /* printf("\tMALLOC - %p\n", adr); */
    pthread_mutex_unlock(&mutex);
    
    return adr;
}

void * calloc(size_t count, size_t size)
{
    pthread_mutex_lock(&mutex);
    /* printf("CALLOC - %d, %d\n", count, size); */
    
    void * adr = calloc_fcn(count, size);
    
    /* printf("\tCALLOC - %p\n", adr); */
    pthread_mutex_unlock(&mutex);
    
    return adr;
}

void * realloc(void * ptr, size_t size)
{
    pthread_mutex_lock(&mutex);
    /* printf("REALLOC - %p, %d\n", ptr, size); */
    
    void * adr = realloc_fcn(ptr, size);
    
    /* printf("\tREALLOC - %p\n", adr); */
    pthread_mutex_unlock(&mutex);
    
    return adr;
}

void free(void * ptr)
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
    print_all_mem_fcn();
    pthread_mutex_unlock(&mutex);
}

void print_free_memory()
{
    pthread_mutex_lock(&mutex);
    print_free_mem_fcn();
    pthread_mutex_unlock(&mutex);
}

int main(int argc, char *argv[])
{
    
    return 0;
}

