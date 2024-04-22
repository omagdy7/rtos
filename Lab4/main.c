#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "inc/tm4c123gh6pm.h"

#define RED_LED (1U << 1) // Assuming RED LED is connected to Port F pin 1

void microControllerInit(void) {
  // Enable and provide a clock to GPIO Port F in Run mode
  SYSCTL_RCGCGPIO_R |= (1U << 5);
  // Set the direction of PF1 (RED LED) as output
  GPIO_PORTF_DIR_R |= RED_LED;
  // Enable the GPIO pins for digital function.
  GPIO_PORTF_DEN_R |= RED_LED;
}

void changeLEDState(void) {
  // Toggle the RED LED
  GPIO_PORTF_DATA_R ^= RED_LED;
}

// This function toggles the RED LED
void toggleRedLED(void *pvParameters) {
  for (;;) {
    // Toggle the state of the RED LED
    changeLEDState();
    // Delay for 1000ms
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

int main(void) {
  // Initialize the microcontroller peripherals
  microControllerInit();

  // Create a task that toggles the RED LED
  xTaskCreate(toggleRedLED,             // Function that implements the task.
              "LEDTask",                // Text name for the task.
              configMINIMAL_STACK_SIZE, // Stack size in words, not bytes.
              NULL,                     // Parameter passed into the task.
              tskIDLE_PRIORITY, // Priority at which the task is created.
              NULL              // Pointer to the task handle.
  );

  // Start the scheduler.
  vTaskStartScheduler();

  // The following line should never be reached. If it is, there is insufficient
  // heap memory.
  for (;;)
    ;
}
