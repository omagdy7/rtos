#include "color.h"
#include "tick.h"
#include "/home/omar/programming/thirdparties/tiva-c/driverlib/sysctl.h"
#include "/home/omar/programming/thirdparties/tiva-c/driverlib/systick.h"

// static int cnt = 1;

void portFInit() {
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)) {
  };
  GPIOUnlockPin(GPIO_PORTF_BASE,
                GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4);
  GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
  GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4, GPIO_STRENGTH_2MA,
                   GPIO_PIN_TYPE_STD_WPU);
}

void toggle_white() {
  if ((GPIO_PORTF_DATA_R & 0xe) == 0xe) {
    reset_color();
  } else {
    set_color(WHITE);
  }
}

void SysTick_Handler() { toggle_color(WHITE); }

void toggle_polling() {
  DIO_Init('F', 0xe, 0x11);
  reset_color();
  _SystickInit(PERIOD);
  while (1) {
    while (_SysTick_Is_Time_Out()) {
      toggle_color(RED);
    }
  }
}

void toggle_interrupts() {
  SysTickEnable();
  SysTickIntEnable();
  SysTickPeriodSet(PERIOD);
  while (1) {
  }
}

int main() {
  // toggle_polling();
  toggle_interrupts();
}
