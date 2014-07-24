#include "fllist.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "debug.h"

// --------------------------------------------------------------- //
static fllist_node *fllist_node_hookNode(fllist_node *node, const unsigned i)
{
	for(int n = 0; n < i; ++n){
		if(!node)
			return NULL;
		node = node->next;
	}
	return node;
}

// --------------------------------------------------------------- //
static fllist_node *fllist_hookNode(const fllist *const list, const unsigned i)
{
	if(list->first)
		return fllist_node_hookNode(list->first, i);
	return NULL;
}

// --------------------------------------------------------------- //
void fllist_init(fllist *const list, const size_t elem_size)
{
	assume_ptr(list);
	list->first = NULL;
	list->last  = NULL;
	list->elem_size = elem_size;
}

// --------------------------------------------------------------- //
void fllist_clear(fllist *const list)
{
	assume_ptr(list);
	fllist_node *node = list->first;
	while(node){
		fllist_node *next = node->next;
		free(node);
		node = next;
	}
	list->first = NULL;
	list->last  = NULL;
}

// --------------------------------------------------------------- //
void fllist_clean(fllist *const list)
{
	fllist_clear(list);
}

// --------------------------------------------------------------- //
int fllist_copy(const fllist *const list, fllist *const to)
{
	assume_ptrs(list, to);
	fllist_init(to, list->elem_size);

	fllist_node *node = list->first;
	while(node){
		int rc = fllist_append(to, &node->data);
		if(rc){
			fllist_clear(to);
			return -1;
		}
		node = node->next;
	}
	return 0;
}

// --------------------------------------------------------------- //
fllist *fllist_clone(const fllist *const list)
{
	assume_ptr(list);
	fllist *ret = malloc(sizeof(fllist));
	if(!ret)
		return NULL;

	int rc = fllist_copy(list, ret);
	if(rc){
		free(ret);
		return NULL;
	}
	return ret;
}

// --------------------------------------------------------------- //
int fllist_append(fllist *const list, const void *const elem)
{
	assume_ptrs(list, elem);
	fllist_node *node = malloc(fllist_nodeSize(list));
	if(!node)
		return -1;
	memmove(&node->data, elem, list->elem_size);
	node->next = NULL;

	if(list->last){
		list->last->next = node;
		list->last = node;
	} else {
		list->first = node;
		list->last = node;
	}
	return 0;
}

// --------------------------------------------------------------- //
int fllist_prepend(fllist *const list, const void *const elem)
{
	assume_ptrs(list, elem);
	fllist_node *node = malloc(fllist_nodeSize(list));
	if(!node)
		return -1;
	memmove(&node->data, elem, list->elem_size);
	node->next = list->first;
	list->first = node;
	if(!list->last)
		list->last = node;
	return 0;
}

// --------------------------------------------------------------- //
int fllist_insert(fllist *const list, const unsigned i, const void *const elem)
{
	assume_ptrs(list, elem);
	if(i == 0)
		return fllist_prepend(list, elem);

	// Create node.
	fllist_node *node = malloc(fllist_nodeSize(list));
	if(!node)
		return -1;
	memmove(&node->data, elem, list->elem_size);

	// Find predecessor.
	fllist_node *prev = fllist_hookNode(list, i-1);

	assume_ptr(prev);
	node->next = prev->next;
	prev->next = node;
	return 0;
}

// --------------------------------------------------------------- //
void fllist_set(fllist *const list, const unsigned i, const void *const src)
{
	assume_ptrs(list, src);
	void *dest = fllist_hook(list, i);
	assume_ptr(dest);
	memcpy(dest, src, list->elem_size);
}

// --------------------------------------------------------------- //
void fllist_fetch(const fllist *const list, const unsigned i, void *const dest)
{
	assume_ptrs(list, dest);
	void *src = fllist_hook(list, i);
	assume_ptr(src);
	memcpy(dest, src, list->elem_size);
}

