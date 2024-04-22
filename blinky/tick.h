#include "dio.h"
#include "color.h"

#define NVIC_BASE_ADDRESS 0xE000E000
#define PERIOD (0xFFFFFF - 1) / 2

void _SystickInit(volatile uint32_t period);

void _SystickDisable(void);

void _SystickEnable(void);

uint32_t _SystickPeriodGet(void);

void _SystickPeriodSet(volatile uint32_t val);

uint32_t _SysticValueGet(void);

bool _SysTick_Is_Time_Out(void);
