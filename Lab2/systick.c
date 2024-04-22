#include "systick.h"

void _SystickInit(volatile uint32_t period) {
  _SystickDisable();
  _SystickEnable();
  _SystickPeriodSet(period);
  _SystickPeriodGet();
}

void _SystickDisable(void) { NVIC_ST_CTRL_R = 0; }

void _SystickEnable(void) { NVIC_ST_CTRL_R = 5; }

uint32_t _SystickPeriodGet(void) { return DIO_ReadPort(NVIC_ST_RELOAD_R); }

void _SystickPeriodSet(volatile uint32_t val) {
  DIO_WritePort(&NVIC_ST_RELOAD_R, val);
}

uint32_t _SystickValueGet(void) { return DIO_ReadPort(NVIC_ST_CURRENT_R); }

bool _SysTick_Is_Time_Out(void) {
  return DIO_ReadPin(&NVIC_ST_CTRL_R, 16) != 0;
}
