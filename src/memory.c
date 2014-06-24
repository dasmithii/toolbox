#include "memory.h"

// ---------------------------------------------------------- //
void fx_swap(void *const addr1
	       , void *const addr2
	       , const size_t size)
{
	fx_checkPtrs(addr1, addr2);
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
void fx_reverse(const void *const addr
	          , const size_t num_elems
	          , const size_t elem_size)
{
	fx_checkPtr(addr);
	fx_assert(elem_size != 0, "Non-positive array element size.");
	for(int i = 0; i < num_elems / 2; ++i){
		void *const p1 = fx_index(addr, elem_size, i);
		void *const p2 = fx_index(addr, elem_size, num_elems - i - 1);
		fx_swap(p1, p2, elem_size);
	}
}

// ---------------------------------------------------------- //
void *fx_offset(const void *const addr
              , const int bytes)
{
	fx_checkPtr(addr);
	return (void*) (((char*) addr) + bytes);
}

// ---------------------------------------------------------- //
void *fx_index(const void *const addr
             , const size_t index
             , const size_t elem_size)
{
	fx_checkPtr(addr);
	fx_assert(elem_size > 0, "Non-positive array element size.");
	return fx_offset(addr, elem_size * index);
}

// ---------------------------------------------------------- //
void fx_zero(void *const addr
	       , const size_t len)
{
	fx_checkPtr(addr);
	memset(addr, 0, len);
}

// ---------------------------------------------------------- //
void fx_safeFree(const void *const ptr){
	if(ptr)
		free(ptr);
}

// ---------------------------------------------------------- //
void *fx_cloneBytes(const void *const ptr
	              , const size_t bytes){
	fx_checkPtr(ptr);
	void *const ret = malloc(bytes);
	if(!ret)
		return NULL;
	memcpy(ret, ptr, bytes);
	return ret;
}
