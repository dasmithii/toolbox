#include "../sources/circle.h"
#include <kit/greatest.h>


#define SETUP_CIRCLE()  \
	Circle c;           \
	Circle_init(&c, sizeof(int))

#define CLEAN_CIRCLE()  \
	Circle_clean(&c);   \
	PASS()


TEST Circle_basic_test(){
	SETUP_CIRCLE();
	for(int i = 0; i < 3; ++i)
		Circle_insert(&c, &i);
	for(int loop = 0; loop < 5; ++loop){
		for(int i = 0; i < 3; ++i){
			int j;
			Circle_fetch(&c, &j);
			ASSERT_EQ(2 - i, j);
			Circle_shift(&c);
		}
	}
	CLEAN_CIRCLE();
}


GREATEST_SUITE(Circle_suite){
	RUN_TEST(Circle_basic_test);
}