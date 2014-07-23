#include "vector.h"
#define DEFAULT_CAPACITY 25

// --------------------------------------------------------------- //
int vector_init(vector *const vec, const size_t elem_size)
{
	assume_ptr(vec);
	assume_m(elem_size > 0, "Attempted to initialize vector with elem_size 0.");

	// attempt inits
	vec->size = 0;
	int rc = array_init(&vec->buffer, DEFAULT_CAPACITY, elem_size);

	// check for allocation error
	if(rc)
		return -1;
	return 0;
}

// --------------------------------------------------------------- //
void vector_clean(vector *const vec)
{
	assume_ptr(vec);
	array_clean(&vec->buffer);
	vec->size = 0;
}

// --------------------------------------------------------------- //
int vector_append(vector *const vec, const void *const ptr)
{
	assume_ptrs(vec, ptr);

	// check capacity
	if(vec->size == vec->buffer.num_elems){
		int rc = vector_expand(vec);
		if(rc)
			return -1;
	}

	// insert element
	vector_set(vec, vec->size, ptr);
	vec->size++;
	return 0;
}

// --------------------------------------------------------------- //
int vector_prepend(vector *const vec, const void *const ptr)
{
	return vector_insert(vec, 0, ptr);
}

// --------------------------------------------------------------- //
void vector_fetch(const vector *const vec, const unsigned i, void *const to)
{
	assume_ptrs(vec, to);
	assume_ceil(i, vec->size);

	void *ptr = vector_hook(vec, i);
	memcpy(to, ptr, vec->buffer.elem_size);
}

// --------------------------------------------------------------- //
void vector_fetchLast(const vector *const vec, void *const to)
{
	assume_pos(vec->size);
	void *ptr = vector_hookLast(vec);
	memcpy(to, ptr, vec->buffer.elem_size);
}

// --------------------------------------------------------------- //
void vector_fetchHead(const vector *const vec, void *const to)
{
	assume_ptrs(vec, to);
	assume_pos(vec->size);
	memcpy(to, vec->buffer.data, vec->buffer.elem_size);
}

// --------------------------------------------------------------- //
void *vector_hook(const vector *const vec, const unsigned i)
{
	assume_ptr(vec);
	assume_max(i, vec->size);
	return array_hook(&vec->buffer, i);
}

// --------------------------------------------------------------- //
int vector_insert(vector *const vec, const unsigned i, const void *const ptr)
{
	assume_ptrs(vec, ptr);
	assume_max(i, vec->size + 1);

	// ensure capacity
	if(vec->size == vec->buffer.num_elems){
		int rc = vector_expand(vec);
		if(rc)
			return -1;
	}

	// shift elements
	char *spot = vector_hook(vec, i);
	size_t size = (vec->size - i) * vec->buffer.elem_size;
	memmove(spot + vec->buffer.elem_size, spot, size);
	memcpy(spot, ptr, vec->buffer.elem_size);
	vec->size++;
	return 0;
}

// --------------------------------------------------------------- //
void vector_remove(vector *const vec, const int i)
{
	assume_ptr(vec);
	assume_ceil(i, vec->size);

	void *elem = vector_hook(vec, i);
	void *next = elem + vec->buffer.elem_size;
	size_t blocks = vec->size - i - 1;
	size_t bytes  = blocks * vec->buffer.elem_size;
	memmove(elem, next, bytes);
	vec->size--;
}

// --------------------------------------------------------------- //
void vector_reverse(vector *const vec)
{
	assume_ptr(vec);

	// hook pivot point
	int piv = vec->size / 2;

	// swap blocks
	char *lb = vec->buffer.data;
	for(int i = 0; i < piv; ++i){
		char *rb = vector_hook(vec, vec->size - i - 1);
		for(int b = 0; b < vec->buffer.elem_size; ++b){
			char tmp = *lb;
			*lb = *rb;
			*rb = tmp;
			++rb;
			++lb;
		}
	}

}

// --------------------------------------------------------------- //
vector *vector_clone(const vector *const vec)
{
	assume_ptr(vec);

	// allocate new vector
	vector *ret = malloc(sizeof(vector));
	if(!ret)
		return NULL;

	// allocate & copy internal memory
	int rc = array_copy(&vec->buffer, &ret->buffer);
	if(rc){
		free(ret);
		return NULL;
	}

	ret->size = vec->size;
	return ret;
}

// --------------------------------------------------------------- //
void vector_popf(vector *const vec)
{
	assume_ptr(vec);
	assume_pos(vec->size);

	// shift elements
	for(int i = 0; i < vec->size - 1; i++){
		void *to = vector_hook(vec, i);
		vector_fetch(vec, i + 1, to);
	}
}

// --------------------------------------------------------------- //
void vector_pop(vector *const vec)
{
	assume_ptr(vec);
	assume_pos(vec->size);
	vec->size--;
}

// --------------------------------------------------------------- //
void vector_clear(vector *const vec)
{
	assume_ptr(vec);
	vec->size = 0;
	vector_setCapacity(vec, DEFAULT_CAPACITY);
}

// --------------------------------------------------------------- //
void vector_each(vector *const vec, void (*func)(void*))
{
	assume_ptrs(vec, func);
	char *elem = vec->buffer.data;
	for(int i = 0; i < vec->size; ++i){
		func((void*) elem);
		elem += vec->buffer.elem_size;
	}
}

// --------------------------------------------------------------- //
int vector_setCapacity(vector *const vec, const size_t n)
{
	assume_ptr(vec);
	assume_pos(n);
	assume_m(n >= vec->size, "Capacity below size.");
	return array_setCapacity(&vec->buffer, n);
}

// --------------------------------------------------------------- //
int vector_reserve(vector * const vec, const size_t n)
{
	assume_ptr(vec);
	assume_pos(n);

	if(vec->buffer.num_elems < n)
		return vector_setCapacity(vec, n);
	return 0;
}

// --------------------------------------------------------------- //
void vector_set(vector *const vec, const unsigned i, const void *const elem)
{
	assume_ptrs(vec, elem);
	assume_max(i, vec->size);
	void *dest = vector_hook(vec, i);
	memcpy(dest, elem, vec->buffer.elem_size);
}

// --------------------------------------------------------------- //
int vector_expand(vector *const vec)
{
	assume_ptr(vec);
	int cap = vec->buffer.num_elems * 2;
	return vector_setCapacity(vec, cap);
}

// --------------------------------------------------------------- //
int vector_contract(vector *const vec)
{
	assume_ptr(vec);
	return vector_setCapacity(vec, vec->size);
}

// --------------------------------------------------------------- //
void *vector_hookLast(const vector *const vec)
{
	int i = vec->size - 1;
	return vector_hook(vec, i);
}

// --------------------------------------------------------------- //
void *vector_hookHead(const vector *const vec)
{
	return vec->buffer.data;
}

// --------------------------------------------------------------- //
void vector_sort(vector *const vec, int (*cmp)(const void*, const void*))
{
	array_sort(&vec->buffer, cmp);
}
