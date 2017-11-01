#include <libc.h>
#include <sched.h>

char buff[24];
int pid;
extern struct task_struct *idle_task;
int __attribute__ ((__section__(".text.main")))

main(void) {
  write(1, "PID idle: ", strlen("PID idle: "));
  int pid = idle_task->PID;
  char b[3];
  itoa(pid, b);
  write(1, b, strlen(b));
  write(1, "Holi", strlen("Holi"));
  
   /*
  write(1, " \n hola mati. PID: ", strlen(" \n hola mati. PID: "));
  int pid = getpid();
  char buf[10];
  itoa(pid, buf);
  write(1, buf, strlen(buf));

  int pid2 = fork();
  if (pid2 == 0) {
    write(1, "\n hola soy el hijo ", strlen("\n hola soy el hijo "));
    itoa(getpid(), buf);
    write(1, buf, strlen(buf));
  }
  else if (pid2 > 0) {
    write(1, "\n hola soy el padre ", strlen("\n hola soy el padre "));
    itoa(getpid(), buf);
    write(1, buf, strlen(buf));
  }
  else if (pid2 < 0) write(1, "no funca man", strlen("no funca man"));
  else write(1, "uy aqui si que no funca", strlen("uy aqui si que no funca"));
*/
  while(1) { }
}
