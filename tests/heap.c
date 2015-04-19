#include "greatest.h"
#include "../sources/heap.h"


static int simpleCompare(const void *p1, const void *p2)
{
    int i1 = *((int*) p1);
    int i2 = *((int*) p2);
    if(i1 == i2)
        return 0;
    else if(i1 > i2)
        return 1;
    else
        return -1;
}


#define SETUP_HEAP()                \
    Heap heap;                      \
    Heap_init(&heap, sizeof(int), simpleCompare)

#define CLEAN_HEAP()    \
    Heap_clean(&heap);  \
    PASS()


TEST Heap_basic_test() 
{
    unsigned n = 100;
	SETUP_HEAP();
    for(int i = 0; i < n; ++i)
        Heap_insert(&heap, &i);
    ASSERT_EQ(n, heap.elementCount);
    for(int i = 0; i < n; ++i){
        int v;
        Heap_fetchTop(&heap, &v);
        Heap_removeTop(&heap);
    }
    CLEAN_HEAP();
}


// Fills heap with random numbers and checks that they're popped
// off in order relative to eachother.
TEST Heap_random_test()
{
    SETUP_HEAP();
    for(int i = 0; i < 100; ++i){
        int n = rand();
        Heap_insert(&heap, &n);
    }
    int prev;
    Heap_fetchTop(&heap, &prev);
    Heap_removeTop(&heap);
    for(int i = 0; i < heap.elementCount; ++i){
        int curr;
        Heap_fetchTop(&heap, &curr);
        ASSERT(prev >= curr);
        prev = curr;
        Heap_removeTop(&heap);
    }
    CLEAN_HEAP();   
}


GREATEST_SUITE(Heap_suite) 
{
    RUN_TEST(Heap_basic_test);
    RUN_TEST(Heap_random_test);
}