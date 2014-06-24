#include "array.h"

// --------------------------------------------------------------- //
int array_init(array *const arr
	            , const size_t num_elems
	            , const size_t elem_size){
	assume_ptr(arr);
	assume_m(elem_size > 0, "Non-positive array element size.");
	arr->num_elems = num_elems;
	arr->elem_size = elem_size;
	arr->data = calloc(num_elems, elem_size);
	return arr->data? 0:1;
}

// --------------------------------------------------------------- //
void array_clean(array *const arr){
	assume_ptr(arr);
	if(arr->data)
		free(arr->data);
}

// --------------------------------------------------------------- //
array *array_new(const size_t num_elems
	                 , const size_t elem_size){
	array *ret = malloc(sizeof(array));
	if(!ret)
		return NULL;
	array_init(ret, num_elems, elem_size);
	return ret;
}

// --------------------------------------------------------------- //
void array_free(array *const arr){
	assume_ptr(arr);
	array_clean(arr);
	free(arr);
}

// --------------------------------------------------------------- //
void *array_hook(const array *const arr
	              , const size_t i){
	assume_ptr(arr);
	assume_m(i < arr->num_elems, "Index out of bounds.");
	return arr->data + arr->elem_size * arr->num_elems;
}

// --------------------------------------------------------------- //
void array_set(array *const arr
	            , const size_t i
	            , const void *const ptr){
	assume_ptrs(arr, ptr);
	assume_m(i < arr->num_elems, "Index out of bounds.");
	memmove(array_hook(arr, i), ptr, arr->elem_size);
}

// --------------------------------------------------------------- //
void array_fetch(const array *const arr
	              , const size_t i
	              , void *const dest){
	assume_ptrs(arr, dest);
	memmove(dest, array_hook(arr, i), arr->elem_size);
}

// --------------------------------------------------------------- //
void array_zero(array *const arr){
	assume_ptr(arr);
	memset(arr->data, 0, arr->elem_size * arr->num_elems);
}

// --------------------------------------------------------------- //
void array_fill(array *const arr
	              , const void *const val){
	assume_ptrs(arr, val);
	for(int i = 0; i < arr->num_elems; ++i)
		array_set(arr, i, val);
}

// --------------------------------------------------------------- //
void array_reverse(array *const arr){
	assume_ptr(arr);
	reverse(arr, arr->num_elems, arr->elem_size);
}

// --------------------------------------------------------------- //
void array_sort(array *const arr
	             , int (*cmp)(const void*, const void*)){
	assume_ptrs(arr, cmp);
	qsort(arr->data, arr->num_elems, arr->elem_size, cmp);
}

// --------------------------------------------------------------- //
void array_each(array *const arr
	             , void (*func)(void*)){
	for(int i = 0; i < arr->num_elems; ++i)
		func(array_hook(arr, i));
}

// --------------------------------------------------------------- //
int array_copy(const array *const src
	            , array *const dest){
	assume_ptrs(src, dest);
	dest->num_elems = src->num_elems;
	dest->elem_size = src->elem_size;
	dest->data = malloc(src->elem_size * src->num_elems);
	if(!dest->data)
		return 1;
	memcpy(dest->data, src->data, src->elem_size * src->num_elems);
	return 0;
}

// --------------------------------------------------------------- //
array *array_clone(const array *const arr){
	array *ret = malloc(sizeof(array));
	if(!ret)
		return NULL;
	int rc = array_copy(arr, ret);
	if(rc){
		free(ret);
		return NULL;
	}
	return ret;
}

// --------------------------------------------------------------- //
size_t array_innerSize(const array *const arr){
	return arr->elem_size * arr->num_elems;
}

// --------------------------------------------------------------- //
int array_setCapacity(array *const arr, const size_t elems)
{
	void *np = realloc(arr->data, arr->elem_size * elems);
	if(!np)
		return -1;
	arr->data = np;
	arr->num_elems = elems;
	return 0;
}


