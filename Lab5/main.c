#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "inc/tm4c123gh6pm.h"

#define RED_LED (1U << 1)
#define BLUE_LED (1U << 2)
#define GREEN_LED (1U << 3)

static const uint8_t Red_Color = (1U << 1);
static const uint8_t Blue_Color = (1U << 2);
static const uint8_t Green_Color = (1U << 3);

void microControllerInit(void) {
  // Enable and provide a clock to GPIO Port F in Run mode
  SYSCTL_RCGCGPIO_R |= (1U << 5);

  GPIO_PORTF_DIR_R |= RED_LED | BLUE_LED | GREEN_LED;

  GPIO_PORTF_DEN_R |= RED_LED | BLUE_LED | GREEN_LED;

  // Reset all Leds
  // GPIO_PORTF_DATA_R &= ~(RED_LED | BLUE_LED | GREEN_LED);
}

// This function toggles the RED LED every 1 second
void toggleRedLED(void *pvParameters) {
  for (;;) {
    GPIO_PORTF_DATA_R ^= *(uint8_t *)pvParameters;
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

// This function toggles the BLUE LED every 2 seconds
void toggleBlueLED(void *pvParameters) {
  for (;;) {
    GPIO_PORTF_DATA_R ^= *(uint8_t *)pvParameters;
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}

// This function toggles the GREEN LED every 3 seconds
void toggleGreenLED(void *pvParameters) {
  for (;;) {
    GPIO_PORTF_DATA_R ^= *(uint8_t *)pvParameters;
    vTaskDelay(pdMS_TO_TICKS(3000));
  }
}

int main(void) {
  // Initialize the microcontroller peripherals
  microControllerInit();

  // Create a task that toggles the RED LED
  xTaskCreate(toggleRedLED, "RedLEDTask", configMINIMAL_STACK_SIZE,
              (void *)(&Red_Color), tskIDLE_PRIORITY, NULL);

  // Create a task that toggles the BLUE LED
  xTaskCreate(toggleBlueLED, "BlueLEDTask", configMINIMAL_STACK_SIZE,
              (void *)(&Blue_Color), tskIDLE_PRIORITY, NULL);

  // Create a task that toggles the GREEN LED
  xTaskCreate(toggleGreenLED, "GreenLEDTask", configMINIMAL_STACK_SIZE,
              (void *)(&Green_Color), tskIDLE_PRIORITY, NULL);

  // Start the scheduler.
  vTaskStartScheduler();

  for (;;)
    ;
}
