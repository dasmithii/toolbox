#ifndef _BASELINE_DEBUG_HELPERS
#define _BASELINE_DEBUG_HELPERS
#include <assert.h>

#define bl_assume_m(cond, on_fail) \
	assert((cond) && (on_fail))

#define bl_assume(cond) \
	bl_assume_m((cons), DEFAULT )


#endif