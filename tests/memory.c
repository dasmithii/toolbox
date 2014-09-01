#include "common.h"
#include "../sources/memory.h"
#include <kit/greatest.h>

TEST memory_swap(){
	int data[2] = {5, 10};
	swap(data, data + 1, sizeof(int));
	ASSERT_EQ(data[0], 10);
	ASSERT_EQ(data[1], 5);
	PASS();
}

TEST memory_reverse(){
	int rev4[] = {1,2,3,4},
		rev5[] = {1,2,3,4,5},
		ans4[] = {4,3,2,1},
		ans5[] = {5,4,3,2,1};
	reverse(rev4, 4, sizeof(int));
	reverse(rev5, 5, sizeof(int));
	for(int i = 0; i < 4; ++i)
		ASSERT_EQ(rev4[i], ans4[i]);
	for(int i = 0; i < 5; ++i)
		ASSERT_EQ(rev5[i], ans5[i]);
	PASS();
}

TEST memory_offset(){
	char i = 'f';
	char *p1 = &i;
	char *p2 = p1 + 4;
	ASSERT_EQ(p2, offset(p1, 4));
	PASS();
}

TEST memory_blockIndex(){
	int i = 4;
	int *p1 = &i;
	int *p2 = p1 + 5;
	int *p3 = blockIndex(p1, 5, sizeof(int));
	ASSERT_EQ(p2, p3);
	PASS();
}

TEST memory_zero(){
	int ns[5] = {234,26,74,34,43};
	zero(&ns, 5 * sizeof(int));
	for(int i = 0; i < 5; ++i)
		ASSERT_EQ(ns[i], 0);
	PASS();
}

GREATEST_SUITE(memory_suite){
	RUN_TEST(memory_swap);
	RUN_TEST(memory_reverse);
	RUN_TEST(memory_offset);
	RUN_TEST(memory_blockIndex);
	RUN_TEST(memory_zero);
}