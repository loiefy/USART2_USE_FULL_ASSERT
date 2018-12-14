

#include "main.h"
#include "handwheel.h"

extern unsigned char EncHWOnOffState;
unsigned short old_AB = 0;
int HW_value = 0;
static short enc_state[] =  {0, 1, -1, 0, -1, 0,0 , 1, 1, 0,0,-1, 0, -1, 1,0};
static short enc_state_t[]=	{0,-1,  1, 0,  1, 0,0, -1,-1, 0,0, 1, 0,  1,-1,0};
extern bool IsTogle;
	
void HandwheelInit(unsigned long LoopFrq)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef     TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	
	/*  ------ Config chanel A,B  --------*/
	HW_GPIO_CLK_ENABLE();
	GPIO_InitStructure.GPIO_Pin = HW_A_PIN | HW_B_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(HW_PORT, &GPIO_InitStructure);

	
	/* ------- Config Timer Freq/Mode-------------*/
	HW_TIM_CLK_ENABLE();
	TIM_DeInit(HW_TIMER);
	TIM_TimeBaseStructure.TIM_Prescaler = (SystemCoreClock/1000000)-1;;//((SystemCoreClock/2)/LoopFrq)-1; //
	TIM_TimeBaseStructure.TIM_Period = 5 - 1; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;

	
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(HW_TIMER, &TIM_TimeBaseStructure);
	TIM_Cmd(HW_TIMER, DISABLE);

	
	/*Enable the TIME global interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = HW_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =HW_ISR_PREEMP_PRIORITY;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = HW_ISR_SUB_PRIORITY;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
  TIM_ITConfig(HW_TIMER, TIM_IT_Update, ENABLE);

	//TIM_Cmd(HW_TIMER,ENABLE);
	//EnableHandwheel();
	HW_value = 0;
}



void HandwheelUpdate(void)
{

	old_AB <<= 2; //remember previous state
	old_AB |= ((HW_A<<1)|HW_B)&0x03;

	if (IsTogle == false) HW_value = HW_value + enc_state[(old_AB & 0x0f)];
	else HW_value = HW_value + enc_state_t[(old_AB & 0x0f)];
}


void DisableHandwheel(void) 
{ 
	TIM_Cmd(HW_TIMER,DISABLE);
	EncHWOnOffState &= 0x01; // 0001  - gán 0 vào bít 1, giữ nguyên bit 0
}

void EnableHandwheel(void)
{	
	TIM_Cmd(HW_TIMER,ENABLE);
	EncHWOnOffState |= 0x02; // 0010 - Gán 1 vào bít 1, giữ nguyên bit 0
}

int GetHWValueAsPulse(void) { return HW_value/4;}
void SetHWValueAsPulse(int32_t Pulse)
{
		HW_value = Pulse*4;
}
void ResetHWValue(void) { HW_value = 0;}

