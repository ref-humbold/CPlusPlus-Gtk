#include "memalc.h"

#define ARENA struct arena
#define BLOCK struct block
#define PLACE struct memory_place
#define ARENA_PTR ARENA *
#define BLOCK_PTR BLOCK *
#define PTR void *

/// Block structure
struct block
{
    ssize_t length;
    BLOCK_PTR next;
    BLOCK_PTR prev;
    BLOCK_PTR next_free;
    BLOCK_PTR prev_free;
} __attribute__((aligned(16)));

/// Arena structure
struct arena
{
    ssize_t length;
    ARENA_PTR next;
    ARENA_PTR prev;
    BLOCK_PTR block_list;
    BLOCK_PTR freeblock_list;
} __attribute__((aligned(16)));

/// Place in memory
struct memory_place
{
    ARENA_PTR arena;
    BLOCK_PTR block;
};

/// Amount of free space
long long int free_space = 0;

/// Pointer to list of arenas
ARENA_PTR arena_list = NULL;

/// Mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

#pragma region common helper functions

/**
 * Counts real amount of allocated space
 * @param size declared size
 */
ssize_t normalize(ssize_t size)
{
    ssize_t treshold = 4 * getpagesize();

    return size + 64 > treshold ? ((size + 31 + treshold) & (~(treshold - 1))) - 32
                                : ((size + 15) & (~15));
}

/**
 * Counts absolute value
 * @param value value
 */
ssize_t absolute(ssize_t value)
{
    return value < 0 ? -value : value;
}

/**
 * Looks up for arena and block where pointer is located
 * @param ptr pointer to look up
 */
PLACE find_place(PTR ptr)
{
    ARENA_PTR ar_ptr = arena_list;
    PLACE mp;

    mp.arena = NULL;
    mp.block = NULL;

    while(ar_ptr != NULL)
    {
        if((PTR)ar_ptr + 32 == ptr && ar_ptr->length > 0 && ar_ptr->block_list == NULL)
        {
            mp.arena = ar_ptr;

            return mp;
        }

        if((PTR)ar_ptr + 32 < ptr && ar_ptr->block_list != NULL
           && ((PTR)(ar_ptr->next) > ptr || (PTR)(ar_ptr->next) == NULL))
        {
            BLOCK_PTR bl_ptr = ar_ptr->block_list;

            while(bl_ptr != NULL)
            {
                if((PTR)bl_ptr + 32 == ptr && bl_ptr->length > 0)
                {
                    mp.arena = ar_ptr;
                    mp.block = bl_ptr;

                    return mp;
                }

                if(((PTR)bl_ptr + 32 == ptr && bl_ptr->length < 0) || (PTR)bl_ptr + 32 > ptr)
                    return mp;

                bl_ptr = bl_ptr->next;
            }

            return mp;
        }

        if((PTR)ar_ptr + 32 > ptr)
            return mp;

        ar_ptr = ar_ptr->next;
    }

    return mp;
}

#pragma endregion
#pragma region print memory

/**
 * Prints all memory to standard output
 */
void print_all_mem_fcn()
{
    ARENA_PTR ar_ptr = arena_list;

    if(arena_list != NULL)
        printf("-----------------------\nALL MEMORY (free space = %lld):\n", free_space);

    while(ar_ptr != NULL)
    {
        BLOCK_PTR bl_ptr = ar_ptr->block_list;

        if(bl_ptr == NULL)
        {
            if(ar_ptr->length < 0)
                printf("  %p - free", ar_ptr);
            else
                printf("  %p - ", ar_ptr);

            printf("arena at %p -> length = %zd\n", (PTR)ar_ptr + 32, absolute(ar_ptr->length));
        }
        else
        {
            printf("  %p - arena at %p -> length = %zd:\n", ar_ptr, (PTR)ar_ptr + 32,
                   absolute(ar_ptr->length));

            while(bl_ptr != NULL)
            {
                printf("    %p - ", bl_ptr);

                if(bl_ptr->length < 0)
                    printf("free ");

                printf("block at %p -> length = %zd\n", (PTR)bl_ptr + 32, absolute(bl_ptr->length));
                bl_ptr = bl_ptr->next;
            }
        }

        ar_ptr = ar_ptr->next;
    }

    if(arena_list != NULL)
        printf("-----------------------\n");
}

