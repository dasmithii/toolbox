#include "common.h"
#include "../sources/list.h"
#include "greatest.h"

#define SETUP_LIST()              \
    List list;                    \
    List_init(&list, sizeof(int))

#define CLEAN_LIST()   \
    List_clean(&list); \
    PASS()


TEST List_append_test() 
{
	SETUP_LIST();

    // populate list
    for(int i = 0; i < ITERS; i++)
    	List_append(&list, &i);

    // check that all elements were set correctly
    for(int i = 0; i < ITERS; i++){
    	int elem;
    	List_fetch(&list, i, &elem);
    	ASSERT_EQ(i, elem);
    }
    CLEAN_LIST();
}


TEST List_prepend_test() 
{
    SETUP_LIST();
    for(int i = 0; i < ITERS; ++i)
        List_prepend(&list, &i);
    for(int i = 0; i < ITERS; ++i){
        int v;
        List_fetch(&list, i, &v);
        ASSERT_EQ(v, ITERS - i - 1);
    }
    CLEAN_LIST();
}


TEST List_insert_test() 
{
    SETUP_LIST();
    int v1 = 1, v2 = 2;

    for(int i = 0; i < ITERS; ++i)
        List_append(&list, &v1);

    for(int i = ITERS - 1; i >= 0; --i)
        List_insert(&list, i, &v2);


    for(int i = 0; i < ITERS - 1; i += 2){
        int e1, e2;
        List_fetch(&list, i, &e1);
        List_fetch(&list, i + 1, &e2);
        ASSERT_EQ(e1 + e2, v1 + v2);
    }
    CLEAN_LIST();
}


TEST List_remove_test() 
{
    SETUP_LIST();

    for (int i = 0; i < ITERS; ++i)
        List_append(&list, &i);
    for (int i = 0; i < ITERS/2; ++i)
        List_remove(&list, 0);
    for (int i = 0; i < ITERS - ITERS/2; ++i){
        int e1;
        List_fetch(&list, i, &e1);
        ASSERT_EQ(e1, ITERS/2 + i);
    }

    CLEAN_LIST();
}


static void _times2(void *ptr){*((int*)ptr) *= 2;}
TEST List_foreach_test() 
{
    SETUP_LIST();

    for(int i = 0; i < ITERS; ++i)
        List_append(&list, &i);
    List_each(&list, _times2);

    for(int i = 0; i < ITERS; ++i){
        int v1;
        List_fetch(&list, i, &v1);
        ASSERT_EQ(v1, i * 2);
    }

    CLEAN_LIST();
}


TEST List_size_test()
{
    SETUP_LIST();

    // populate
    for(int i = 0; i < ITERS; ++i)
        List_append(&list, &i);
    ASSERT_EQ(list.length, ITERS);
    CLEAN_LIST();
}


GREATEST_SUITE(List_suite) 
{
    RUN_TEST(List_append_test);
    RUN_TEST(List_prepend_test);
    RUN_TEST(List_insert_test);
    RUN_TEST(List_remove_test);
    RUN_TEST(List_foreach_test);
    RUN_TEST(List_size_test);
}