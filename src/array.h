#ifndef _BASELINE_ARRAY_
#define _BASELINE_ARRAY_
#include <string.h>
#include <stdlib.h>
#include "debug.h"
#include "memory.h"

typedef struct {
	size_t num_elems;
	size_t elem_size;
	char *data;
} array;

// Initializes a preallocated array.
int array_init(array *const arr
	            , const size_t num_elems
	            , const size_t elem_size);

// Cleans array internals without freeing the structure.
void array_clean(array *const arr);

// Allocates, initializes, and returns an array.
array *array_new(const size_t num_elems
	                 , const size_t elem_size);

// Cleans and frees parameter.
void array_free(array *const arr);

// Returns pointer to nth element.
void *array_hook(const array *const arr
	              , const size_t i);

// Copies data into element.
void array_set(array *const arr
	            , const size_t i
	            , const void *const ptr);

// Copies data from element.
void array_fetch(const array *const arr
	              , const size_t i
	              , void *const dest);

// Sets all array bytes to zero.
void array_zero(array *const arr);

// Copies data from address <val> to each array element.
void array_fill(array *const arr
	             , const void *const val);

// Reverses elements.
void array_reverse(array *const arr);

// Calls qsort() internally.
void array_sort(array *const arr
	             , int (*cmp)(const void*, const void*));

// Applies <func> to each array element directly.
void array_each(array *const arr
	             , void (*func)(void*));

// Copies all internal data, returning an independent array.
int array_copy(const array *const src
	            , array *const dest);

// Allocates and returns a copied array. Returns NULL on failure.
array *array_clone(const array *const arr);

// Returns byte count of internal allocation.
size_t array_innerSize(const array *const arr);

// Sets number of elements.
int array_setCapacity(array *const arr
	                   , const size_t elems);


#endif