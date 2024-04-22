#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "driverlib/systick.h"

#define NUM_OF_TASKS 3

typedef struct {
  void (*task)();
  uint32_t period;
} os_thread;

void create_task(void (*task)(), uint32_t);
void scheduler_run();

#endif /* SCHEDULER_H */
