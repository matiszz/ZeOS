#include <libc.h>
#include <sched.h>

char buff[24];
int pid;
int __attribute__ ((__section__(".text.main")))

main(void) {

  int p = fork();
  if (p == 0) {
    write(1, "\n  Hola, soy el hijo, mi PID es ", strlen("\n  Hola, soy el hijo, mi PID es "));
    itoa(getpid(), buff);
    write(1, buff, strlen(buff));
  }
  else if (p > 0) {
    write(1, "\n  Hola, soy el padre, mi PID es ", strlen("\n  Hola, soy el padre, mi PID es "));
    itoa(getpid(), buff);
    write(1, buff, strlen(buff));
  }

  while(1) { }
}
