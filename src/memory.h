#ifndef _BASELINE_MEMORY_UTILITIES_
#define _BASELINE_MEMORY_UTILITIES_
#include <string.h>
#include "debug.h"


// Swaps n-sized blocks of memory at given addresses.
void fx_swap(void *const addr1
	       , void *const addr2
	       , const size_t size);

// Reverses memory blocks of given size.
void fx_reverse(const void *const addr
	          , const size_t num_elems
	          , const size_t elem_size);

// Offsets memory address of any pointer type by <n> bytes.
void *fx_offset(const void *const addr
              , const int bytes);

// Indexes into <addr> a though it an array.
void *fx_index(const void *const addr
                    , const size_t index
                    , const size_t elem_size);

// Zeros memory block.
void fx_zero(void *const addr
	       , const size_t len);

// Frees pointer unless its value is NULL.
void fx_safeFree(const void *const ptr);

// Returns pointer to an independent copy of data pointed
// to by <ptr>. NULL on failure.
void *fx_cloneBytes(const void *const ptr
	              , const size_t bytes);

#endif