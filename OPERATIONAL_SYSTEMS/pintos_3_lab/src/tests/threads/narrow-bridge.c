
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
#define MAX_CONSECUTIVE_TRAVELS 2

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
	
	sema_init(&waiter.semaphore,0);
	list_insert_ordered(queue, &waiter.elem, queue_less_func, NULL);
	lock_release(&global_lock);
	sema_down(&waiter.semaphore);
	lock_acquire(&global_lock);
}


void wake_car_from_queue(struct list * queue)
{
	if (!list_empty(queue))
	{
		struct queue_elem * waiter = list_entry(list_pop_front(queue), struct queue_elem, elem);
		sema_up(&waiter->semaphore);
	}
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

	bool must_wait = false;
	
	struct list *my_queue = (dir == left) ? &left_queue : &right_queue;
	struct list *opp_queue = (dir == left) ? &right_queue : &left_queue;

	int opp_has_emergency = !list_empty(opp_queue) && 
			list_entry(list_front(opp_queue), struct queue_elem, elem)->priority == car_emergency;


	if (road_dir != dir && road_dir != none)
		must_wait = true;
	else if (road_count == 2)
		must_wait = true;
	else if (!list_empty(my_queue))
		must_wait = true;
	else if (opp_has_emergency && prio != car_emergency)
		must_wait = true;



	if (must_wait)
	{
		add_car_to_queue(my_queue, prio, dir);
	}
	else
	{
		if (road_dir == none)
			road_dir = dir;
		
		road_count++;
	}

	lock_release(&global_lock);
}

void exit_bridge(enum car_priority prio UNUSED, enum car_direction dir UNUSED)
{
	lock_acquire(&global_lock);

	struct list *my_queue = (dir == left) ? &left_queue : &right_queue;
	struct list *opp_queue = (dir == left) ? &right_queue : &left_queue;

	road_count--;

	int my_has_emergency = !list_empty(my_queue) && list_entry(list_front(my_queue), struct queue_elem, elem)->priority == car_emergency;
	int opp_has_emergency = !list_empty(opp_queue) && list_entry(list_front(opp_queue), struct queue_elem, elem)->priority == car_emergency;

	
	if (road_count == 0)
	{
		while (road_count < 2)
		{
			if (opp_has_emergency && (road_dir != dir || road_count == 0))
			{
				road_dir = !dir;
				wake_car_from_queue(opp_queue);
				opp_has_emergency = !list_empty(opp_queue) && list_entry(list_front(opp_queue), struct queue_elem, elem)->priority == car_emergency;
			}
			else if (my_has_emergency && road_dir == dir)
			{
				wake_car_from_queue(my_queue);
				my_has_emergency = !list_empty(my_queue) && list_entry(list_front(my_queue), struct queue_elem, elem)->priority == car_emergency;
			}
			else if (!list_empty(opp_queue) && !(my_has_emergency || opp_has_emergency) && (road_dir != dir || road_count == 0))
			{
				road_dir = !dir;
				wake_car_from_queue(opp_queue);
			}
			else if (!list_empty(my_queue) && road_dir == dir && !(my_has_emergency || opp_has_emergency))
			{
				wake_car_from_queue(my_queue);
			}
			else
			{
				break;
			}
			
			road_count++;
		}
	}


	lock_release(&global_lock);
}
