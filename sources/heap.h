#ifndef _BASELINE_HEAP_
#define _BASELINE_HEAP_
#include <stddef.h>


typedef struct {
	size_t elementCount;
	size_t elementSize;
	char *data;
	int (*compareFunction)(const void*, const void*);
} Heap;


// Initialize empty heap.
int Heap_init(Heap *self
	        , size_t elementSize
	        , int(*compareFunction)(const void*, const void*));


// Frees all internal data, invalidating the heap.
void Heap_clean(Heap *self);


// Inserts data from <address>, maintaining the heap property.
int Heap_insert(Heap *self
	         , const void *address);


// Pops top element.
int Heap_removeTop(Heap *self);


// Returns address of first element.
void *Heap_hookTop(Heap *self);


// Copies data from first element to <destination> address.
void Heap_fetchTop(Heap *self
	             , void *destination);



void Heap_test();
#endif