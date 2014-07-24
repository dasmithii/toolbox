#ifndef _FLUX_LINKED_LIST_UTILITY_
#define _FLUX_LINKED_LIST_UTILITY_
#include <stdlib.h>



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


// Instanciates preallocated list.
void fllist_init(fllist *const list
	           , const size_t elem_size);

// Deallocates all list elements.
void fllist_clear(fllist *const list);

// Frees all internal memory.
void fllist_clean(fllist *const list);

// Clones to preallocated memory block.
int fllist_copy(const fllist *const
	          , fllist *const);

// Allocates, clones, and returns copied list.
fllist *fllist_clone(const fllist *const list);

// Appends data from given address.
int fllist_append(fllist *const list
	            , const void *const element);

// Prepends data from given address.
int fllist_prepend(fllist *const list
	             , const void* const element);

// Inserts data from given address.
int fllist_insert(fllist *const list
	             , const unsigned index
	             , const void *const element);

// Copies data at given address to given index.
void fllist_set(fllist *const list
	          , const unsigned index
	          , const void *const element);

// Returns pointer to location where item <index> is stored.
void *fllist_hook(const fllist *const list
	            , const unsigned index);

// Hooks first element.
void *fllist_hookHead(const fllist *const list);

// Hooks last element.
void *fllist_hookLast(const fllist *const list);

// Copies data at given index to given address.
void fllist_fetch(const fllist *const list
	            , const unsigned index
	            , void *const destination);

// Fetches first element.
void fllist_fetchHead(const fllist *const list
	                , void *const destination);

// Fetches last element.
void fllist_fetchLast(const fllist *const list
	                , void *const destination);

// Removes item at given index, shifting subsquent items
// leftward.
void fllist_remove(fllist *const list
	             , const unsigned index);

// Removes last element.
void fllist_pop(fllist *const list);

// Removes first element.
void fllist_popf(fllist *const list);

// Applies given function to each element.
void fllist_each(fllist *const list, void (*function)(void*));

// Reverses items in list.
void fllist_reverse(fllist *const list);

// Applies bubblesort.
void fllist_sort(fllist *const list, int (*compare)(const void*, const void*));

// Returns bytes in each node.
size_t fllist_nodeSize(const fllist *const list);

// Counts elements in list.
size_t fllist_size(const fllist *const list);


#endif