/**
 * Prints all free memory to standard output
 */
void print_free_mem_fcn()
{
    ARENA_PTR ar_ptr = arena_list;

    if(arena_list != NULL)
        printf("-----------------------\nFREE MEMORY (free space = %lld):\n", free_space);

    while(ar_ptr != NULL)
    {
        BLOCK_PTR fbl_ptr = ar_ptr->freeblock_list;

        if(fbl_ptr == NULL)
        {
            if(ar_ptr->length < 0)
                printf("  %p - free arena at %p -> length = %zd\n", ar_ptr, (PTR)ar_ptr + 32,
                       absolute(ar_ptr->length));
        }
        else
        {
            printf("  %p - arena at %p -> length = %zd:\n", ar_ptr, (PTR)ar_ptr + 32,
                   absolute(ar_ptr->length));

            while(fbl_ptr != NULL)
            {
                printf("    %p - free block at %p -> length = %zd, prev = %p, next = %p\n", fbl_ptr,
                       (PTR)fbl_ptr + 32, absolute(fbl_ptr->length), fbl_ptr->prev_free,
                       fbl_ptr->next_free);
                fbl_ptr = fbl_ptr->next_free;
            }
        }

        ar_ptr = ar_ptr->next;
    }

    if(arena_list != NULL)
        printf("-----------------------\n");
}

#pragma endregion
#pragma region memory helper functions

/**
 * Funkcja zapisująca pola struktury bloku.
 * @param bl_ptr wskaźnik na blok
 * @param ln długość bloku
 * @param prevb wskaźnik na poprzedni blok
 * @param nextb wskaźnik na następny blok
 * @param prevf wskaźnik na poprzedni wolny blok
 * @param nextf wskaźnik na następny wolny blok
 */
void set_block_fields(BLOCK_PTR bl_ptr, ssize_t ln, BLOCK_PTR prevb, BLOCK_PTR nextb,
                      BLOCK_PTR prevf, BLOCK_PTR nextf)
{
    bl_ptr->length = ln;
    bl_ptr->prev = prevb;
    bl_ptr->next = nextb;
    bl_ptr->prev_free = prevf;
    bl_ptr->next_free = nextf;
}

/**
 * Funkcja zapisująca pola struktury areny.
 * @param ar_ptr wskaźnik na blok
 * @param ln długość bloku
 * @param preva wskaźnik na poprzednią arenę
 * @param nexta wskaźnik na następną arenę
 * @param blist wskaźnik na pierszy blok listy
 * @param flist wskaźnik na pierszy wolny blok listy
 */
void set_arena_fields(ARENA_PTR ar_ptr, ssize_t ln, ARENA_PTR preva, ARENA_PTR nexta,
                      BLOCK_PTR blist, BLOCK_PTR flist)
{
    ar_ptr->length = ln;
    ar_ptr->prev = preva;
    ar_ptr->next = nexta;
    ar_ptr->block_list = blist;
    ar_ptr->freeblock_list = flist;
}

/**
 * Funkcja przepinająca wskaźniki wolnych bloków.
 * @param ar_ptr wskaźnik na arenę
 * @param bl_ptr wskaźnik na blok
 * @param prev_of_next poprzedni wskaźnik dla następnego
 * @param next_of_prev następny wskaźnik dla poprzedniego
 */
void switch_fblock_pointers(ARENA_PTR ar_ptr, BLOCK_PTR bl_ptr, BLOCK_PTR prev_of_next,
                            BLOCK_PTR next_of_prev)
{
    if(bl_ptr->next_free != NULL)
        bl_ptr->next_free->prev_free = prev_of_next;

    if(ar_ptr != NULL)
    {
        if(bl_ptr->prev_free != NULL)
            bl_ptr->prev_free->next_free = next_of_prev;
        else
            ar_ptr->freeblock_list = next_of_prev;
    }
}

/**
 * Funkcja przepinająca wskaźniki bloków.
 * @param ar_ptr wskaźnik na arenę
 * @param bl_ptr wskaźnik na blok
 * @param prev_of_next poprzedni wskaźnik dla następnego
 * @param next_of_prev następny wskaźnik dla poprzedniego
 */
