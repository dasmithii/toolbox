#include "../sources/circle.h"
#include "greatest.h"


#define SETUP_CIRCLE()  \
	Circle c;           \
	Circle_init(&c, sizeof(int))

#define CLEAN_CIRCLE()  \
	Circle_clean(&c);   \
	PASS()


TEST Circle_basic_test()
{
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


TEST Circle_removal_test()
{
	SETUP_CIRCLE();

	for(int i = 0; i < 3; ++i)
		Circle_insert(&c, &i);

	int order[] = {2,1,0,1,0,0};
	int *p = order;

	for(int loop = 0; loop < 3; ++loop){
		for(int i = 0; i < Circle_length(&c); ++i){
			int n;
			Circle_fetch(&c, &n);
			ASSERT_EQ(n, *p);
			++p;
			Circle_remove(&c);
		}
	}
	CLEAN_CIRCLE();
}


TEST Circle_fef_test()
{
	SETUP_CIRCLE();

	for(int i = 0; i < 3; ++i)
		Circle_insert(&c, &i);
	
	for(int i = 0; i < 3; ++i)
		Circle_remove(&c);

	for(int i = 0; i < 3; ++i)
		Circle_insert(&c, &i);

	ASSERT_EQ(3, Circle_length(&c));

	CLEAN_CIRCLE();
}



GREATEST_SUITE(Circle_suite){
	RUN_TEST(Circle_basic_test);
	RUN_TEST(Circle_removal_test);
	RUN_TEST(Circle_fef_test);
}