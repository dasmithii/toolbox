#include "common.h"
#include <kit/greatest.h>
#include "../sources/vector.h"

#define SETUP_VEC()                    \
    vector vec;                     \
    vector_init(&vec, sizeof(int))

#define CLEAN_VEC() vector_clean(&vec) 


// BASIC
TEST vector_basic_test() 
{
	SETUP_VEC();

    // populate vector
    for(int i = 0; i < ITERS; i++){
    	vector_append(&vec, &i);
    }

    // check that all elements were set correctlys
    for(int i = 0; i < ITERS; i++){
    	int elem;
    	vector_fetch(&vec, i, &elem);
    	ASSERT_EQ(i, elem);
    }
    CLEAN_VEC();
    PASS();
}

// SORT
static int intcmp(const void *v1, const void *v2){return (*(int *)v1 - *(int *)v2);}
TEST vector_sort_test() 
{
    SETUP_VEC();

    for (int i = 0; i < ITERS; ++i)
    {
        int n = rand();
        vector_append(&vec, &n);
    }

    vector_sort(&vec, intcmp);
    ASSERT_EQ(ITERS, vec.size);
    for(int i = 0; i < vec.size - 1; ++i){
        int v1, v2;
        vector_fetch(&vec, i, &v1);
        vector_fetch(&vec, i+1, &v2);
        ASSERT(v1 <= v2);
    }
    CLEAN_VEC();
    PASS();
}

// PREPEND
TEST vector_prepend_test() 
{
    SETUP_VEC();

    for(int i = 0; i < ITERS; ++i)
        vector_prepend(&vec, &i);
    for(int i = 0; i < ITERS; ++i){
        int v;
        vector_fetch(&vec, i, &v);
        ASSERT_EQ(v, ITERS - i - 1);
    }
    CLEAN_VEC();
    PASS();
}

// INSERT
TEST vector_insert_test() 
{
    SETUP_VEC();
    int v1 = 1, v2 = 2;

    for(int i = 0; i < ITERS; ++i)
        vector_append(&vec, &v1);

    for(int i = ITERS -1; i >= 0; --i)
        vector_insert(&vec, i, &v2);

    for(int i = 0; i < vec.size - 1; i += 2){
        int e1, e2;
        vector_fetch(&vec, i, &e1);
        vector_fetch(&vec, i + 1, &e2);
        ASSERT_EQ(e1 + e2, v1 + v2);
    }
    CLEAN_VEC();
    PASS();
}

// REMOVE
TEST vector_remove_test() 
{
    SETUP_VEC();

    for (int i = 0; i < ITERS; ++i)
        vector_append(&vec, &i);
    for (int i = 0; i < ITERS/2; ++i)
        vector_remove(&vec, 0);
    for (int i = 0; i < vec.size; ++i){
        int e1;
        vector_fetch(&vec, i, &e1);
        ASSERT_EQ(e1, ITERS/2 + i);
    }
    ASSERT_EQ(vec.size, ITERS - ITERS/2);

    CLEAN_VEC();
    PASS();
}

// REVERSE
TEST vector_reverse_test() 
{
    SETUP_VEC();

    for(int i = 0; i < ITERS; ++i)
        vector_append(&vec, &i);
    vector_reverse(&vec);
    for(int i = 0; i < ITERS; ++i){
        int v;
        vector_fetch(&vec, i, &v);
        ASSERT_EQ(v, ITERS - i - 1);
    }

    CLEAN_VEC();
    PASS();
}


// FOREACH
static void times2(void *ptr) {*((int*)ptr) *= 2;}
TEST vector_foreach_test() 
{
    SETUP_VEC();

    for(int i = 0; i < ITERS; ++i)
        vector_append(&vec, &i);
    vector_each(&vec, times2);

    for(int i = 0; i < ITERS; ++i){
        int v1;
        vector_fetch(&vec, i, &v1);
        ASSERT_EQ(v1, i * 2);
    }

    CLEAN_VEC();
    PASS();
}

// vector *vector_clone(vector*);

// void vector_each(vector*, void (*)(void*));


GREATEST_SUITE(vector_suite) 
{
    RUN_TEST(vector_basic_test);
    RUN_TEST(vector_sort_test);
    RUN_TEST(vector_prepend_test);
    RUN_TEST(vector_insert_test);
    RUN_TEST(vector_remove_test);
    RUN_TEST(vector_reverse_test);
    RUN_TEST(vector_foreach_test);
}