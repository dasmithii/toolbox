#include "circle.h"


void *Circle_next(Circle *self){
	void *next = FLList_next(&self->list, self->item);
	return next? next : self->list.firstElement;
}


void Circle_init(Circle *self, size_t elementSize){
	self->item = NULL;
	FLList_init(&self->list, elementSize);
}


void Circle_clean(Circle *self){
	FLList_clean(&self->list);
	self->item = NULL;
}


void *Circle_hook(Circle *self){
	return Circle_next(self);
}


void Circle_fetch(Circle *self, void *dest){
	void *source = Circle_next(self);
	memmove(dest, source, self->list.elementSize);
}


void Circle_shift(Circle *self){
	if(self->item)
		self->item = Circle_next(self);
}


int Circle_insert(Circle *self, void *data){
	if(self->item)
		return FLList_insertAfter(&self->list, self->item, data);
	int r = FLList_insert(&self->list, data, 0);
	self->item = self->list.firstElement;
	return r;
}


void Circle_remove(Circle *self){
	FLList_removeNext(&self->list, self->item);
}


void Circle_each(Circle *self, void (*function)(void*)){
	FLList_each(&self->list, function);
}
