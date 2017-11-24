#include <libc.h>

char buff[24];

int __attribute__ ((__section__(".text.main")))


main(void) {
	set_sched_policy(0);
	struct stats s;
	char buff[10000];
	char buff2[10000];	

	int ret = fork();

	if (ret > 0) {
		int a=0;
		for (int i=0; i<1000000; i++) {
			a = i+1;
		}

		get_stats(getpid(), &s);
		itoa(s.user_ticks,buff);
		write(1, "\nPID= ", strlen("\nPID= "));
		itoa(getpid(), buff2);
		write(1,buff2,strlen(buff2));
		
		write(1," User ticks = ", strlen("\nUser ticks = "));
		itoa(s.user_ticks,buff);
		write(1,buff,strlen(buff));

		write(1," System ticks = ", strlen("System ticks = "));
		itoa(s.system_ticks,buff);
		write(1,buff,strlen(buff));

		write(1," Blocked ticks = ", strlen("Blocked ticks = "));
		itoa(s.blocked_ticks,buff);
		write(1,buff,strlen(buff));

		int ret2 = fork();

		if (ret2 == 0) {
			int c=0;
			for (int i=0; i<1000000; i++) {
				c= c*c*c+i;
			}

			get_stats(getpid(), &s);
			itoa(s.user_ticks,buff);
			write(1, "\nPID= ", strlen("\nPID= "));
			itoa(getpid(), buff2);
			write(1,buff2,strlen(buff2));
			
			write(1," User ticks = ", strlen("\nUser ticks = "));
			itoa(s.user_ticks,buff);
			write(1,buff,strlen(buff));

			write(1," System ticks = ", strlen("System ticks = "));
			itoa(s.system_ticks,buff);
			write(1,buff,strlen(buff));

			write(1," Blocked ticks = ", strlen("Blocked ticks = "));
			itoa(s.blocked_ticks,buff);
			write(1,buff,strlen(buff));
		}
	}

	else if (ret == 0) {
		int b=0;
		for (int i=0; i<1000000; i++)
			b= b*b+i;

		get_stats(getpid(), &s);
		itoa(s.user_ticks,buff);
		write(1, "\nPID= ", strlen("\nPID= "));
		itoa(getpid(), buff2);
		write(1,buff2,strlen(buff2));
		
		write(1," User ticks = ", strlen("\nUser ticks = "));
		itoa(s.user_ticks,buff);
		write(1,buff,strlen(buff));

		write(1," System ticks = ", strlen("System ticks = "));
		itoa(s.system_ticks,buff);
		write(1,buff,strlen(buff));

		write(1," Blocked ticks = ", strlen("Blocked ticks = "));
		itoa(s.blocked_ticks,buff);
		write(1,buff,strlen(buff));
		
	}
	

	while(1) { }
}


void work3() {
	int c=0;
	for (int i=0; i<1000000; i++) {
		c= c*c*c+i;
	}
}
