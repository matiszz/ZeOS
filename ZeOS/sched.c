/*
 * sched.c - initializes struct for task 0 anda task 1
 */

#include <sched.h>
#include <mm.h>
#include <io.h>

/**
 * Container for the Task array and 2 additional pages (the first and the last one)
 * to protect against out of bound accesses.
 */
union task_union protected_tasks[NR_TASKS+2]
  __attribute__((__section__(".data.task")));

union task_union *task = &protected_tasks[1];

extern struct list_head blocked;
extern struct task_struct *idle_task; 
struct list_head freequeue; 				  // Tiene que ser global
struct list_head readyqueue; 				  // Tiene que ser global

struct task_struct *list_head_to_task_struct(struct list_head *l) {
	unsigned long aux = (unsigned long)l;
	unsigned long aux2 = aux&0xfffff000;
	return (struct task_struct *)aux2;
}

/* get_DIR - Returns the Page Directory address for task 't' */
page_table_entry * get_DIR (struct task_struct *t) {
	return t->dir_pages_baseAddr;
}

/* get_PT - Returns the Page Table address for task 't' */
page_table_entry * get_PT (struct task_struct *t) {
	return (page_table_entry *)(((unsigned int)(t->dir_pages_baseAddr->bits.pbase_addr))<<12);
}

void inner_task_switch(union task_union *nuevo) {
	// Cambio pila de sistema.
	tss.esp0 = (unsigned long)&(nuevo->stack[KERNEL_STACK_SIZE]);

	// Cambio de Tabla de Páginas
	set_cr3(nuevo->task.dir_pages_baseAddr);

	// Guardamos en ebp el esp de nuevo
	asm volatile("movl %%ebp, %0" /* %0 es el input */
		: "=g" (current()->esp)
	);

	// Guardamos el contenido de esp en el esp de mi pila
	asm volatile("movl %0, %%esp"
		: /* No input */
		: "g" (nuevo->task.esp)
	);
	// Salir del modo sistema
	asm volatile("pop %ebp;");
	asm volatile("ret;");
}

void task_switch(union task_union *t) {
	asm("push %esi;");
	asm("push %edi;");
	asm("push %ebx;");
	inner_task_switch(t);
	asm("pop %ebx;");
	asm("pop %edi;");
	asm("pop %esi;");
}

int allocate_DIR(struct task_struct *t) {
	int pos;
	pos = ((int)t-(int)task)/sizeof(union task_union);
	t->dir_pages_baseAddr = (page_table_entry*) &dir_pages[pos]; 
	return 1;
}

void cpu_idle(void) {
	// Para permitir las interrupciones en modo Kernel
	__asm__ __volatile__("sti": : :"memory");

	while(1) { ; }
}

void init_idle (void) {
	struct list_head *primer = list_first(&freequeue); // Obtenemos el primer elemento de la freequeue;
	list_del(primer); 			// Eliminamos este elemento

	struct task_struct *pcb_idle = list_head_to_task_struct(primer); // A partir del list_head sacamos el task_struct
	pcb_idle->PID = 0; 			// Asignamos el PID 0 al proceso

	allocate_DIR(pcb_idle); 	// Inicializamos el directorio de paginas del proceso task

	union task_union *uIdle = (union task_union*)pcb_idle;
	uIdle->task = *(pcb_idle);
	uIdle->stack[1023] = (unsigned long)&cpu_idle; // Asignamos la direccion de la funcion cpu_idle
	uIdle->stack[1022] = 0; 		// %ebp = 0
	//KERNEL_ESP(uIdle); 				// Hacemos que el Kernel_ESP apunte a la cima de la pila del contexto idle
	pcb_idle->esp = (unsigned long)&(uIdle->stack[1022]);

	struct task_struct *idle_task = pcb_idle; // Hacemos que la variable global aputne al PCB de idle
	idle_task = idle_task; // Para que el complilador no se queje
}

void init_task1(void) {
	struct list_head *primer = list_first(&freequeue); // Obtenemos el primer elemento de la freequeue;
	list_del(primer);			// Lo eliminamos

	struct task_struct *pcb_init = list_head_to_task_struct(primer); // A partir del list_head sacamos el task_struct
	pcb_init->PID = 1; 			// Asignamos el PID 1 al proceso 
	
	allocate_DIR(pcb_init); 	// Inicializamos el directorio de paginas del proceso task1
	set_user_pages(pcb_init);
	
	union task_union *uInit = (union task_union*)pcb_init;
	uInit->task = *(pcb_init);
	tss.esp0 = (DWord)&(uInit->stack[KERNEL_STACK_SIZE]);

	set_cr3(pcb_init->dir_pages_baseAddr);	// Hacemos que cr3 apunte a su directorio
}

void init_sched() {

	/// FREE QUEUE
	INIT_LIST_HEAD(&freequeue); 	// La inicializamos
	for (int i = 0; i < NR_TASKS; ++i)
		list_add_tail(&(task[i].task.list), &freequeue); // Añadimos las tareas al principio

	// READY QUEUE
	INIT_LIST_HEAD(&readyqueue); 	// La inicializamos
}

struct task_struct* current() {
  int ret_value;
  
  __asm__ __volatile__(
  	"movl %%esp, %0"
	: "=g" (ret_value)
  );

  return (struct task_struct*)(ret_value&0xfffff000);
}