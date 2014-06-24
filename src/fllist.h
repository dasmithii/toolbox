#ifndef _FLUX_LINKED_LIST_UTILITY_
#define _FLUX_LINKED_LIST_UTILITY_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "debug.h"



// Represents one item in the linked list.
typedef struct fllist_node {
	struct fllist_node *next;
	void *data;
} fllist_node;

// Represents a forward linked list.
typedef struct {
	fllist_node *first;
	fllist_node *last;
	size_t elem_size;
} fllist;

// Management.
void fllist_init(fllist *const, const size_t);
void fllist_clear(fllist *const);
void fllist_clean(fllist *const);
int fllist_cloneTo(const fllist *const, fllist *const);
fllist *fllist_clone(const fllist *const);

// Value storage.
int fllist_append(fllist *const, const void *const);
int fllist_prepend(fllist *const, const void* const);
int fllist_insert(fllist *const, const unsigned, const void *const);
void fllist_set(fllist *const, const unsigned, const void *const);

// Value fetching.
void *fllist_hook(const fllist *const, const unsigned);
void *fllist_hookHead(const fllist *const);
void *fllist_hookLast(const fllist *const);
void fllist_fetch(const fllist *const, const unsigned, void *const);
void fllist_fetchHead(const fllist *const, void *const);
void fllist_fetchLast(const fllist *const, void *const);

// Value removal.
void fllist_remove(fllist *const, const unsigned);
void fllist_pop(fllist *const);
void fllist_popf(fllist *const);

// Special functions.
void fllist_each(fllist *const, void (*)(void*));
void fllist_reverse(fllist *const);
void fllist_sort(fllist *const, int (*)(const void*, const void*));

// Helper functions.
size_t fllist_nodeSize(const fllist *const);
size_t fllist_size(const fllist *const);




#endif