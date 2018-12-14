#ifndef _GOUTPUT_H_
#define _GOUTPUT_H_

#define NUMBERS_OF_OUTPUT_ARE_USE 8

void SetOutput(unsigned char Index, unsigned char value);
void SetAllOutput(unsigned char value);
void BuildOutputData(void);
void GOutputConfig(void);

#if NUMBERS_OF_OUTPUT_ARE_USE >=1
#define OP0_PORT				GPIOE				
#define OP0_PIN					GPIO_Pin_15
#define OP0_MODE				GPIO_Mode_Out_PP
#endif

#if NUMBERS_OF_OUTPUT_ARE_USE >=2
#define OP1_PORT				GPIOE				
#define OP1_PIN					GPIO_Pin_14
#define OP1_MODE				GPIO_Mode_Out_PP
#endif

#if NUMBERS_OF_OUTPUT_ARE_USE >=3
#define OP2_PORT				GPIOE				
#define OP2_PIN					GPIO_Pin_13
#define OP2_MODE				GPIO_Mode_Out_PP
#endif


#if NUMBERS_OF_OUTPUT_ARE_USE >=4
#define OP3_PORT				GPIOE				
#define OP3_PIN					GPIO_Pin_12
#define OP3_MODE				GPIO_Mode_Out_PP
#endif

#if NUMBERS_OF_OUTPUT_ARE_USE >=5
#define OP4_PORT				GPIOE				
#define OP4_PIN					GPIO_Pin_11
#define OP4_MODE				GPIO_Mode_Out_PP
#endif

#if NUMBERS_OF_OUTPUT_ARE_USE >=6
#define OP5_PORT				GPIOE				
#define OP5_PIN					GPIO_Pin_10
#define OP5_MODE				GPIO_Mode_Out_PP
#endif

#if NUMBERS_OF_OUTPUT_ARE_USE >=7
#define OP6_PORT				GPIOE				
#define OP6_PIN					GPIO_Pin_9
#define OP6_MODE				GPIO_Mode_Out_PP
#endif

#if NUMBERS_OF_OUTPUT_ARE_USE >=8
#define OP7_PORT				GPIOE				
#define OP7_PIN					GPIO_Pin_8
#define OP7_MODE				GPIO_Mode_Out_PP
#endif

#if NUMBERS_OF_OUTPUT_ARE_USE >=9
#define OP8_PORT				GPIOE				
#define OP8_PIN					GPIO_Pin_15
#define OP8_MODE				GPIO_Mode_Out_PP
#endif

#if NUMBERS_OF_OUTPUT_ARE_USE >=10
#define OP9_PORT				GPIOE				
#define OP9_PIN					GPIO_Pin_15
#define OP9_MODE				GPIO_Mode_Out_PP
#endif

#if NUMBERS_OF_OUTPUT_ARE_USE >=11
#define OP10_PORT				GPIOE				
#define OP10_PIN					GPIO_Pin_15
#define OP10_MODE				GPIO_Mode_Out_PP
#endif

#if NUMBERS_OF_OUTPUT_ARE_USE >=12
#define OP11_PORT				GPIOE				
#define OP11_PIN					GPIO_Pin_15
#define OP11_MODE				GPIO_Mode_Out_PP
#endif

#if NUMBERS_OF_OUTPUT_ARE_USE >=13
#define OP12_PORT				GPIOE				
#define OP12_PIN					GPIO_Pin_15
#define OP12_MODE				GPIO_Mode_Out_PP
#endif

#if NUMBERS_OF_OUTPUT_ARE_USE >=14
#define OP13_PORT				GPIOE				
#define OP13_PIN					GPIO_Pin_15
#define OP13_MODE				GPIO_Mode_Out_PP
#endif

#if NUMBERS_OF_OUTPUT_ARE_USE >=15
#define OP14_PORT				GPIOE				
#define OP14_PIN					GPIO_Pin_15
#define OP14_MODE				GPIO_Mode_Out_PP
#endif

#if NUMBERS_OF_OUTPUT_ARE_USE >=16
#define OP15_PORT				GPIOE				
#define OP15_PIN					GPIO_Pin_15
#define OP15_MODE				GPIO_Mode_Out_PP
#endif


#endif