void switch_block_pointers(ARENA_PTR ar_ptr, BLOCK_PTR bl_ptr, BLOCK_PTR prev_of_next,
                           BLOCK_PTR next_of_prev)
{
    if(bl_ptr->next != NULL)
        bl_ptr->next->prev = prev_of_next;

    if(ar_ptr != NULL)
    {
        if(bl_ptr->prev != NULL)
            bl_ptr->prev->next = next_of_prev;
        else
            ar_ptr->block_list = next_of_prev;
    }
}

/**
 * Funkcja przepinająca wskaźniki aren.
 * @param ar_fw_ptr wskaźnik na następną arenę
 * @param ar_bk_ptr wskaźnik na poprzednią arenę
 * @param prev_of_fw poprzedni wskaźnik dla następnego
 * @param next_of_bk następny wskaźnik dla poprzedniego
 */
void switch_arena_pointers(ARENA_PTR ar_fw_ptr, ARENA_PTR ar_bk_ptr, ARENA_PTR prev_of_fw,
                           ARENA_PTR next_of_bk)
{
    if(ar_fw_ptr != NULL)
        ar_fw_ptr->prev = prev_of_fw;

    if(ar_bk_ptr != NULL)
        ar_bk_ptr->next = next_of_bk;
    else
        arena_list = next_of_bk;
}

/**
 * Funkcja przydzielająca pamięć bloku.
 * @param ar_ptr wskaźnik na arenę
 * @param bl_ptr wskaźnik na blok
 * @param ln rozmiar do alokacji
 * @param will_be_free czy blok będzie wolny
 */
PTR alloc_to_block(ARENA_PTR ar_ptr, BLOCK_PTR bl_ptr, ssize_t ln, int will_be_free)
{
    if(absolute(bl_ptr->length) >= ln + 32 + 16)
    {
        BLOCK_PTR new_block = (PTR)bl_ptr + 32 + ln;

        switch_fblock_pointers(ar_ptr, bl_ptr, new_block, new_block);
        switch_block_pointers(NULL, bl_ptr, new_block, NULL);
        set_block_fields(new_block, -(absolute(bl_ptr->length) - ln - 32), bl_ptr, bl_ptr->next,
                         bl_ptr->prev_free, bl_ptr->next_free);

        if(will_be_free == 0)
        {
            set_block_fields(bl_ptr, ln, bl_ptr->prev, new_block, NULL, NULL);
            free_space -= 32 - absolute(bl_ptr->length);
        }
        else
        {
            set_block_fields(bl_ptr, ln, bl_ptr->prev, new_block, bl_ptr->prev_free, new_block);
            free_space += absolute(new_block->length);
        }
    }
    else
    {
        switch_fblock_pointers(ar_ptr, bl_ptr, bl_ptr->prev_free, bl_ptr->next_free);
        set_block_fields(bl_ptr, ln, bl_ptr->prev, bl_ptr->next, NULL, NULL);

        free_space -= absolute(bl_ptr->length);
    }

    return (PTR)bl_ptr + 32;
}

/**
 * Funkcja przydzielająca pamięć areny.
 * @param ar_back_ptr wskaźnik na poprzednią arenę
 * @param ar_forw_ptr wskaźnik na następną arenę
 * @param ln rozmiar do alokacji
 * @param alc_block czy przydzielamy z blokami
 */
PTR alloc_to_arena(ARENA_PTR ar_back_ptr, ARENA_PTR ar_forw_ptr, ssize_t ln, int alc_block)
{
    PTR adr = mmap(NULL, ln, (PROT_READ | PROT_WRITE), (MAP_ANONYMOUS | MAP_PRIVATE), -1, 0);

    if(adr == MAP_FAILED)
        return MAP_FAILED;

    ARENA_PTR ar_ptr = adr;

    while(ar_back_ptr != NULL && ar_back_ptr > ar_ptr)
    {
        ar_forw_ptr = ar_back_ptr;
        ar_back_ptr = ar_back_ptr->prev;
    }

    switch_arena_pointers(ar_forw_ptr, ar_back_ptr, ar_ptr, ar_ptr);

    if(alc_block == 0)
        set_arena_fields(ar_ptr, ln - 32, ar_back_ptr, ar_forw_ptr, NULL, NULL);
    else
    {
        set_arena_fields(ar_ptr, ln - 32, ar_back_ptr, ar_forw_ptr, adr + 32, adr + 32);

        BLOCK_PTR bl_str = adr + 32;

        set_block_fields(bl_str, -ln + 64, NULL, NULL, NULL, NULL);
        free_space += absolute(bl_str->length);
    }

    return (PTR)ar_ptr + 32;
}

