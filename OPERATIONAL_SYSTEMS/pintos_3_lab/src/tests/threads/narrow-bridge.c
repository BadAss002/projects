
/* File for 'narrow_bridge' task implementation.  
   SPbSTU, IBKS, 2017 */

#include <stdio.h>
#include "tests/threads/tests.h"
#include "threads/thread.h"
#include "threads/synch.h"
#include "narrow-bridge.h"

#define right 1
#define left 0
#define none 2

struct queue_elem
{
	int priority;
	int direction;
	struct semaphore semaphore;
	struct list_elem elem;
};

int road_count;
int road_dir;
struct lock global_lock;
struct list right_queue;
struct list left_queue;

bool queue_less_func(struct list_elem *a, struct list_elem *b, void *aux)
{
	int a_priority = list_entry(a, struct queue_elem, elem)->priority;
	int b_priority = list_entry(b, struct queue_elem, elem)->priority;

	return a_priority > b_priority;
}


void add_car_to_queue(struct list * queue, int prio, int dir)
{
	struct queue_elem waiter;
	waiter.direction = dir;
	waiter.priority = prio;
	
	list_insert_ordered(queue, &waiter.elem, queue_less_func, NULL);
	lock_release(&global_lock);
	sema_down(&waiter.semaphore);
}


// Called before test. Can initialize some synchronization objects.
void narrow_bridge_init(void)
{
	road_count = 0;
	road_dir = none;
	lock_init(&global_lock);
	list_init(&right_queue);
	list_init(&left_queue);
}

void arrive_bridge(enum car_priority prio UNUSED, enum car_direction dir UNUSED)
{
	lock_acquire(&global_lock);

	lock_release(&global_lock);
}

void exit_bridge(enum car_priority prio UNUSED, enum car_direction dir UNUSED)
{
	lock_acquire(&global_lock);
	

	lock_release(&global_lock);
}
