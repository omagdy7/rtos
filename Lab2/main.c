#include "inc/tm4c123gh6pm.h"
#include <stdint.h>
#include "scheduler.h"

#define DELAY 2e7

void Led_Init() {
  volatile uint32_t ui32Loop;

  // Enable the GPIO port that is used for the on-board LED.
  SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;

  // Do a dummy read to insert a few cycles after enabling the peripheral.
  ui32Loop = SYSCTL_RCGC2_R;

  // Enable the GPIO pin for the LED (PF3) and LED (PF2).  Set the direction as
  // output, and enable the GPIO pin for digital function.
  GPIO_PORTF_DIR_R = 0x08 | 0x04 | 0x02;
  GPIO_PORTF_DEN_R = 0x08 | 0x04 | 0x02;

  GPIO_PORTF_DATA_R &= ~((1 << 2) | (1 << 3) | (1 << 4));
}


void toggle_red() { GPIO_PORTF_DATA_R ^= 0x02; }

void toggle_blue() { GPIO_PORTF_DATA_R ^= 0x04; }

void toggle_green() { GPIO_PORTF_DATA_R ^= 0x08; }

int main(void) {
  Led_Init();

  create_task(toggle_red, 5);
  create_task(toggle_green, 10);
  create_task(toggle_blue, 20);

  scheduler_run();

  while (1) {
  }
}