/**
 * Funkcja dołączająca wolny blok.
 * @param ar_ptr wskaźnik na arenę
 * @param first_bl_ptr wskaźnik na blok, do którego przyłączamy
 * @param second_fbl_ptr wskaźnik na wolny blok, który będziemy przyłączać
 * @param is_first_free czy pierwszy blok jest wolny
 */
void concat_blocks(ARENA_PTR ar_ptr, BLOCK_PTR first_bl_ptr, BLOCK_PTR second_fbl_ptr,
                   int is_first_free)
{
    if(first_bl_ptr != NULL && second_fbl_ptr != NULL && first_bl_ptr->next == second_fbl_ptr)
    {
        if(is_first_free == 0)
        {
            free_space += 32 + absolute(first_bl_ptr->length);
            set_block_fields(
                first_bl_ptr,
                -(absolute(first_bl_ptr->length) + 32 + absolute(second_fbl_ptr->length)),
                first_bl_ptr->prev, second_fbl_ptr->next, second_fbl_ptr->prev_free,
                second_fbl_ptr->next_free);
            switch_block_pointers(NULL, second_fbl_ptr, first_bl_ptr, NULL);
            switch_fblock_pointers(ar_ptr, second_fbl_ptr, first_bl_ptr, first_bl_ptr);
        }
        else
        {
            free_space += 32;
            set_block_fields(
                first_bl_ptr,
                -(absolute(first_bl_ptr->length) + 32 + absolute(second_fbl_ptr->length)),
                first_bl_ptr->prev, second_fbl_ptr->next, first_bl_ptr->prev_free,
                second_fbl_ptr->next_free);
            switch_block_pointers(NULL, second_fbl_ptr, first_bl_ptr, NULL);
            switch_fblock_pointers(NULL, second_fbl_ptr, first_bl_ptr, NULL);
        }
    }
    else if(first_bl_ptr != NULL && second_fbl_ptr != NULL)
    {
        first_bl_ptr->next_free = second_fbl_ptr;
        second_fbl_ptr->prev_free = first_bl_ptr;
    }
    else if(first_bl_ptr != NULL && second_fbl_ptr == NULL && is_first_free == 0)
        first_bl_ptr->next_free = NULL;
    else if(first_bl_ptr == NULL && second_fbl_ptr != NULL && is_first_free != 0)
    {
        second_fbl_ptr->prev_free = NULL;
        ar_ptr->freeblock_list = second_fbl_ptr;
    }
}

/**
 * Funkcja powiększająca rozmiar i przesuwająca bloki.
 * @param ar_ptr wskaźnik na arenę
 * @param rs_bl_ptr wskaźnik na blok powiększany
 * @param mv_bl_ptr wskaźnik na blok przesuwany
 * @param ln nowy rozmiar
 */
PTR resize_and_move(ARENA_PTR ar_ptr, BLOCK_PTR rs_bl_ptr, BLOCK_PTR mv_bl_ptr, ssize_t ln)
{
    if(absolute(rs_bl_ptr->length) + 32 + absolute(mv_bl_ptr->length) >= ln + 32 + 16)
    {
        BLOCK_PTR new_block = (PTR)rs_bl_ptr + 32 + ln;
        BLOCK mvbl = *mv_bl_ptr;

        switch_fblock_pointers(ar_ptr, &mvbl, new_block, new_block);
        set_block_fields(new_block, -(absolute(rs_bl_ptr->length) + absolute(mvbl.length) - ln),
                         rs_bl_ptr, mvbl.next, mvbl.prev_free, mvbl.next_free);
        set_block_fields(rs_bl_ptr, ln, rs_bl_ptr->prev, new_block, rs_bl_ptr->prev_free,
                         new_block);
        free_space -= absolute(mvbl.length) + absolute(new_block->length);
    }
    else
    {
        set_block_fields(rs_bl_ptr, absolute(rs_bl_ptr->length) + 32 + absolute(mv_bl_ptr->length),
                         rs_bl_ptr->prev, mv_bl_ptr->next, rs_bl_ptr->prev_free,
                         rs_bl_ptr->next_free);
        switch_block_pointers(NULL, mv_bl_ptr, rs_bl_ptr, NULL);
        switch_fblock_pointers(ar_ptr, mv_bl_ptr, mv_bl_ptr->prev_free, mv_bl_ptr->next_free);
    }

    return (PTR)rs_bl_ptr + 32;
}