// --------------------------------------------------------------- //
void fllist_fetchHead(const fllist *const list, void *const dest)
{
	assume_ptrs(list, dest);
	assume_m(list->first, "Empty list.");
	void *src = fllist_hookLast(list);
	memcpy(dest, src, list->elem_size);
}

// --------------------------------------------------------------- //
void fllist_fetchLast(const fllist *const list, void *const dest)
{
	assume_ptrs(list, dest);
	assume_m(list->last, "Empty list.");
	void *src = fllist_hookLast(list);
	memcpy(dest, src, list->elem_size);
}

// --------------------------------------------------------------- //
void fllist_remove(fllist *const list, const unsigned i)
{
	assume_ptr(list);
	if(i == 0){
		if(list->first)
			fllist_popf(list);
	} else {
		fllist_node *prev = fllist_hookNode(list, i-1);
		if(prev && prev->next){
			prev->next = prev->next->next;
			free(prev->next);
		} else {
			assume(-1);
		}
	}
}

// --------------------------------------------------------------- //
void fllist_pop(fllist *const list)
{
	assume_ptr(list);
	if(!list->first)
		return;

	// hook second-to-last node
	fllist_node *node = list->first;
	while(node->next && node->next->next)
		node = node->next;
	node->next = NULL;
	free(list->last);
	list->last = node;
}

// --------------------------------------------------------------- //
void fllist_popf(fllist *const list)
{
	if(!list->first)
		return;
	fllist_node *node = list->first;
	list->first = node->next;
	free(node);
}

// --------------------------------------------------------------- //
void fllist_each(fllist *const list, void (*func)(void*))
{
	assume_ptr(list);
	fllist_node *node = list->first;
	while(node){
		func(&node->data);
		node = node->next;
	}
}

// --------------------------------------------------------------- //
void fllist_reverse(fllist *const list)
{
	assume_ptr(list);
	fllist_node *prev = NULL
			   , *node = list->first;

	while(node){
		fllist_node *next = node->next;
		node->next = prev;
		prev = node;
		node = next;
	}

	node = list->first;
	list->first = list->last;
	list->last  = node;
}

// --------------------------------------------------------------- //
void fllist_sort(fllist *const list, int (*cmp)(const void*, const void*))
{
	assume_ptrs(list, cmp);
	bool swap;
	do {
		swap = false;
		fllist_node *n0 = NULL
				   , *n1 = list->first
				   , *n2 = n1->next;
		while(n2){
			int c = cmp(&n1->data, &n2->data);
			if(c > 0){
				// flip n1 and n2
				n1->next = n2->next;
				n2->next = n1;
				if(n0)
					n0->next = n2;
				else
					list->first = n2;
				fllist_node *tmp = n1;
				n1 = n2;
				n2 = tmp;
				swap = true;
			}
			// shift to next node
			n0 = n1;
			n1 = n2;
			n2 = n2->next;
		}

		if(list->last->next)
			list->last = list->last->next;
	} while(swap);
}

// --------------------------------------------------------------- //
void *fllist_hook(const fllist *const list, const unsigned i)
{
	assume_ptr(list);
	fllist_node *node = list->first;
	for(int n = 0; n < i; ++n){
		if(!node)
			return NULL;
		node = node->next;
	}
	return &node->data;
}

// --------------------------------------------------------------- //
void *fllist_hookHead(const fllist *const list)
{
	fllist_node *node = list->first;
	if(node)
		return &node->data;
	return NULL;
}

// --------------------------------------------------------------- //
void *fllist_hookLast(const fllist *const list)
{
	fllist_node *node = list->last;
	if(node)
		return &node->data;
	return NULL;
}

// --------------------------------------------------------------- //
size_t fllist_nodeSize(const fllist *const list)
{
	assume_ptr(list);
	return sizeof(fllist_node) - sizeof(void*) + list->elem_size;
}

// --------------------------------------------------------------- //
size_t fllist_size(const fllist *const list)
{
	assume_ptr(list);
	size_t ret = 0;
	fllist_node *node = list->first;
	while(node){
		++ret;
		node = node->next;
	}
	return ret;
}