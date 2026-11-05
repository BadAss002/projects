
/* File for 'narrow_bridge' task implementation.  
   SPbSTU, IBKS, 2017 */

#include <stdio.h>
#include "tests/threads/tests.h"
#include "threads/thread.h"
#include "threads/synch.h"
#include "narrow-bridge.h"

#define right 1
#define left 0

int road_count;
int road_dir; // 0=left 1=right 2=none
int emergency_left;
int emergency_right;
int default_left;
int default_right;
int yield_to_emergency;
int consecutive_count;
struct lock global_lock;
struct semaphore left_queue;
struct semaphore right_queue;
struct semaphore left_emergency_queue;
struct semaphore right_emergency_queue;


// Called before test. Can initialize some synchronization objects.
void narrow_bridge_init(void)
{
	road_count = 0;
	road_dir = 2;
	emergency_left = 0;
	default_left = 0;
	emergency_right = 0;
	default_right = 0;
	yield_to_emergency = 0;
	consecutive_count = 0;

	lock_init(&global_lock);
	sema_init(&left_queue, 0);
	sema_init(&right_queue, 0);
	sema_init(&left_emergency_queue, 0);
	sema_init(&right_emergency_queue, 0);
}

void arrive_bridge(enum car_priority prio UNUSED, enum car_direction dir UNUSED)
{
	lock_acquire(&global_lock);

	//road is empty
	if (road_count == 0)
	{
		//maybe emergency_yield here is also needed
		road_count++;
		road_dir = dir;
		consecutive_count = 1;
		lock_release(&global_lock);
	}
	else if (road_dir == dir)
	{
		int opp_waiting;
		if (dir == left)
			opp_waiting = default_right+emergency_right;
		else
			opp_waiting = default_left+emergency_left; 


		if (road_count == 1 && (consecutive_count < 4 || opp_waiting == 0) && yield_to_emergency == 0)
		{
			road_count++;
			consecutive_count++;
			lock_release(&global_lock);
		}
		else
		{
			if (prio == 0)
			{
				default_left++;
				lock_release(&global_lock);
				sema_down(&left_queue);
			}
			else
			{
				emergency_left++;
				lock_release(&global_lock);
				sema_down(&left_emergency_queue);
			}
		}
	}
	else
	{
		if (prio == 0)
		{
			default_right++;
			lock_release(&global_lock);
			sema_down(&right_queue);
		}
		else
		{
			emergency_right++;
			lock_release(&global_lock);
			sema_down(&right_emergency_queue);
		}
	}
}

void exit_bridge(enum car_priority prio UNUSED, enum car_direction dir UNUSED)
{
	lock_acquire(&global_lock);
	road_count--;


	unsigned char left_first = 1;
	if (consecutive_count < 4)
		left_first = 1;
	else if (consecutive_count >=4 && consecutive_count < 8)
		left_first = 0;
	else
	{
		consecutive_count = 0;
		left_first = 1;
	}


	if (prio == 1) yield_to_emergency = 0;


	if (left_first)
	{
		if (emergency_left != 0)
		{
			emergency_left--;
			yield_to_emergency = 1;
			consecutive_count++;
			road_count++;
			sema_up(&left_emergency_queue);
		}
		else if (emergency_right != 0)
		{
			emergency_right--;
			yield_to_emergency = 1;
			road_dir = right;
			consecutive_count++;
			road_count++;
			sema_up(&right_emergency_queue);
		}
		else if (default_left != 0)
		{
			default_left--;
			consecutive_count++;
			road_count++;
			sema_up(&left_queue);
		}
		else if (default_right != 0)
		{
			default_right--;
			consecutive_count++;
			road_dir = right;
			road_count++;
			sema_up(&right_queue);
		}
	}
	else
	{
		if (emergency_right != 0)
		{
			emergency_right--;
			yield_to_emergency = 1;
			consecutive_count++;
			road_count++;
			sema_up(&right_emergency_queue);
		}
		else if (emergency_left != 0)
		{
			emergency_left--;
			yield_to_emergency = 1;
			consecutive_count++;
			road_dir = left;
			road_count++;
			sema_up(&left_emergency_queue);
		}
		else if (default_right != 0)
		{
			default_right--;
			consecutive_count++;
			road_count++;
			sema_up(&right_queue);
		}
		else if (default_left != 0)
		{
			default_left--;
			consecutive_count++;
			road_dir = left;
			road_count++;
			sema_up(&left_queue);
		}
	}

	
	
	lock_release(&global_lock);
}
