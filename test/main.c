#include "greatest.h"
extern SUITE(memory);

GREATEST_MAIN_DEFS();
int main(int argc, char **argv) {
	GREATEST_MAIN_BEGIN();   
	RUN_SUITE(memory);  
	GREATEST_MAIN_END();
	return 0;
}