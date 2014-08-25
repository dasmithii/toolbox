#include "../sources/bits.h"
#include <kit/greatest.h>
#include <limits.h>


TEST bits_basic(){
	unsigned int n = 0;
	FLAG_BIT(n, 0);
	printf("HERE: %u\n", n);
	ASSERT(GET_BIT(n, 0) == true);
	ASSERT(GET_BIT(n, 1) == false);
	CLEAR_BIT(n, 0);
	ASSERT(GET_BIT(n, 0) == false);
	TOGGLE_BIT(n, 0);
	ASSERT(GET_BIT(n, 0) == true);
	TOGGLE_BIT(n, 0);
	ASSERT(GET_BIT(n, 0) == false);
	PASS();
}


TEST bits_extras()
{
	unsigned char n = 0;
	for(int i = 0; i < CHAR_BIT; ++i)
		ASSERT(GET_BIT(n, i) == false);
	FLAG_BIT(n, 0);
	ASSERT(GET_BIT(n, 0) == true);
	for(int i = 1; i < CHAR_BIT; ++i)
		ASSERT(GET_BIT(n, i) == false);
	PASS();
}



GREATEST_SUITE(bits_suite){
	RUN_TEST(bits_basic);
	RUN_TEST(bits_extras);
}