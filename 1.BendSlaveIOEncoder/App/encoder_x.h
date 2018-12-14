#ifndef _ENC_X_

#define _ENC_X_


/*-- Cấu hình IO cho chanel A,B ---*/
#define ENX_A_PIN 							GPIO_Pin_6
#define ENX_B_PIN 							GPIO_Pin_7
#define ENX_PORT	 							GPIOB

#define ENX_RCC_GPIO_CLK				RCC_APB2Periph_GPIOB
#define ENX_GPIO_CLK_ENABLE()	RCC_APB2PeriphClockCmd(ENX_RCC_GPIO_CLK, ENABLE)

/*-- Cấu hình Timer để update Encoder state ---*/
#define ENX_TIMER								TIM4
#define ENX_IRQn								TIM4_IRQn 	
#define ENX_IRQHandler					TIM4_IRQHandler			// Tên hàm ngắt Timer
#define ENX_RCC_TIM_CLK					RCC_APB1Periph_TIM4
#define ENX_TIM_CLK_ENABLE()		RCC_APB1PeriphClockCmd(ENX_RCC_TIM_CLK,ENABLE);

#define ENX_ISR_PREEMP_PRIORITY		0	// PreempPriority của ngắt Timer
#define ENX_ISR_SUB_PRIORITY			0	// Sub Priority của ngắt Timer


#define ENX_A 									GPIO_ReadInputDataBit(ENX_PORT, ENX_A_PIN)
#define ENX_B 									GPIO_ReadInputDataBit(ENX_PORT, ENX_B_PIN)

void EncoderXUpdate(void);
void EncoderXInit(unsigned long LoopFrq);
void DisableEncoderX(void);	
void EnableEncoderX(void);

int GetENXValueAsPulse(void);
void SetENXValueAsPulse(int32_t Pulse);
void ResetENXValue(void);
	


#endif

