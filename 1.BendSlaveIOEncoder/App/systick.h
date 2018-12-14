#ifndef _SYSTICK_H_

#define _SYSTICK_H_

#include "main.h"

void SystickConfig(void);
void delayMs(uint16_t msec);
unsigned long millis(void);

#endif

