#include "greatest.h"
extern SUITE(memory_suite);
extern SUITE(array_suite);

GREATEST_MAIN_DEFS();
int main(int argc, char **argv) {
	GREATEST_MAIN_BEGIN();   
	RUN_SUITE(memory_suite);  
	RUN_SUITE(array_suite);  
	GREATEST_MAIN_END();
	return 0;
}