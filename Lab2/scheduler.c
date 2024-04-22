#include <stdint.h>
#include "scheduler.h"
#include "systick.h"

#define PERIOD (0xFFFFFF - 1) / 2

os_thread tasks[NUM_OF_TASKS];

int cnt = 0;

void SysTick_Handler() { cnt++; }

void create_task(void (*task)(), uint32_t period) {
  static uint32_t cnt = 0;
  tasks[cnt].task = task;
  tasks[cnt].period = period;
  cnt++;
}

void scheduler_run() {
  SysTickEnable();
  SysTickPeriodSet(PERIOD);
  SysTickIntEnable();
  IntMasterEnable();
  while (1) {
    uint32_t volatile i;
    for (i = 0; i < NUM_OF_TASKS; i++) {
      if (cnt % tasks[i].period == 0) {
        tasks[i].task();
      }
    }
  }
}
