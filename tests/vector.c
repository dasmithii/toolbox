#include "common.h"
#include <kit/greatest.h>
#include "../sources/vector.h"

#define SETUP_VEC()                 \
    Vector vec;                     \
    Vector_init(&vec, sizeof(int))

#define CLEAN_VEC() Vector_clean(&vec) 


// BASIC
TEST Vector_basic_test() 
{
	SETUP_VEC();

    // populate vector
    for(int i = 0; i < ITERS; i++){
    	Vector_append(&vec, &i);
    }

    // check that all elements were set correctlys
    for(int i = 0; i < ITERS; i++){
    	int elem;
    	Vector_fetch(&vec, i, &elem);
    	ASSERT_EQ(i, elem);
    }
    CLEAN_VEC();
    PASS();
}

// SORT
static int intcmp(const void *v1, const void *v2){return (*(int *)v1 - *(int *)v2);}
TEST Vector_sort_test() 
{
    SETUP_VEC();

    for (int i = 0; i < ITERS; ++i)
    {
        int n = rand();
        Vector_append(&vec, &n);
    }

    Vector_sort(&vec, intcmp);
    ASSERT_EQ(ITERS, vec.size);
    for(int i = 0; i < vec.size - 1; ++i){
        int v1, v2;
        Vector_fetch(&vec, i, &v1);
        Vector_fetch(&vec, i+1, &v2);
        ASSERT(v1 <= v2);
    }
    CLEAN_VEC();
    PASS();
}

// PREPEND
TEST Vector_prepend_test() 
{
    SETUP_VEC();

    for(int i = 0; i < ITERS; ++i)
        Vector_prepend(&vec, &i);
    for(int i = 0; i < ITERS; ++i){
        int v;
        Vector_fetch(&vec, i, &v);
        ASSERT_EQ(v, ITERS - i - 1);
    }
    CLEAN_VEC();
    PASS();
}

// INSERT
TEST Vector_insert_test() 
{
    SETUP_VEC();
    int v1 = 1, v2 = 2;

    for(int i = 0; i < ITERS; ++i)
        Vector_append(&vec, &v1);

    for(int i = ITERS -1; i >= 0; --i)
        Vector_insert(&vec, i, &v2);

    for(int i = 0; i < vec.size - 1; i += 2){
        int e1, e2;
        Vector_fetch(&vec, i, &e1);
        Vector_fetch(&vec, i + 1, &e2);
        ASSERT_EQ(e1 + e2, v1 + v2);
    }
    CLEAN_VEC();
    PASS();
}

// REMOVE
TEST Vector_remove_test() 
{
    SETUP_VEC();

    for (int i = 0; i < ITERS; ++i)
        Vector_append(&vec, &i);
    for (int i = 0; i < ITERS/2; ++i)
        Vector_remove(&vec, 0);
    for (int i = 0; i < vec.size; ++i){
        int e1;
        Vector_fetch(&vec, i, &e1);
        ASSERT_EQ(e1, ITERS/2 + i);
    }
    ASSERT_EQ(vec.size, ITERS - ITERS/2);

    CLEAN_VEC();
    PASS();
}

// REVERSE
TEST Vector_reverse_test() 
{
    SETUP_VEC();

    for(int i = 0; i < ITERS; ++i)
        Vector_append(&vec, &i);
    Vector_reverse(&vec);
    for(int i = 0; i < ITERS; ++i){
        int v;
        Vector_fetch(&vec, i, &v);
        ASSERT_EQ(v, ITERS - i - 1);
    }

    CLEAN_VEC();
    PASS();
}


// FOREACH
static void times2(void *ptr) {*((int*)ptr) *= 2;}
TEST Vector_foreach_test() 
{
    SETUP_VEC();

    for(int i = 0; i < ITERS; ++i)
        Vector_append(&vec, &i);
    Vector_each(&vec, times2);

    for(int i = 0; i < ITERS; ++i){
        int v1;
        Vector_fetch(&vec, i, &v1);
        ASSERT_EQ(v1, i * 2);
    }

    CLEAN_VEC();
    PASS();
}

// vector *Vector_clone(vector*);

// void Vector_each(vector*, void (*)(void*));


GREATEST_SUITE(Vector_suite) 
{
    RUN_TEST(Vector_basic_test);
    RUN_TEST(Vector_sort_test);
    RUN_TEST(Vector_prepend_test);
    RUN_TEST(Vector_insert_test);
    RUN_TEST(Vector_remove_test);
    RUN_TEST(Vector_reverse_test);
    RUN_TEST(Vector_foreach_test);
}