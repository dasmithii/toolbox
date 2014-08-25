#include <kit/greatest.h>
extern SUITE(array_suite);
extern SUITE(bits_suite);
extern SUITE(memory_suite);
extern SUITE(fllist_suite);
extern SUITE(vector_suite);
extern SUITE(hash_suite);


GREATEST_MAIN_DEFS();
int main(int argc, char **argv) {
	GREATEST_MAIN_BEGIN();   
	RUN_SUITE(array_suite);  
	RUN_SUITE(bits_suite);
	RUN_SUITE(fllist_suite);  
	RUN_SUITE(memory_suite);  
	RUN_SUITE(vector_suite);
	GREATEST_MAIN_END();
	return 0;
}