#include <libc.h>

char buff[24];
int pid;
int __attribute__ ((__section__(".text.main")))

main(void) {
  write(1, " Hola, bienvenido!", strlen(" Hola, bienvenido!"));
  while(1) { }
}
