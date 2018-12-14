#ifndef _GINPUT_H_
#define _GINPUT_H_

#include "main.h"

#define NUMBER_OF_INPUT_ARE_USE				16
#define MAX_READ_CNT 									50			// Đọc Input 50 lần thì chốt 1 lần.
#define PERCENTAGE_SET_HIGHT_STATE			0.7				

void BuildGInput(void);
void GInputConfig(void);
void ReadGInputLoop(void);
char ReadGInput(unsigned char Index);



#if NUMBER_OF_INPUT_ARE_USE >=1
#define IP0_PORT				GPIOA				// X-
#define IP0_PIN					GPIO_Pin_12
#define IP0_MODE				GPIO_Mode_IN_FLOATING
#endif


#if NUMBER_OF_INPUT_ARE_USE >=2
#define IP1_PORT				GPIOA
#define IP1_PIN					GPIO_Pin_11
#define IP1_MODE				GPIO_Mode_IN_FLOATING
#endif

#if NUMBER_OF_INPUT_ARE_USE >=3
#define IP2_PORT				GPIOA				// X Home
#define IP2_PIN					GPIO_Pin_10
#define IP2_MODE				GPIO_Mode_IN_FLOATING
#endif

#if NUMBER_OF_INPUT_ARE_USE >=4
#define IP3_PORT				GPIOC
#define IP3_PIN					GPIO_Pin_9
#define IP3_MODE				GPIO_Mode_IPU
#endif

#if NUMBER_OF_INPUT_ARE_USE >=5
#define IP4_PORT				GPIOC
#define IP4_PIN					GPIO_Pin_8
#define IP4_MODE				GPIO_Mode_IPU
#endif

#if NUMBER_OF_INPUT_ARE_USE >=6
#define IP5_PORT				GPIOC
#define IP5_PIN					GPIO_Pin_7
#define IP5_MODE				GPIO_Mode_IPU//
#endif

#if NUMBER_OF_INPUT_ARE_USE >=7
#define IP6_PORT				GPIOC
#define IP6_PIN					GPIO_Pin_6
#define IP6_MODE				GPIO_Mode_IPU
#endif

#if NUMBER_OF_INPUT_ARE_USE >=8
#define IP7_PORT				GPIOD
#define IP7_PIN					GPIO_Pin_15
#define IP7_MODE				GPIO_Mode_IPU
#endif

#if NUMBER_OF_INPUT_ARE_USE >=9
#define IP8_PORT				GPIOD
#define IP8_PIN					GPIO_Pin_14
#define IP8_MODE				GPIO_Mode_IPU
#endif

#if NUMBER_OF_INPUT_ARE_USE >=10
#define IP9_PORT				GPIOD
#define IP9_PIN					GPIO_Pin_13
#define IP9_MODE				GPIO_Mode_IPU
#endif

#if NUMBER_OF_INPUT_ARE_USE >=11
#define IP10_PORT				GPIOD
#define IP10_PIN				GPIO_Pin_12
#define IP10_MODE				GPIO_Mode_IPU
#endif

#if NUMBER_OF_INPUT_ARE_USE >=12
#define IP11_PORT				GPIOD				// R Home
#define IP11_PIN				GPIO_Pin_11
#define IP11_MODE				GPIO_Mode_IN_FLOATING
#endif

#if NUMBER_OF_INPUT_ARE_USE >=13
#define IP12_PORT				GPIOD
#define IP12_PIN				GPIO_Pin_10
#define IP12_MODE				GPIO_Mode_IPU
#endif

#if NUMBER_OF_INPUT_ARE_USE >=14
#define IP13_PORT				GPIOD
#define IP13_PIN				GPIO_Pin_9
#define IP13_MODE				GPIO_Mode_IPU
#endif

#if NUMBER_OF_INPUT_ARE_USE >=15
#define IP14_PORT				GPIOD
#define IP14_PIN				GPIO_Pin_8
#define IP14_MODE				GPIO_Mode_IPU
#endif

