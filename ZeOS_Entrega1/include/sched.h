/*
* sched.h - Estructures i macros pel tractament de processos
*/

#ifndef __SCHED_H__
#define __SCHED_H__

#include <list.h>
#include <types.h>
#include <stats.h>
#include <mm_address.h>

#define NR_TASKS      		10
#define KERNEL_STACK_SIZE	1024
#define QUANTUM_CPU			10

enum state_t { ST_RUN, ST_READY, ST_BLOCKED };

struct task_struct {
	int PID;					// Process ID. This MUST be the first field of the struct.
	page_table_entry * dir_pages_baseAddr;
	struct list_head list; 		// Se utiliza para encolarse a si mismo
	int esp;
	int quantum;
	enum state_t estado_actual;
	struct stats estadisticas;
};

union task_union {
	struct task_struct task;
	unsigned long stack[KERNEL_STACK_SIZE];    // Pila de sistema, per procés
};

extern struct list_head freequeue; 	// Declaración e inicializacion de la free queue
extern struct list_head readyqueue; // Declaración e inicializacion de la ready queue

extern union task_union protected_tasks[NR_TASKS+2];
extern union task_union *task;      // Vector de tasques
extern struct task_struct *idle_task;
extern int tiempoCPU;

#define KERNEL_ESP(t)       (DWord) &(t)->stack[KERNEL_STACK_SIZE]
#define INITIAL_ESP       	KERNEL_ESP(&task[1])

/* Inicialitza les dades del proces inicial */
void init_task1(void);  // Inicializa y crea el proceso init
void init_idle(void);   // Inicializa y crea el proceso idle
void init_sched(void);  // Inicializa la freequeue y la readyqueue

struct task_struct * current();
void task_switch(union task_union*t);
struct task_struct *list_head_to_task_struct(struct list_head *l);
int allocate_DIR(struct task_struct *t);
page_table_entry * get_PT (struct task_struct *t) ;
page_table_entry * get_DIR (struct task_struct *t) ;

/* Headers for the scheduling policy */
void sched_next_rr();
void update_process_state_rr(struct task_struct *t, struct list_head *dest);
int needs_sched_rr();
void update_sched_data_rr();
int get_quantum (struct task_struct *t);
void set_quantum (struct task_struct *t, int new_quantum);
void planificador();

#endif  /* __SCHED_H__ */