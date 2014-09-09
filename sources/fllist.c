#include "fllist.h"
#include "error.h"
#include <string.h>


void FLList_init(FLList *self, size_t elementSize)
{
	self->elementSize = elementSize;
	self->firstElement = NULL;
}


void FLList_clean(FLList *self)
{
	FLList_clear(self);
	self->elementSize = 0;
}


static inline void setNext(void *data, size_t offset, void *next)
{
	void *dest = (char*) data + offset;
	memcpy(dest, &next, sizeof(void*));
}


static inline void *getNext(void *data, size_t elementSize)
{
	void *next;
	void *addr = (void*) ((char*) data + elementSize);
	memmove(&next, addr, sizeof(void*));
	return next;
}


void FLList_clear(FLList *self)
{
	void *data = self->firstElement;
	while(data){
		void *prev = data;
		data = getNext(prev, self->elementSize);
		free(prev);
	}
}


int FLList_prepend(FLList *self, void *data)
{
	void *node = malloc(self->elementSize + sizeof(void*));
	if(!node) return 1;
	memcpy(node, data, self->elementSize);
	setNext(node, self->elementSize, self->firstElement);
	self->firstElement = node;
	return 0;
}


static inline void *newNode(void *data, size_t elementSize)
{
	void *node = malloc(elementSize + sizeof(void*));
	if(!node) return NULL;
	memcpy(node, data, elementSize);
	setNext(node, elementSize, NULL);
	return node;
}


static inline void *nodeBefore(void *next, void *data, size_t elementSize)
{
	void *node = newNode(data, elementSize);
	setNext(node, elementSize, next);
	return node;
}


static inline int insertAfter(void *n0, void *data, size_t elementSize)
{
	void *n1 = getNext(n0, elementSize);
	void *node = nodeBefore(n1, data, elementSize);
	if(node){
		setNext(n0, elementSize, node);
		return 0;
	}
	return 1;
}


int FLList_append(FLList *self, void *data)
{
	if(self->firstElement){
		return insertAfter(FLList_hookLast(self)
		             	 , data
		                 , self->elementSize);
	} else {
		self->firstElement = newNode(data, self->elementSize);
		return self->firstElement? 0:1;
	}
}



int FLList_insert(FLList *self, void *data, size_t i)
{
	if(i == 0)
		return FLList_prepend(self, data);
	else
		return insertAfter(FLList_hook(self, i)
			              , data
			              , self->elementSize);
}


static inline void squeezeNext(void *n0, size_t elementSize)
{
	void *n1 = getNext(n0, elementSize);
	void *n2 = getNext(n1, elementSize);
	setNext(n0, elementSize, n2);
	free(n1);
}


inline void FLList_removeHead(FLList *self)
{
	void *first = self->firstElement;
	self->firstElement = getNext(first, self->elementSize);
	free(first);
}


void FLList_remove(FLList *self, size_t i)
{
	if(i == 0)
		FLList_removeHead(self);
	else
		squeezeNext(FLList_hook(self, i - 1)
			      , self->elementSize);
}


void FLList_set(FLList *self, size_t i, void *source)
{
	void *dest = FLList_hook(self, i);
	memmove(dest, source, self->elementSize);
}


void *FLList_hook(FLList *self, size_t i)
{
	return FLList_at(self, i).data;
}


void *FLList_hookLast(FLList *self)
{
	void *node = self->firstElement;
	while(node && getNext(node, self->elementSize))
		node = getNext(node, self->elementSize);
	return node;
}


void FLList_fetch(FLList *self, size_t i, void *dest)
{
	void *source = FLList_hook(self, i);
	memmove(dest, source, self->elementSize);
}


void FLList_fetchLast(FLList *self, void *dest)
{
	void *source = FLList_hookLast(self);
	memmove(dest, source, self->elementSize);
}


void FLList_each(FLList *self, void (*function)(void*))
{
	void *data = self->firstElement;
	while(data){
		function(data);
		data = getNext(data, self->elementSize);
	}
}


size_t FLList_length(FLList *self)
{
	size_t n = 0;
	void *data = self->firstElement;
	while(data){
		++n;
		data = getNext(data, self->elementSize);
	}
	return n;
}


static FLListIterator iteratorFrom(void *data, size_t elementSize)
{
	FLListIterator ret;
	ret.data = data;
	ret.next = getNext(data, elementSize);
	ret.elementSize = elementSize;
	return ret;
}


FLListIterator FLList_begin(FLList *self)
{
	return iteratorFrom(self->firstElement, self->elementSize);
} 


FLListIterator FLList_end(FLList *self)
{
	return iteratorFrom(NULL, self->elementSize);
} 


FLListIterator FLList_at(FLList *self, size_t i)
{
	FLListIterator it = FLList_begin(self);
	for(int x = 0; x < i; ++x)
		FLListIterator_advance(&it);
	return it;
} 


FLListIterator FLList_last(FLList *self){
	FLListIterator it = FLList_begin(self);
	while(it.next){
		FLListIterator_advance(&it);
	}
	return it;
}


FLListIterator FLList_next(FLListIterator *self)
{
	FLListIterator it = *self;
	FLListIterator_advance(&it);
	return it;
}


bool FLListIterator_advance(FLListIterator *self)
{
	self->data = self->next;
	self->next = getNext(self->data, self->elementSize);
	return self->data? true:false;
}