#if NUMBER_OF_INPUT_ARE_USE >=16
#define IP15_PORT				GPIOB
#define IP15_PIN				GPIO_Pin_15
#define IP15_MODE				GPIO_Mode_IPU
#endif

#if NUMBER_OF_INPUT_ARE_USE >=17
#define IP16_PORT				GPIOD
#define IP16_PIN				GPIO_Pin_8
#define IP16_MODE				GPIO_Mode_IPU
#endif

#if NUMBER_OF_INPUT_ARE_USE >=18
#define IP17_PORT				GPIOD
#define IP17_PIN				GPIO_Pin_8
#define IP17_MODE				GPIO_Mode_IPU
#endif

#if NUMBER_OF_INPUT_ARE_USE >=19
#define IP18_PORT				GPIOD
#define IP18_PIN				GPIO_Pin_8
#define IP18_MODE				GPIO_Mode_IPU
#endif

#if NUMBER_OF_INPUT_ARE_USE >=20
#define IP19_PORT				GPIOD
#define IP19_PIN				GPIO_Pin_8
#define IP19_MODE				GPIO_Mode_IPU
#endif

#if NUMBER_OF_INPUT_ARE_USE >=21
#define IP20_PORT				GPIOD
#define IP20_PIN				GPIO_Pin_8
#define IP20_MODE				GPIO_Mode_IPU
#endif

#if NUMBER_OF_INPUT_ARE_USE >=22
#define IP21_PORT				GPIOD
#define IP21_PIN				GPIO_Pin_8
#define IP21_MODE				GPIO_Mode_IPU
#endif

#if NUMBER_OF_INPUT_ARE_USE >=23
#define IP22_PORT				GPIOD
#define IP22_PIN				GPIO_Pin_8
#define IP22_MODE				GPIO_Mode_IPU
#endif

#if NUMBER_OF_INPUT_ARE_USE >=24
#define IP23_PORT				GPIOD
#define IP23_PIN				GPIO_Pin_8
#define IP23_MODE				GPIO_Mode_IPU
#endif

#if NUMBER_OF_INPUT_ARE_USE >=25
#define IP24_PORT				GPIOD
#define IP24_PIN				GPIO_Pin_8
#define IP24_MODE				GPIO_Mode_IPU
#endif

#if NUMBER_OF_INPUT_ARE_USE >=26
#define IP25_PORT				GPIOD
#define IP25_PIN				GPIO_Pin_8
#define IP25_MODE				GPIO_Mode_IPU
#endif

#if NUMBER_OF_INPUT_ARE_USE >=27
#define IP26_PORT				GPIOD
#define IP26_PIN				GPIO_Pin_8
#define IP26_MODE				GPIO_Mode_IPU
#endif

#if NUMBER_OF_INPUT_ARE_USE >=28
#define IP27_PORT				GPIOD
#define IP27_PIN				GPIO_Pin_8
#define IP27_MODE				GPIO_Mode_IPU
#endif

#if NUMBER_OF_INPUT_ARE_USE >=29
#define IP28_PORT				GPIOD
#define IP28_PIN				GPIO_Pin_8
#define IP28_MODE				GPIO_Mode_IPU
#endif

#if NUMBER_OF_INPUT_ARE_USE >=30
#define IP29_PORT				GPIOD
#define IP29_PIN				GPIO_Pin_8
#define IP29_MODE				GPIO_Mode_IPU
#endif

#if NUMBER_OF_INPUT_ARE_USE >=31
#define IP30_PORT				GPIOD
#define IP30_PIN				GPIO_Pin_8
#define IP30_MODE				GPIO_Mode_IPU
#endif 

#if NUMBER_OF_INPUT_ARE_USE >=32
#define IP31_PORT				GPIOD
#define IP31_PIN				GPIO_Pin_8
#define IP31_MODE				GPIO_Mode_IPU
#endif

#endif



