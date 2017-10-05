#include <libc.h>

char buff[24];

int pid;

long inner (long n) {
	int i;
	long suma;
	suma = 0;
	for (i=0; i<n; i++)
		suma = suma + i;
	return suma;
}

long outer (long n) {
	int i;
	long acum;
	acum = 0;
	for (i=0; i<n; i++)
		acum = acum + inner(i);
	return acum;
}

int add (int par1, int par2) {
	asm("movl %edx, -4(%ebp)");
	asm("movl %ecx, -8(%ebp)");
	asm("addl %edx, %ecx");
	asm("movl %ecx, %eax");
	asm("ret");
}

int __attribute__ ((__section__(".text.main")))
main(void) {
	write(1, " Raul gay", strlen(" Raul gay"));
	while(1) { }
}
