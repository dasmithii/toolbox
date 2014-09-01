#include <kit/greatest.h>
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
    #define N 100
	SETUP_HEAP();
    for(int i = 0; i < N; ++i)
        Heap_insert(&heap, &i);
    ASSERT_EQ(N, heap.elementCount);
    for(int i = 0; i < N; ++i){
        int v;
        Heap_fetchTop(&heap, &v);
        Heap_removeTop(&heap);
    }
    CLEAN_HEAP();
}


GREATEST_SUITE(Heap_suite) 
{
    RUN_TEST(Heap_basic_test);
}