#pragma endregion
#pragma region memory functions

/**
 * Funkcja zwalniająca pamięć spod danego wskaźnika.
 * @param ptr wskaźnik
 */
void free_fcn(PTR ptr)
{
    if(ptr == NULL)
        return;

    if(ptr < (PTR)arena_list)
    {
        errno = EINVAL;

        return;
    }

    PLACE mp = find_place(ptr);
    ARENA_PTR ar_ptr = mp.arena;
    BLOCK_PTR bl_ptr = mp.block;

    if(ar_ptr == NULL && bl_ptr == NULL)
    {
        errno = EINVAL;

        return;
    }

    if(bl_ptr == NULL)
    {
        ar_ptr->length = -ar_ptr->length;
        free_space += absolute(ar_ptr->length);
    }
    else
    {
        BLOCK_PTR back_fbl = NULL;
        BLOCK_PTR forw_fbl = ar_ptr->freeblock_list;

        bl_ptr->length = -bl_ptr->length;
        free_space += absolute(bl_ptr->length);

        while(forw_fbl != NULL && (PTR)forw_fbl < (PTR)bl_ptr)
        {
            back_fbl = forw_fbl;
            forw_fbl = forw_fbl->next_free;
        }

        concat_blocks(ar_ptr, bl_ptr, forw_fbl, 0);
        concat_blocks(ar_ptr, back_fbl, bl_ptr, 1);
    }

    ssize_t treshold = 4 * getpagesize();

    if(free_space > 2 * treshold)
    {
        ARENA_PTR del_ptr = arena_list;

        while(del_ptr != NULL)
        {
            if(del_ptr->length < 0
               || (del_ptr->freeblock_list != NULL
                   && absolute(del_ptr->freeblock_list->length) == treshold - 64))
            {
                ssize_t ln = absolute(del_ptr->length);
                PTR ptr = del_ptr;

                switch_arena_pointers(del_ptr->next, del_ptr->prev, del_ptr->prev, del_ptr->next);
                del_ptr = del_ptr->next;
                free_space -= ln;
                munmap(ptr, ln + 32);
            }
            else
                del_ptr = del_ptr->next;
        }
    }
}

/**
 * Funkcja przydzielająca pamięć o zadanym rozmiarze.
 * @param size rozmiar
 */
PTR malloc_fcn(size_t size)
{
    if(size == 0)
        return NULL;

    ssize_t norm_size = normalize(size);
    ssize_t treshold = 4 * getpagesize();
    ARENA_PTR ar_forw_ptr = arena_list;
    ARENA_PTR ar_back_ptr = NULL;

    if(norm_size + 64 > treshold)
    {
        while(ar_forw_ptr != NULL)
        {
            if(ar_forw_ptr->length < 0 && ar_forw_ptr->block_list == NULL
               && absolute(ar_forw_ptr->length) >= norm_size)
            {
                ar_forw_ptr->length = absolute(ar_forw_ptr->length);
                free_space -= absolute(ar_forw_ptr->length);

                return (PTR)ar_forw_ptr + 32;
            }

            ar_back_ptr = ar_forw_ptr;
            ar_forw_ptr = ar_forw_ptr->next;
        }

        return alloc_to_arena(ar_back_ptr, ar_forw_ptr, norm_size + 32, 0);
    }
    else
    {
        while(ar_forw_ptr != NULL)
        {
            if(ar_forw_ptr->freeblock_list != NULL)
            {
                BLOCK_PTR bl_ptr = ar_forw_ptr->freeblock_list;

                while(bl_ptr != NULL)
                {
                    if(absolute(bl_ptr->length) >= norm_size)
                        return alloc_to_block(ar_forw_ptr, bl_ptr, norm_size, 0);

                    bl_ptr = bl_ptr->next_free;
                }
            }

            ar_back_ptr = ar_forw_ptr;
            ar_forw_ptr = ar_forw_ptr->next;
        }

        PTR adr = alloc_to_arena(ar_back_ptr, ar_forw_ptr, treshold, 1);

        if(adr == MAP_FAILED)
            return MAP_FAILED;

        ARENA_PTR ar_ptr = adr - 32;
        BLOCK_PTR bl_str = adr;

        return alloc_to_block(ar_ptr, bl_str, norm_size, 0);
    }
}

