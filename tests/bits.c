#include "../sources/bits.h"
#include <kit/greatest.h>


TEST bits_test(){
	unsigned int n = 0;
	FLAG_BIT(n, 0);
	ASSERT_EQ(GET_BIT(n, 0), true);
	CLEAR_BIT(n, 0);
	ASSERT_EQ(GET_BIT(n, 0), false);
	TOGGLE_BIT(n, 0);
	ASSERT_EQ(GET_BIT(n, 0), true);
	TOGGLE_BIT(n, 0);
	ASSERT_EQ(GET_BIT(n, 0), false);
	PASS();
}

GREATEST_SUITE(bits_suite){
	RUN_TEST(bits_test);
}