#include "common.h"
#include "../sources/array.h"
#include "../sources/memory.h"
#include <kit/greatest.h>


#define SETUP_ARRAY() \
	array arr;        \
	array_init(&arr, ITERS, sizeof(int))

#define CLEAN_ARRAY()  \
	array_clean(&arr); \
	PASS()

TEST array_hook_test(){
	SETUP_ARRAY();
	for(int i = 0; i < ITERS; ++i){
		int *hooked  = array_hook(&arr, i);
		int *indexed = block_index(arr.data, i, sizeof(int));
		ASSERT_EQ(hooked, indexed);
	}
	CLEAN_ARRAY();
}

TEST array_set_test(){
	SETUP_ARRAY();
	for(int i = 0; i < ITERS; ++i)
		array_set(&arr, i, &i);
	for(int i = 0; i < ITERS; ++i){
		int *elem = array_hook(&arr, i);
		ASSERT_EQ(*elem, i);
	}
	CLEAN_ARRAY();
}

TEST array_fetch_test(){
	SETUP_ARRAY();
	for(int i = 0; i < ITERS; ++i)
		array_set(&arr, i, &i);
	for(int i = 0; i < ITERS; ++i){
		int elem;
		array_fetch(&arr, i, &elem);
		ASSERT_EQ(elem, i);
	}
	CLEAN_ARRAY();
}

TEST array_zero_test(){
	SETUP_ARRAY();
	array_zero(&arr);
	for(int i = 0; i < ITERS; ++i){
		int *elem = array_hook(&arr, i);
		ASSERT_EQ(*elem, 0);
	}
	CLEAN_ARRAY();
}

TEST array_fill_test(){
	SETUP_ARRAY();
	int value = 5;
	array_fill(&arr, &value);
	for(int i = 0; i < ITERS; ++i){
		int *elem = array_hook(&arr, i);
		ASSERT_EQ(*elem, value);
	}
	CLEAN_ARRAY();
}


TEST array_reverse_test(){
	SETUP_ARRAY();
	for(int i = 0; i < ITERS; ++i)
		array_set(&arr, i, &i);
	array_reverse(&arr);
	for(int i = 0; i < ITERS; ++i){
		int *elem = array_hook(&arr, i);
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

TEST array_sort_test(){
	SETUP_ARRAY();
	for(int i = 0; i < ITERS; ++i){
		int r = rand();
		array_set(&arr, i, &r);
	}
	array_sort(&arr, int_cmp);
	for(int i = 0; i < ITERS - 1; ++i){
		int *e1 = array_hook(&arr, i);
		int *e2 = array_hook(&arr, i + 1);
		ASSERT(*e1 < *e2);
	}
	CLEAN_ARRAY();	
}

GREATEST_SUITE(array_suite){
	RUN_TEST(array_hook_test);
	RUN_TEST(array_set_test);
	RUN_TEST(array_fetch_test);
	RUN_TEST(array_zero_test);
	RUN_TEST(array_fill_test);
	RUN_TEST(array_reverse_test);
	RUN_TEST(array_sort_test);
}