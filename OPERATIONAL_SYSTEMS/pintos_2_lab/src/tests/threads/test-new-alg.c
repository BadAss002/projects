
/*
  File for 'test-new-alg' task implementation.
*/

#include <stdio.h>
#include "tests/threads/tests.h"
#include "threads/malloc.h"
#include "threads/thread.h"
#include "threads/synch.h"
#include "devices/timer.h"

#define TIME_SLICE 4

static thread_func print_statistics_thread_func;

void test_new_alg(void) 
{
  thread_set_priority(PRI_MAX);
  thread_create_cpu_burst("Proc0", 3, print_statistics_thread_func, NULL, 8);
  thread_create_cpu_burst("Proc1", 28, print_statistics_thread_func, NULL, 4);
  thread_create_cpu_burst("Proc2", 62, print_statistics_thread_func, NULL, 7);
  thread_create_cpu_burst("Proc3", 62, print_statistics_thread_func, NULL, 3);
  thread_set_priority(PRI_MIN);

  msg("all threads had been created");
}

static void
print_statistics_thread_func(void *aux)
{
  struct thread *cur = thread_current();

  int ticks_spent_active = 0;

  while (ticks_spent_active < cur->cpu_burst)
  {
    int current_tick = ticks_spent_active; 
    printf("Name: %s Priority: %d Ticks: %d\n", cur->name, cur->priority, current_tick);
    ticks_spent_active++;

    if (ticks_spent_active % TIME_SLICE == 0) thread_yield();
  }
}