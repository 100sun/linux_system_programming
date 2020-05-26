#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <setjmp.h>

void ssu_nested_func(int loc_var, int loc_volatile, int loc_register);

static jmp_buf glob_buffer;

int main(void)
{
	register int loc_register; // register variable
	volatile int loc_volatile; // volatile variable
	int loc_var; // local variable
	loc_var = 10;
	loc_volatile = 11;
	loc_register = 12;
	// 10 11 12
	if (setjmp(glob_buffer) != 0) { // performing nonlocal goto by saving info in glob_buffer for later use by longjmp()
		printf("after longjmp, loc_var = %d, loc_volatile = %d, loc_register = %d\n", loc_var, loc_volatile, loc_register);
		exit(0);
	}
				//   do opt  VS   no opt
	loc_var = 80;		// in memory VS in register
	loc_volatile = 81;	// in memory VS in memory(keep the value)
	loc_register = 83;	// in memory VS in register
	
	// 80 81 82	
	ssu_nested_func(loc_var, loc_volatile, loc_register);
	
	exit(0);
}

void ssu_nested_func(int loc_var, int loc_volatile, int loc_register) {
	printf("before longjmp, loc_var = %d, loc_volatile = %d, loc_register = %d\n", loc_var, loc_volatile, loc_register);
	longjmp(glob_buffer, 1); // execution skips to setjmp() by using the info saved in glob_buf to transfer control and restore stack 
}
