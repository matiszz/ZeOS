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
int lastPID = 3;

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

void libera_frames(int fisicas[NUM_PAG_DATA]) {
	int acabat = 0;
	for (int i = 0; i < NUM_PAG_DATA && acabat != 1; ++i) {
		if (fisicas[i] != -5) free_frame(fisicas[i]);
		else acabat = 1;
	}
}

int random_pid() {
	return zeos_ticks%100;
}

int ret_from_fork() {
	return 0;
}

int sys_fork() {
	int PID = -1;

	if (list_empty(&freequeue)) return -1;
	// Cogemos el primer PCB, lo liberamos y se lo asignamos al hijo.
	struct list_head *primer = list_first(&freequeue);
	list_del(primer);
	struct task_struct *pcb_hijo = list_head_to_task_struct(primer);

	// Creamos los dos tasks_union para poder copiar el del padre en el del hijo.
	union task_union *uHijo = (union task_union*)pcb_hijo;
	union task_union *uPadre = (union task_union*)current();
	copy_data(uPadre, uHijo, sizeof(union task_union));

	// Inicializar el Directorio de páginas del hijo
	allocate_DIR(pcb_hijo);

	// Comprobar si hay suficiente espacio
	int fisicas[NUM_PAG_DATA];
	for (int i = 0; i < NUM_PAG_DATA; ++i) fisicas[i] = -5; // Pongo todos los valores a -5 
	for (int i = 0; i < NUM_PAG_DATA; ++i) { // Veo si hay espacio suficiente
		int num_pag = alloc_frame();
		fisicas[i] = num_pag;
		if (num_pag < 0) {
			libera_frames(fisicas);
			return -1;
		}
	}

	// Copiar la pila del padre en el hijo
	page_table_entry * TP_padre = get_PT(current());
	page_table_entry * TP_hijo = get_PT(pcb_hijo);
	// - Primero tenemos que hacer que Kernel y Code de hijo apunten a frames del padre
	for (int i = 0; i < NUM_PAG_KERNEL+NUM_PAG_CODE; ++i) {
		unsigned int fisica = get_frame(TP_padre, i);
		set_ss_pag(TP_hijo, i, fisica);
	}
	// - Ahora tengo que crear nuevas páginas para data, a partir de code
	for (int i = 0; i < NUM_PAG_DATA; ++i) {
		set_ss_pag(TP_hijo, PAG_LOG_INIT_DATA+i, fisicas[i]);
	}

	// Copiar el contenido de Data del padre al hijo
	// - Primero tenemos que buscar entradas temporales de la TP del padre para apuntar a las del hijo
	// - Luego copiamos los datos desde el frame del padre hasta el del hijo
	// - Finalmente eliminamos la entrada temporal
	for (int i = 0; i < NUM_PAG_DATA; ++i) {
		// Debería comprobar que no hay nada ?? que no me vaya de rango y tal
		int logica_tmp = NUM_PAG_KERNEL+NUM_PAG_CODE+i;
		set_ss_pag(TP_padre, logica_tmp+NUM_PAG_DATA, fisicas[i]);

		//unsigned int numFrame = get_frame(TP_padre, PAG_LOG_INIT_DATA+i);

		copy_data((void *)(logica_tmp<<12), (void *)((logica_tmp+NUM_PAG_DATA)<<12), PAGE_SIZE);
		//copy_data((numFrame>>12), &(fisicas[i]), PAGE_SIZE);
		del_ss_pag(TP_padre, logica_tmp+NUM_PAG_DATA);
	}
	// - Por último, hacemos flush del TLB
	set_cr3(current()->dir_pages_baseAddr);

	// Comprobamos que el PID no existe y lo asignamos
	PID = lastPID;
	++lastPID;

	// Cambiamos los parámetros que son propios del hijo
	
	// Hacer ret_from_fork
	uHijo->stack[KERNEL_STACK_SIZE-18] = (unsigned long)&ret_from_fork; //preparar la pila del hijo con lo que se espera el task_switch
	uHijo->stack[KERNEL_STACK_SIZE-19] = 0;
	pcb_hijo->esp = (int)&(uHijo->stack[KERNEL_STACK_SIZE-19]);
	
	// Añandimos el proceso hijo a la readyqueue
	list_add_tail(&(pcb_hijo->list), &readyqueue);

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