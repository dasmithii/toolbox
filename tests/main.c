#include "greatest.h"
extern SUITE(Array_suite);
extern SUITE(bits_suite);
extern SUITE(Circle_suite);
extern SUITE(memory_suite);
extern SUITE(FLList_suite);
extern SUITE(Vector_suite);
extern SUITE(hash_suite);
extern SUITE(Heap_suite);


GREATEST_MAIN_DEFS();
int main(int argc, char **argv) {
	GREATEST_MAIN_BEGIN();   
	RUN_SUITE(Array_suite);  
	RUN_SUITE(bits_suite);
	RUN_SUITE(Circle_suite);
	RUN_SUITE(FLList_suite);  
	RUN_SUITE(memory_suite);  
	RUN_SUITE(Vector_suite);
	RUN_SUITE(Heap_suite);
	GREATEST_MAIN_END();
	return 0;
}