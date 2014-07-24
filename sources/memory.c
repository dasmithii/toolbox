#include "memory.h"

// ---------------------------------------------------------- //
void swap(void *const addr1
	    , void *const addr2
	    , const size_t size)
{
	assume_ptrs(addr1, addr2);
	char *ptr1 = (char*) addr1;
	char *ptr2 = (char*) addr2;
	for(int b = 0; b < size; ++b){
		const char c = *ptr1;
		*ptr1 = *ptr2;
		*ptr2 = c;
		++ptr1; ++ptr2;
	}
}

// ---------------------------------------------------------- //
void reverse(const void *const addr
	       , const size_t num_elems
	       , const size_t elem_size)
{
	assume_ptr(addr);
	assume_nzero(elem_size);
	for(int i = 0; i < num_elems / 2; ++i){
		void *const p1 = block_index(addr, i, elem_size);
		void *const p2 = block_index(addr, num_elems - i - 1, elem_size);
		swap(p1, p2, elem_size);
	}
}

// ---------------------------------------------------------- //
void *offset(const void *const addr
           , const int bytes)
{
	assume_ptr(addr);
	return (void*) (((char*) addr) + bytes);
}

// ---------------------------------------------------------- //
void *block_index(const void *const addr
             , const size_t block_index
             , const size_t elem_size)
{
	assume_ptr(addr);
	assume_pos(elem_size);
	return offset(addr, elem_size * block_index);
}

// ---------------------------------------------------------- //
void zero(void *const addr
	       , const size_t len)
{
	assume_ptr(addr);
	memset(addr, 0, len);
}

// ---------------------------------------------------------- //
void safe_free(void *const ptr){
	if(ptr)
		free(ptr);
}

// ---------------------------------------------------------- //
void *clone_bytes(const void *const ptr
	              , const size_t bytes){
	assume_ptr(ptr);
	void *const ret = malloc(bytes);
	if(!ret)
		return NULL;
	memcpy(ret, ptr, bytes);
	return ret;
}