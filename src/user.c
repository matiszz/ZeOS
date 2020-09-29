#include <libc.h>

char buff[24];

int __attribute__ ((__section__(".text.main")))


main(void) {
	set_sched_policy(0);
	struct stats sp, s1, s2;
	char buff[10000];
	char buff2[10000];	

	int ret = fork();

	if (ret > 0) { // Padre
		int a=0;
		for (int i=0; i<1000000; i++) {
			a= a*a*a*a*a*i^a+i;
		}
		write(1, "\nCalculo el numero ", strlen("\nCalculo el numero "));
		itoa(a, buff2);
		write(1,buff2,strlen(buff2));

		get_stats(getpid(), &sp);
		write(1, "\nPID = ", strlen("\nPID = "));
		itoa(getpid(), buff2);
		write(1,buff2,strlen(buff2));
		
		write(1," User ticks = ", strlen(" User ticks = "));
		itoa(sp.user_ticks,buff);
		write(1,buff,strlen(buff));

		write(1," System ticks = ", strlen(" System ticks = "));
		itoa(sp.system_ticks,buff);
		write(1,buff,strlen(buff));

		write(1," Blocked ticks = ", strlen(" Blocked ticks = "));
		itoa(sp.blocked_ticks,buff);
		write(1,buff,strlen(buff));

		int ret2 = fork();

		if (ret2 == 0) { // Hijo 2
			int c=0;
			for (int i=0; i<1000000; i++) {
				c= c*c*c*c*c*i^c+i;
			}
			write(1, "\nCalculo el numero ", strlen("\nCalculo el numero "));
			itoa(c, buff2);
			write(1,buff2,strlen(buff2));

			get_stats(getpid(), &s2);
			write(1, "\nPID = ", strlen("\nPID = "));
			itoa(getpid(), buff2);
			write(1,buff2,strlen(buff2));
			
			write(1," User ticks = ", strlen(" User ticks = "));
			itoa(s2.user_ticks,buff);
			write(1,buff,strlen(buff));

			write(1," System ticks = ", strlen(" System ticks = "));
			itoa(s2.system_ticks,buff);
			write(1,buff,strlen(buff));

			write(1," Blocked ticks = ", strlen(" Blocked ticks = "));
			itoa(s2.blocked_ticks,buff);
			write(1,buff,strlen(buff));
		}
	}

	else if (ret == 0) { // Hijo 1
		int b=0;
		for (int i=0; i<1000000; i++)
			b= b*b*b*b*b*i^b+i;
		write(1, "\nCalculo el numero ", strlen("\nCalculo el numero "));
		itoa(b, buff2);
		write(1,buff2,strlen(buff2));

		get_stats(getpid(), &s1);
		write(1, "\nPID = ", strlen("\nPID = "));
		itoa(getpid(), buff2);
		write(1,buff2,strlen(buff2));
		
		write(1," User ticks = ", strlen(" User ticks = "));
		itoa(s1.user_ticks,buff);
		write(1,buff,strlen(buff));

		write(1," System ticks = ", strlen(" System ticks = "));
		itoa(s1.system_ticks,buff);
		write(1,buff,strlen(buff));

		write(1," Blocked ticks = ", strlen(" Blocked ticks = "));
		itoa(s1.blocked_ticks,buff);
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
