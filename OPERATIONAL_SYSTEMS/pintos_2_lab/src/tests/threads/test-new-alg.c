
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
  //msg("Not implemented.");
  // struct semaphore sema;
  // sema_init(&sema, 0);

  thread_set_priority(PRI_MAX);

  thread_create_cpu_burst("Proc0", 3, print_statistics_thread_func, NULL, 8);
  thread_create_cpu_burst("Proc1", 28, print_statistics_thread_func, NULL, 4);
  thread_create_cpu_burst("Proc2", 62, print_statistics_thread_func, NULL, 7);
  thread_create_cpu_burst("Proc3", 31, print_statistics_thread_func, NULL, 3);

  thread_set_priority(PRI_MIN);

  // sema_down(&sema);
  // sema_down(&sema);
  // sema_down(&sema);
  // sema_down(&sema);
}


static void
print_statistics_thread_func (void *aux) 
{
  struct thread * cur = thread_current();
  struct semaphore *sema = aux;

  while (cur->ticks_spent_active < cur->cpu_burst)
  {
    printf("Name: %s Priority: %d Ticks: %d\n", cur->name, cur->priority, cur->ticks_spent_active);
  }

  //sema_up(sema);
}