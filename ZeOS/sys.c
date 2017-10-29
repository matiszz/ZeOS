// sys.c - Syscalls implementation
#include <mm_address.h>
#include <devices.h>
#include <system.h>
#include <sched.h>
#include <utils.h>
#include <list.h>
#include <io.h>
#include <mm.h>

#define LECTURA 0
#define ESCRIPTURA 1

int zeos_ticks;

int check_fd(int fd, int permissions) {
	if (fd!=1) return -9; /*EBADF*/
	if (permissions!=ESCRIPTURA) return -13; /*EACCES*/
	return 0;
}

int sys_ni_syscall() {
	return -38; /*ENOSYS*/
}

int sys_getpid() {
	return current()->PID;
}

void libera_pags(int paginas[NUM_PAG_DATA]) {
	int acabat = 0;
	for (int i = 0; i < NUM_PAG_DATA && acabat != 0; ++i) {
		if (paginas[i] != -5) free_frame(paginas[i]);
		else acabat = 1;
	}
}

int sys_fork() {
	int PID = -1;

	if (list_empty(&freequeue)) return -1;
	// Cogemos el primer PCB, lo liberamos y se lo asignamos al hijo.
	struct task_head *primer = list_first(&freequeue);
	list_del(primer);
	struct task_struct *pcb_hijo = list_head_to_task_struct(primer);

	// Creamos los dos tasks_union para poder copiar el del padre en el del hijo.
	union task_union *uHijo = (union task_union*)pcb_hijo;
	union task_union *uPadre = (union task_union*)current();
	copy_data(uPadre, uHijo, sizeof(union task_union));

	// Inicializar el dir_pages_baseAddr. Set_cr3 ??
	allocate_DIR(pcb_hijo);

	// Comprobar si hay suficiente espacio. Vector ??
	int paginas[NUM_PAG_DATA];
		// Pongo todos los valores a -5
	for (int i = 0; i < NUM_PAG_DATA; ++i) paginas[i] = -5;
		// Veo si hay espacio suficiente
	for (int i = 0; i < NUM_PAG_DATA; ++i) {
		int num_pag = alloc_frame();
		paginas[i] = num_pag;
		if (num_pag < 0) {
			libera_pags(paginas);
			return -1;
		}
	}

	return PID;
}

void sys_exit() {  
}

int sys_write(int fd, char * buffer, int size) {
	int res;

	if ((res = check_fd(fd, ESCRIPTURA)) < 0) return -1;  	// Comprova fd
	if (buffer == NULL) return -1;							// Comprova buffer
	if (size < 0) return -1;								// Comprova mida

	return sys_write_console(buffer, size);
}

int sys_gettime() {
	return zeos_ticks;
}