/**
 * Funkcja przydzielająca kolejne kawałki pamięci o zadanym rozmiarze.
 * @param count liczba kawałków
 * @param size rozmiar pojedynczego kawałka
 */
PTR calloc_fcn(size_t count, size_t size)
{
    if(count == 0 || size == 0)
        return NULL;

    size_t norm_size = normalize(count * size);
    PTR ret = malloc_fcn(count * size);

    ret = memset(ret, 0, norm_size);

    return ret;
}

/**
 * Funkcja tworząca całkowicie nowy blok i przenosząca do niego zawartość.
 * @param ar_ptr wskaźnik na arenę
 * @param bl_ptr wskaźnik na blok
 * @param del_ptr wskaźnik do zwolnienia
 * @param size nowy rozmiar
 */
PTR alloc_and_move(ARENA_PTR ar_ptr, BLOCK_PTR bl_ptr, PTR del_ptr, ssize_t size)
{
    PTR ret = malloc_fcn(absolute(size));

    if(ar_ptr != NULL)
        ret = memmove(ret, (PTR)ar_ptr + 32, absolute(ar_ptr->length));
    else if(bl_ptr != NULL)
        ret = memmove(ret, (PTR)bl_ptr + 32, absolute(bl_ptr->length));

    free_fcn(del_ptr);

    return ret;
}

/**
 * Funkcja dokonująca zmiany rozmiaru już przydzielonego obszaru.
 * @param ptr wskaźnik na przydzialony obszar
 * @param size nowy rozmiar obszaru
 */
PTR realloc_fcn(PTR ptr, size_t size)
{
    if(ptr == NULL && size == 0)
        return NULL;

    if(ptr == NULL)
        return malloc_fcn(size);

    if(size == 0)
    {
        free_fcn(ptr);

        return NULL;
    }

    if(ptr < (PTR)arena_list)
    {
        errno = EINVAL;

        return MAP_FAILED;
    }

    ssize_t norm_size = normalize(size);
    PLACE mp = find_place(ptr);
    ARENA_PTR ar_ptr = mp.arena;
    BLOCK_PTR bl_ptr = mp.block;

    if(ar_ptr == NULL && bl_ptr == NULL)
    {
        errno = EINVAL;

        return MAP_FAILED;
    }

    if(bl_ptr == NULL)
        return absolute(ar_ptr->length) < norm_size ? alloc_and_move(ar_ptr, NULL, ptr, size)
                                                    : (PTR)ar_ptr + 32;

    if(norm_size + 64 > 4 * getpagesize())
        return alloc_and_move(NULL, bl_ptr, ptr, size);

    if(absolute(bl_ptr->length) >= norm_size + 32 + 16)
        return alloc_to_block(ar_ptr, bl_ptr, norm_size, 1);

    if(norm_size > absolute(bl_ptr->length))
    {
        BLOCK_PTR forw_bl = bl_ptr->next;

        return forw_bl != NULL && forw_bl->length < 0
                       && absolute(bl_ptr->length) + 32 + absolute(forw_bl->length) >= norm_size
                   ? resize_and_move(ar_ptr, bl_ptr, forw_bl, norm_size)
                   : alloc_and_move(NULL, bl_ptr, ptr, size);
    }

    return (PTR)bl_ptr + 32;
}

#pragma endregion
#pragma region public functions

PTR malloc(size_t size)
{
    pthread_mutex_lock(&mutex);

    PTR adr = malloc_fcn(size);

    pthread_mutex_unlock(&mutex);

    return adr;
}

PTR calloc(size_t count, size_t size)
{
    pthread_mutex_lock(&mutex);

    PTR adr = calloc_fcn(count, size);

    pthread_mutex_unlock(&mutex);

    return adr;
}

PTR realloc(PTR ptr, size_t size)
{
    pthread_mutex_lock(&mutex);

    PTR adr = realloc_fcn(ptr, size);

    pthread_mutex_unlock(&mutex);

    return adr;
}

void free(PTR ptr)
{
    pthread_mutex_lock(&mutex);
    free_fcn(ptr);
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
