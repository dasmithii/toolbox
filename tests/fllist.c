#include "common.h"
#include "../sources/fllist.h"
#include <kit/greatest/greatest.h>

#define SETUP_FLLIST()              \
    fllist list;                    \
    fllist_init(&list, sizeof(int))

#define CLEAN_FLLIST()   \
    fllist_clean(&list); \
    PASS()


TEST fllist_basic_test() 
{
	SETUP_FLLIST();

    // populate list
    for(int i = 0; i < ITERS; i++){
    	fllist_append(&list, &i);
    }

    // check that all elements were set correctlys
    for(int i = 0; i < ITERS; i++){
    	int elem;
    	fllist_fetch(&list, i, &elem);
    	ASSERT_EQ(i, elem);
    }
    CLEAN_FLLIST();
}

// SORT
static int _intcmp(const void *v1, const void *v2){return (*(int *)v1 - *(int *)v2);}
TEST fllist_sort_test() 
{

    SETUP_FLLIST();

    for (int i = 0; i < ITERS; ++i)
    {
        int n = rand();
        fllist_append(&list, &n);
    }

    fllist_sort(&list, _intcmp);


    for(int i = 0; i < ITERS - 1; ++i){
        int v1, v2;
        fllist_fetch(&list, i, &v1);
        fllist_fetch(&list, i+1, &v2);
        ASSERT(v1 <= v2);
    }

    CLEAN_FLLIST();
}

// PREPEND
TEST fllist_prepend_test() 
{
    SETUP_FLLIST();

    for(int i = 0; i < ITERS; ++i)
        fllist_prepend(&list, &i);
    for(int i = 0; i < ITERS; ++i){
        int v;
        fllist_fetch(&list, i, &v);
        ASSERT_EQ(v, ITERS - i - 1);
    }
    CLEAN_FLLIST();
}

// INSERT
TEST fllist_insert_test() 
{
    SETUP_FLLIST();
    int v1 = 1, v2 = 2;

    for(int i = 0; i < ITERS; ++i)
        fllist_append(&list, &v1);

    for(int i = ITERS - 1; i >= 0; --i)
        fllist_insert(&list, i, &v2);


    for(int i = 0; i < ITERS - 1; i += 2){
        int e1, e2;
        fllist_fetch(&list, i, &e1);
        fllist_fetch(&list, i + 1, &e2);
        ASSERT_EQ(e1 + e2, v1 + v2);
    }
    CLEAN_FLLIST();
}

// REMOVE
TEST fllist_remove_test() 
{
    SETUP_FLLIST();

    for (int i = 0; i < ITERS; ++i)
        fllist_append(&list, &i);
    for (int i = 0; i < ITERS/2; ++i)
        fllist_remove(&list, 0);
    for (int i = 0; i < ITERS - ITERS/2; ++i){
        int e1;
        fllist_fetch(&list, i, &e1);
        ASSERT_EQ(e1, ITERS/2 + i);
    }

    CLEAN_FLLIST();
}

// REVERSE
TEST fllist_reverse_test() 
{
    SETUP_FLLIST();

    for(int i = 0; i < ITERS; ++i)
        fllist_append(&list, &i);

    fllist_reverse(&list);

    for(int i = 0; i < ITERS; ++i){
        int v;
        fllist_fetch(&list, i, &v);
        ASSERT_EQ(v, ITERS - i - 1);
    }

    CLEAN_FLLIST();
}


// FOREACH
static void _times2(void *ptr){*((int*)ptr) *= 2;}
TEST fllist_foreach_test() 
{
    SETUP_FLLIST();

    for(int i = 0; i < ITERS; ++i)
        fllist_append(&list, &i);
    fllist_each(&list, _times2);

    for(int i = 0; i < ITERS; ++i){
        int v1;
        fllist_fetch(&list, i, &v1);
        ASSERT_EQ(v1, i * 2);
    }

    CLEAN_FLLIST();
}

// CLONE
TEST fllist_clone_test()
{
    SETUP_FLLIST();

    // populate
    for(int i = 0; i < ITERS; ++i)
        fllist_append(&list, &i);

    // clone
    fllist *clone = fllist_clone(&list);

    // ccheck
    ASSERT(clone != &list);
    ASSERT_EQ(clone->elem_size, list.elem_size);
    for(int i = 0; i < ITERS; ++i){
        int e1, e2;
        fllist_fetch(&list, i, &e1); 
        fllist_fetch(clone, i, &e2); 
        ASSERT_EQ(e1, e2);
    }
    CLEAN_FLLIST();
}

TEST fllist_size_test()
{
    SETUP_FLLIST();

    // populate
    for(int i = 0; i < ITERS; ++i)
        fllist_append(&list, &i);
    ASSERT_EQ(fllist_size(&list), ITERS);
    CLEAN_FLLIST();
}


GREATEST_SUITE(fllist_suite) 
{
    RUN_TEST(fllist_basic_test);
    RUN_TEST(fllist_sort_test);
    RUN_TEST(fllist_prepend_test);
    RUN_TEST(fllist_insert_test);
    RUN_TEST(fllist_remove_test);
    RUN_TEST(fllist_reverse_test);
    RUN_TEST(fllist_foreach_test);
    RUN_TEST(fllist_clone_test);
    RUN_TEST(fllist_size_test);
}