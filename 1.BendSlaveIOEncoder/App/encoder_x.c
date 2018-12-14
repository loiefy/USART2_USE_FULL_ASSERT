
#include "main.h"
#include "encoder_x.h"

extern unsigned char EncHWOnOffState;
unsigned short oldx_AB = 0;
int ENX_value = 0;
static short encx_state[] =  {0, 1, -1, 0, -1, 0,0 , 1, 1, 0,0,-1, 0, -1, 1,0};
static short encx_state_t[]= {0,-1,  1, 0,  1, 0,0, -1,-1, 0,0, 1, 0,  1,-1,0};
bool IsTogle  = false;
	
void EncoderXInit(unsigned long LoopFrq)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef     TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	
	/*  ------ Config chanel A,B  --------*/
	ENX_GPIO_CLK_ENABLE();
	GPIO_InitStructure.GPIO_Pin = ENX_A_PIN | ENX_B_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(ENX_PORT, &GPIO_InitStructure);

	
	/* ------- Config Timer Freq/Mode-------------*/
	ENX_TIM_CLK_ENABLE();
	TIM_DeInit(ENX_TIMER);
	TIM_TimeBaseStructure.TIM_Prescaler = ((SystemCoreClock/2)/LoopFrq)-1; //
	TIM_TimeBaseStructure.TIM_Period = 10 - 1; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;

	
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(ENX_TIMER, &TIM_TimeBaseStructure);
	TIM_Cmd(ENX_TIMER, DISABLE);

	
	/*Enable the TIME global interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = ENX_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =ENX_ISR_PREEMP_PRIORITY;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = ENX_ISR_SUB_PRIORITY;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
  TIM_ITConfig(ENX_TIMER, TIM_IT_Update, ENABLE);

	//TIM_Cmd(ENX_TIMER,ENABLE);
	//EnableEncoderX();
	ENX_value = 0;
}



void EncoderXUpdate(void)
{

	oldx_AB <<= 2; //remember previous state
	oldx_AB |= ((ENX_A<<1)|ENX_B)&0x03;

	if (IsTogle == false) ENX_value = ENX_value + encx_state[(oldx_AB & 0x0f)];
	else ENX_value = ENX_value + encx_state_t[(oldx_AB & 0x0f)];
}


void DisableEncoderX(void) 
{ 
	TIM_Cmd(ENX_TIMER,DISABLE); //0010 = 2
	EncHWOnOffState &= 0x02;
}

void EnableEncoderX(void)
{
	TIM_Cmd(ENX_TIMER,ENABLE); // 0001 = 1
	EncHWOnOffState |= 0x01;
}

int GetENXValueAsPulse(void) { return ENX_value/4;}

void SetENXValueAsPulse(int32_t Pulse)
{
	ENX_value = Pulse *4;
}

void ResetENXValue(void) { ENX_value = 0;}

