/*
 * libc.c 
 */

#include <libc.h>
#include <types.h>

int errno;

// Convierte int a sring
void itoa(int a, char *b) {
	int i, i1;
	char c;
  
  	if (a == 0) { b[0] = '0'; b[1] = 0; return ;}
  
	i = 0;
	while (a > 0) {
		b[i] = (a%10)+'0';
		a = a/10;
		i++;
	}
  
	for (i1 = 0; i1 < i/2; i1++) {
		c = b[i1];
		b[i1] = b[i-i1-1];
		b[i-i1-1] = c;
	}
	b[i] = 0;
}

int strlen(char *a) {
	int i;
	i = 0;
	while (a[i] != 0) i++;
	return i;
}

void perror() {
	char txt[100];
	itoa(errno, txt);
	write(1, txt, strlen(txt));
}

int write(int fd, char *buffer, int size) {
	int resultado;
	asm ( "int $0x80"
		: "=a" (resultado)
		: "a" (4), "b" (fd), "c" (buffer), "d" (size)
	);

	if (resultado >= 0) return resultado;
	else {
		errno = -resultado;
		return -1;
	}
}

int gettime() {
	int resultado;
	asm ( "int $0x80"
		: "=a" (resultado)
		: "a" (10)
	);

	if (resultado >= 0) return resultado;
	else {
		errno = -resultado;
		return -1;
	}
}

int getpid() {
	int resultado;
	asm ( "int $0x80"
		: "=a" (resultado)
		: "a" (20)
	);

	if (resultado >= 0) return resultado;
	else {
		errno = -resultado;
		return -1;
	}
}