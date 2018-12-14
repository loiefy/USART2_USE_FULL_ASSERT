
#ifndef _HANDWHEEL_H_
#define _HANDWHEEL_H_

/*-- Cấu hình IO cho chanel A,B ---*/
#define HW_A_PIN 							GPIO_Pin_6
#define HW_B_PIN 							GPIO_Pin_7
#define HW_PORT	 							GPIOB

#define HW_RCC_GPIO_CLK				RCC_APB2Periph_GPIOB
#define HW_GPIO_CLK_ENABLE()	RCC_APB2PeriphClockCmd(HW_RCC_GPIO_CLK, ENABLE)

/*-- Cấu hình Timer để update Encoder state ---*/
#define HW_TIMER							TIM3
#define HW_IRQn								TIM3_IRQn 	
#define HW_IRQHandler					TIM3_IRQHandler			// Tên hàm ngắt Timer
#define HW_RCC_TIM_CLK				RCC_APB1Periph_TIM3
#define HW_TIM_CLK_ENABLE()		RCC_APB1PeriphClockCmd(HW_RCC_TIM_CLK,ENABLE);

#define HW_ISR_PREEMP_PRIORITY	0	// PreempPriority của ngắt Timer
#define HW_ISR_SUB_PRIORITY			1	// Sub Priority của ngắt Timer


#define HW_A 									GPIO_ReadInputDataBit(HW_PORT, HW_A_PIN)
#define HW_B 									GPIO_ReadInputDataBit(HW_PORT, HW_B_PIN)

void HandwheelUpdate(void);
void HandwheelInit(unsigned long LoopFrq);
void DisableHandwheel(void);	
void EnableHandwheel(void);

int GetHWValueAsPulse(void);
void SetHWValueAsPulse(int32_t Pulse);
void ResetHWValue(void);
	

#endif

