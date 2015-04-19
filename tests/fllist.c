#include "common.h"
#include "../sources/fllist.h"
#include "greatest.h"

#define SETUP_FLLIST()              \
    FLList list;                    \
    FLList_init(&list, sizeof(int))

#define CLEAN_FLLIST()   \
    FLList_clean(&list); \
    PASS()


TEST FLList_append_test() 
{
	SETUP_FLLIST();

    // populate list
    for(int i = 0; i < ITERS; i++)
    	FLList_append(&list, &i);

    // check that all elements were set correctly
    for(int i = 0; i < ITERS; i++){
    	int elem;
    	FLList_fetch(&list, i, &elem);
    	ASSERT_EQ(i, elem);
    }
    CLEAN_FLLIST();
}


TEST FLList_prepend_test() 
{
    SETUP_FLLIST();
    for(int i = 0; i < ITERS; ++i)
        FLList_prepend(&list, &i);
    for(int i = 0; i < ITERS; ++i){
        int v;
        FLList_fetch(&list, i, &v);
        ASSERT_EQ(v, ITERS - i - 1);
    }
    CLEAN_FLLIST();
}


TEST FLList_insert_test() 
{
    SETUP_FLLIST();
    int v1 = 1, v2 = 2;

    for(int i = 0; i < ITERS; ++i)
        FLList_append(&list, &v1);

    for(int i = ITERS - 1; i >= 0; --i)
        FLList_insert(&list, &v2, i);


    for(int i = 0; i < ITERS - 1; i += 2){
        int e1, e2;
        FLList_fetch(&list, i, &e1);
        FLList_fetch(&list, i + 1, &e2);
        ASSERT_EQ(e1 + e2, v1 + v2);
    }
    CLEAN_FLLIST();
}


TEST FLList_remove_test() 
{
    SETUP_FLLIST();

    for (int i = 0; i < ITERS; ++i)
        FLList_append(&list, &i);
    for (int i = 0; i < ITERS/2; ++i)
        FLList_remove(&list, 0);
    for (int i = 0; i < ITERS - ITERS/2; ++i){
        int e1;
        FLList_fetch(&list, i, &e1);
        ASSERT_EQ(e1, ITERS/2 + i);
    }

    CLEAN_FLLIST();
}


static void _times2(void *ptr){*((int*)ptr) *= 2;}
TEST FLList_foreach_test() 
{
    SETUP_FLLIST();

    for(int i = 0; i < ITERS; ++i)
        FLList_append(&list, &i);
    FLList_each(&list, _times2);

    for(int i = 0; i < ITERS; ++i){
        int v1;
        FLList_fetch(&list, i, &v1);
        ASSERT_EQ(v1, i * 2);
    }

    CLEAN_FLLIST();
}


TEST FLList_size_test()
{
    SETUP_FLLIST();

    // populate
    for(int i = 0; i < ITERS; ++i)
        FLList_append(&list, &i);
    ASSERT_EQ(FLList_length(&list), ITERS);
    CLEAN_FLLIST();
}


GREATEST_SUITE(FLList_suite) 
{
    RUN_TEST(FLList_append_test);
    RUN_TEST(FLList_prepend_test);
    RUN_TEST(FLList_insert_test);
    RUN_TEST(FLList_remove_test);
    RUN_TEST(FLList_foreach_test);
    RUN_TEST(FLList_size_test);
}