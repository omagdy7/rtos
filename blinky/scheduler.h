#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>

// Assume NUM_OF_TASKS is defined somewhere as required
#define NUM_OF_TASKS 3

typedef struct {
  void (*taskFunc)(void); // Pointer to the task function
  uint32_t period;        // Period of the task in ms
  uint32_t elapsed;       // Time since the task was last run
} Task;

void Scheduler_Init(void);
void Scheduler_Start(void);
void Create_Task(Task *task, uint32_t period);

#endif // SCHEDULER_H
