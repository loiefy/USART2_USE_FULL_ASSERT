
#include "systick.h"

void SystickConfig(void)
{
	SystemCoreClockUpdate();
	if (SysTick_Config(SystemCoreClock / 1000))
	{
		while (1) 
		{
			int Bug = 1;
		}
	}
}


