#include <libc.h>

char buff[24];
int pid;
int __attribute__ ((__section__(".text.main")))

main(void) {
  write(1, " hola mati. PID: ", strlen(" hola mati. PID: "));
  int pid = getpid();
  
  char buf[10];
  itoa(pid, buf);
  write(1, buf, strlen(buf));

  while(1) { }
}
