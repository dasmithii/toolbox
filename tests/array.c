#include "common.h"
#include "../sources/array.h"
#include "../sources/memory.h"
#include "greatest.h"


#define SETUP_ARRAY() \
	Array arr;        \
	Array_init(&arr, ITERS, sizeof(int))

#define CLEAN_ARRAY()  \
	Array_clean(&arr); \
	PASS()

TEST Array_hook_test(){
	SETUP_ARRAY();
	for(int i = 0; i < ITERS; ++i){
		int *hooked  = Array_hook(&arr, i);
		int *indexed = blockIndex(arr.data, i, sizeof(int));
		ASSERT_EQ(hooked, indexed);
	}
	CLEAN_ARRAY();
}

TEST Array_set_test(){
	SETUP_ARRAY();
	for(int i = 0; i < ITERS; ++i)
		Array_set(&arr, i, &i);
	for(int i = 0; i < ITERS; ++i){
		int *elem = Array_hook(&arr, i);
		ASSERT_EQ(*elem, i);
	}
	CLEAN_ARRAY();
}

TEST Array_fetch_test(){
	SETUP_ARRAY();
	for(int i = 0; i < ITERS; ++i)
		Array_set(&arr, i, &i);
	for(int i = 0; i < ITERS; ++i){
		int elem;
		Array_fetch(&arr, i, &elem);
		ASSERT_EQ(elem, i);
	}
	CLEAN_ARRAY();
}

TEST Array_zero_test(){
	SETUP_ARRAY();
	Array_zero(&arr);
	for(int i = 0; i < ITERS; ++i){
		int *elem = Array_hook(&arr, i);
		ASSERT_EQ(*elem, 0);
	}
	CLEAN_ARRAY();
}

TEST Array_fill_test(){
	SETUP_ARRAY();
	int value = 5;
	Array_fill(&arr, &value);
	for(int i = 0; i < ITERS; ++i){
		int *elem = Array_hook(&arr, i);
		ASSERT_EQ(*elem, value);
	}
	CLEAN_ARRAY();
}


TEST Array_reverse_test(){
	SETUP_ARRAY();
	for(int i = 0; i < ITERS; ++i)
		Array_set(&arr, i, &i);
	Array_reverse(&arr);
	for(int i = 0; i < ITERS; ++i){
		int *elem = Array_hook(&arr, i);
		ASSERT_EQ(*elem, ITERS - 1 - i);
	}
	CLEAN_ARRAY();
}

static int int_cmp(const void *p1, const void *p2){
	const int *e1 = p1, *e2 = p2;
	if(*e1 > *e2)
		return 1;
	else if(*e2 > *e1)
		return -1;
	return 0;
}

TEST Array_sort_test(){
	SETUP_ARRAY();
	for(int i = 0; i < ITERS; ++i){
		int r = rand();
		Array_set(&arr, i, &r);
	}
	Array_sort(&arr, int_cmp);
	for(int i = 0; i < ITERS - 1; ++i){
		int *e1 = Array_hook(&arr, i);
		int *e2 = Array_hook(&arr, i + 1);
		ASSERT(*e1 < *e2);
	}
	CLEAN_ARRAY();	
}

GREATEST_SUITE(Array_suite){
	RUN_TEST(Array_hook_test);
	RUN_TEST(Array_set_test);
	RUN_TEST(Array_fetch_test);
	RUN_TEST(Array_zero_test);
	RUN_TEST(Array_fill_test);
	RUN_TEST(Array_reverse_test);
	RUN_TEST(Array_sort_test);
}