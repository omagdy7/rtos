#include "scheduler.h"
#include "inc/tm4c123gh6pm.h" // Replace with your specific Tiva C Series board header file
#include <stdbool.h>
#include <stdint.h>

static Task tasks[NUM_OF_TASKS];

// SysTick timer frequency
#define SYSTICK_FREQUENCY                                                      \
  16000 // Assuming 16 MHz clock, this gives us 1 ms ticks

void SysTick_Init(void) {
  // Disable SysTick during setup
  NVIC_ST_CTRL_R = 0;
  // Maximum reload value
  NVIC_ST_RELOAD_R = SYSTICK_FREQUENCY - 1;
  // Any write to current clears it
  NVIC_ST_CURRENT_R = 0;
  // Enable SysTick with core clock
  NVIC_ST_CTRL_R = NVIC_ST_CTRL_CLK_SRC | NVIC_ST_CTRL_ENABLE;
}

void Scheduler_Start(void) {
  // Enable SysTick interrupt
  NVIC_ST_CTRL_R |= NVIC_ST_CTRL_INTEN;
  // Set the priority of the SysTick interrupt to 2
  NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R & 0x00FFFFFF) | 0x40000000; // Priority 2
}

void Scheduler_Init(void) {
  SysTick_Init();
  for (int i = 0; i < NUM_OF_TASKS; i++) {
    tasks[i].taskFunc = 0;
  }
}

// Interrupt handler for SysTick timer, must be linked to the actual SysTick
// handler for the board
void SysTick_Handler(void) {
  // This is the interrupt handler that will be called every ms
  for (int i = 0; i < NUM_OF_TASKS; i++) {
    if (tasks[i].taskFunc) {
      tasks[i].elapsed++;
      if (tasks[i].elapsed >= tasks[i].period) {
        tasks[i].elapsed = 0;
        tasks[i].taskFunc();
      }
    }
  }
}

void Create_Task(Task *task, uint32_t period) {
  for (int i = 0; i < NUM_OF_TASKS; i++) {
    if (tasks[i].taskFunc == 0) {
      tasks[i].taskFunc = task->taskFunc;
      tasks[i].period = period;
      tasks[i].elapsed = 0;
    }
  }
}
