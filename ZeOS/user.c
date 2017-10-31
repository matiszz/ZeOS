#include <libc.h>

char buff[24];
int pid;
int __attribute__ ((__section__(".text.main")))

main(void) {
  write(1, " hola mati. PID: ", strlen(" hola mati. PID: "));

  /*int pid = getpid();
  
  char buf[10];
  itoa(pid, buf);
  write(1, buf, strlen(buf));
*/
  int pid2 = fork();
  if (pid2 == 0) {
  	write(1, "hola soy el hijo", strlen("hola soy el hijo"));
  }
  else if (pid2 > 0) {
  	write(1, "hola soy el padre", strlen("hola soy el padre"));
  }
  else if (pid2 < 0) write(1, "no funca man", strlen("no funca man"));
  else write(1, "uy aqui si que no funca", strlen("uy aqui si que no funca"));

  while(1) { }
}
