
/*
  File for 'test-new-alg' task implementation.
*/

#include <stdio.h>
#include "tests/threads/tests.h"
#include "threads/malloc.h"
#include "threads/thread.h"
#include "threads/synch.h"
#include "devices/timer.h"

static thread_func print_statistics_thread_func;

void test_new_alg(void) 
{
  thread_set_priority(PRI_MAX);
  thread_create_cpu_burst("Proc0", 3, print_statistics_thread_func, NULL, 8);
  thread_create_cpu_burst("Proc1", 28, print_statistics_thread_func, NULL, 4);
  thread_create_cpu_burst("Proc2", 62, print_statistics_thread_func, NULL, 7);
  thread_create_cpu_burst("Proc3", 62, print_statistics_thread_func, NULL, 3);
  thread_set_priority(PRI_MIN);
}

static void
print_statistics_thread_func (void *aux) 
{
  struct thread * cur = thread_current();
  int last_printed_tick = -1;

  while (cur->ticks_spent_active < cur->cpu_burst)
  {
    if (cur->ticks_spent_active != last_printed_tick)
    {
      printf("Name: %s Priority: %d Ticks: %d\n", cur->name, cur->priority, cur->ticks_spent_active);
      last_printed_tick = cur->ticks_spent_active;
    }
    // thread_yield();
    //printf("Name: %s Priority: %d Ticks: %d\n", cur->name, cur->priority, cur->ticks_spent_active);
  }
}