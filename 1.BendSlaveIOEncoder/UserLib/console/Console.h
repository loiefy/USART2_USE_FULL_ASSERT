/** file : console.h
** author: dungnb@havicom.vn
**/
#ifndef __CONSOLE_H
#define __CONSOLE_H

#include "main.h"

/*define UART1 GPIO and Clock*/
#define CONSOLE_RX_PIN			GPIO_Pin_3
#define CONSOLE_TX_PIN			GPIO_Pin_2
#define CONSOLE_GPIO				GPIOA
#define CONSOLE_GPIO_CLOCK	RCC_APB2Periph_GPIOA
#define CONSOLE_AFIO_CLOCK	RCC_APB2Periph_AFIO
#define CONSOLE_USART				USART2
#define CONSOLE_IRQ					USART2_IRQn
#define CONSOLE_IRQHanler		USART2_IRQHandler
#define CONSOLE_BAUDRATE		115200

#define CONSOLE_CLK					RCC_APB1Periph_USART2
#define CONSOLE_CLK_ENABLE()	RCC_APB1PeriphClockCmd(CONSOLE_CLK, ENABLE)
#define CONSOLE_PREEMP_PRIORITY		0
#define CONSOLE_SUB_PRIORITY			2
typedef struct
{
    char buffer[32];
    int	leng;
} BUFFER_typdef;



#define START_CODE	0x3A
#define END_CODE	0x0A


/* Define Run command*/

void Console_Init(void);
void Console_Process(void);

	
#endif
