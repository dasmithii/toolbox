#ifndef _BASELINE_VECTOR_
#define _BASELINE_VECTOR_
#include "debug.h"
#include "array.h"
#include <stdlib.h>
#include <string.h>

// Stores a contiguous, dynamically-sized array of elements. 
typedef struct {
	array buffer;
	size_t size;
} vector;

// Initializer & cleaner.
int vector_init(vector *const, const size_t);
void vector_clean(vector *const);
int vector_append(vector *const, const void *const);
int vector_prepend(vector*const, const void *const);
int vector_insert(vector *const, const unsigned, const void *const);
void vector_remove(vector *const, const int);
vector *vector_clone(const vector *const);
void vector_popf(vector *const);
void vector_pop(vector *const);
void vector_clear(vector *const);
void vector_set(vector *const, const unsigned, const void *const);

void vector_each(vector *const, void (*)(void*));
void vector_reverse(vector *const);
void vector_sort(vector *const, int (*)(const void*, const void*));

void vector_fetch(const vector *const, const unsigned, void *const);
void vector_fetchLast(const vector *const, void *const);
void vector_fetchHead(const vector *const, void *const);
void *vector_hook(const vector *const, const unsigned);
void *vector_hookLast(const vector *const);
void *vector_hookHead(const vector *const);
int vector_setCapacity(vector *const, const size_t);
int vector_reserve(vector *const, const size_t);
int vector_expand(vector *const);
int vector_contract(vector *const);

#endif