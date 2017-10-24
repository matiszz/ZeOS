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

union task_union *task = &protected_tasks[1]; /* == union task_union task[NR_TASKS] */


struct task_struct *list_head_to_task_struct(struct list_head *l) {
  	return (unsigned long) l & (0xfffff000);
}

extern struct list_head blocked;
extern struct task_struct *idle_task; 


struct list_head freequeue; // tiene que ser global


/* get_DIR - Returns the Page Directory address for task 't' */
page_table_entry * get_DIR (struct task_struct *t) {
	return t->dir_pages_baseAddr;
}

/* get_PT - Returns the Page Table address for task 't' */
page_table_entry * get_PT (struct task_struct *t) 
{
	return (page_table_entry *)(((unsigned int)(t->dir_pages_baseAddr->bits.pbase_addr))<<12);
}


int allocate_DIR(struct task_struct *t) 
{
	int pos;

	pos = ((int)t-(int)task)/sizeof(union task_union);

	t->dir_pages_baseAddr = (page_table_entry*) &dir_pages[pos]; 

	return 1;
}

void cpu_idle(void)
{
	__asm__ __volatile__("sti": : :"memory");

	while(1)
	{
	;
	}
}

void init_idle (void) {
	struct list_head *free; //elemento a sacar
	free = list_first(&freequeue); //obtenemos el primer elemento de la freequeue;
	struct task_struct *pcb_idle;
	pcb_idle = list_head_to_task_struct(free); //a partir del list_head sacamos el task_struct
	pcb_idle->PID = 0; //asignamos el PID 0 al proceso 
	allocate_DIR(pcb_idle); //inicializamos el directorio de paginas del proceso task

	union task_union *uIdle;
	uIdle->task = *(pcb_idle);
	uIdle->stack[1023] = &cpu_idle; //asignamos la direccion de la funcion cpu_idle, ojo parentesis
	uIdle->stack[1022] = 0; //ebp = 0
	KERNEL_ESP(uIdle); // Hacemos que el Kernel_ESP apunte a la cima de la pila del contexto idle
	struct task_struct *idle_task = pcb_idle;
}

void init_task1(void) {
	struct list_head *free; //elemento a sacar
	free = list_first(&freequeue); //obtenemos el primer elemento de la freequeue;
	struct task_struct *pcb_init;
	pcb_init = list_head_to_task_struct(free); //a partir del list_head sacamos el task_struct
	pcb_init->PID = 1; //asignamos el PID 1 al proceso 
	allocate_DIR(pcb_init); //inicializamos el directorio de paginas del proceso task
	set_user_pages(pcb_init);

	union task_union *uInit;
	uInit->task = *(pcb_init);
	tss.esp0 = uInit->stack[1023];
	set_cr3(pcb_init->dir_pages_baseAddr);
}


void init_sched() {

	/******************** FREE QUEUE ********************/
	INIT_LIST_HEAD(&freequeue); //la inicializamos
	
	struct list_head primer; //declaramos un auxiliar
	primer = freequeue;

	for (int i = 0; i < 10; ++i) {
		struct task_struct tmp; //declaramos un task_struct vacio
		list_add(&(tmp.list), &primer); //añadimos el list del task_struct vacio despues de primer
		primer = tmp.list; //el añadido pasa a ser primer
	}
	/******************** FREE QUEUE ********************/

	/******************** READY QUEUE *******************/
	struct list_head *readyqueue; //declaramos una readyqueue
	INIT_LIST_HEAD(readyqueue); //la inicializamos
		/******************** READY QUEUE *******************/

}

struct task_struct* current() {
  int ret_value;
  
  __asm__ __volatile__(
  	"movl %%esp, %0"
	: "=g" (ret_value)
  );

  return (struct task_struct*)(ret_value&0xfffff000);
}