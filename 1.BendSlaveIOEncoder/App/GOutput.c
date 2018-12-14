#include "GOutput.h"
#include "main.h"

int16_t MyOutputValue = 0;	// Đây là giá trị của toàn bộ 32Output sẽ gửi lên master

typedef struct 
{
		GPIO_TypeDef* PORT;		 // GPIOx
		uint16_t Pin;					 // GPIO_Pin_x
		unsigned char OP_Mode; // Floatting, Pull Up, Pull Down, Analog In 
} OutputStruct;

OutputStruct MyOutputStruct[32] = {NULL};


/*
* BuildOutputData
* Hàm này gộp các Output vào biến MyOutputValue để gửi lên master
*/
void BuildOutputData(void)
{
 	int16_t Temp =0;
	int16_t Temp2 = 0;
	for (int i = 0;i<16; i++)
	{
		if (i >= NUMBERS_OF_OUTPUT_ARE_USE) break;
		Temp2 = GPIO_ReadOutputDataBit(MyOutputStruct[i].PORT, MyOutputStruct[i].Pin);
		Temp2 = Temp2 &0x01;
		Temp2 = Temp2 << i;
		Temp = Temp | Temp2;
	}
	MyOutputValue = Temp;
}



/*
* SetOutput
* hàm này dùng để Set các output
*/
void SetOutput(unsigned char Index, unsigned char value)
{
	GPIO_WriteBit(MyOutputStruct[Index].PORT, MyOutputStruct[Index].Pin, value == 0? Bit_RESET: Bit_SET);
}


/*
* SetAllOutput
* Hàm này set tất cả Ouput về 1 giá trị 
*/
void SetAllOutput(unsigned char value)
{
	for (int i = 0;i< 32; i++)
	{
		if (i >= NUMBERS_OF_OUTPUT_ARE_USE ) break;
		GPIO_WriteBit(MyOutputStruct[i].PORT, MyOutputStruct[i].Pin, value == 0? Bit_RESET: Bit_SET);
	}
}


/*
* GOutputConfig
* Hàm này cấu hình các General Output
* Vào file GOutput.h để sửa các Port/Pin/Mode cho các Output
*/
void GOutputConfig(void)
{
	#if NUMBERS_OF_OUTPUT_ARE_USE >=1
	// Output 0
	MyOutputStruct[0].PORT = OP0_PORT;
	MyOutputStruct[0].Pin = 	OP0_PIN;
	MyOutputStruct[0].OP_Mode = OP0_MODE;
	#endif
	
	#if NUMBERS_OF_OUTPUT_ARE_USE >=2
	// Output 1
	MyOutputStruct[1].PORT = OP1_PORT;
	MyOutputStruct[1].Pin = 	OP1_PIN;
	MyOutputStruct[1].OP_Mode = OP1_MODE;
	#endif
	
	#if NUMBERS_OF_OUTPUT_ARE_USE >=3
	// Output 2
	MyOutputStruct[2].PORT = OP2_PORT;
	MyOutputStruct[2].Pin = 	OP2_PIN;
	MyOutputStruct[2].OP_Mode = OP2_MODE;
	#endif
	
	#if NUMBERS_OF_OUTPUT_ARE_USE >=4
	// Output 3
	MyOutputStruct[3].PORT = OP3_PORT;
	MyOutputStruct[3].Pin = 	OP3_PIN;
	MyOutputStruct[3].OP_Mode = OP3_MODE;
	#endif
	
	#if NUMBERS_OF_OUTPUT_ARE_USE >=5
	// Output 4
	MyOutputStruct[4].PORT = OP4_PORT;
	MyOutputStruct[4].Pin = 	OP4_PIN;
	MyOutputStruct[4].OP_Mode = OP4_MODE;
	#endif
	
	#if NUMBERS_OF_OUTPUT_ARE_USE >=6
	// Output 5
	MyOutputStruct[5].PORT = OP5_PORT;
	MyOutputStruct[5].Pin = 	OP5_PIN;
	MyOutputStruct[5].OP_Mode = OP5_MODE;
	#endif
	
	#if NUMBERS_OF_OUTPUT_ARE_USE >=7
	// Output 6
	MyOutputStruct[6].PORT = OP6_PORT;
	MyOutputStruct[6].Pin = 	OP6_PIN;
	MyOutputStruct[6].OP_Mode = OP6_MODE;
	#endif
	
	#if NUMBERS_OF_OUTPUT_ARE_USE >=8
	// Output 7
	MyOutputStruct[7].PORT = OP7_PORT;
	MyOutputStruct[7].Pin = 	OP7_PIN;	
	MyOutputStruct[7].OP_Mode = OP7_MODE;
	#endif
	
	#if NUMBERS_OF_OUTPUT_ARE_USE >=9
	// Output 8
	MyOutputStruct[8].PORT = OP8_PORT;
	MyOutputStruct[8].Pin = 	OP8_PIN;	
	MyOutputStruct[8].OP_Mode = OP8_MODE;
	#endif
	
	#if NUMBERS_OF_OUTPUT_ARE_USE >=10
	// Output 9
	MyOutputStruct[9].PORT = OP9_PORT;
	MyOutputStruct[9].Pin = 	OP9_PIN;	
	MyOutputStruct[9].OP_Mode = OP9_MODE;
	#endif
	
	#if NUMBERS_OF_OUTPUT_ARE_USE >=11
	// Output 10
	MyOutputStruct[10].PORT = OP10_PORT;
	MyOutputStruct[10].Pin =  OP10_PIN;	
	MyOutputStruct[10].OP_Mode = OP10_MODE;
	#endif
	
	#if NUMBERS_OF_OUTPUT_ARE_USE >=12
	// Output 11
	MyOutputStruct[11].PORT = OP11_PORT;
	MyOutputStruct[11].Pin =  OP11_PIN;	
	MyOutputStruct[11].OP_Mode = OP11_MODE;
	#endif
	
	#if NUMBERS_OF_OUTPUT_ARE_USE >=13
	// Output 12
	MyOutputStruct[12].PORT = OP12_PORT;
	MyOutputStruct[12].Pin =  OP12_PIN;	
	MyOutputStruct[12].OP_Mode = OP12_MODE;
	#endif
	
	#if NUMBERS_OF_OUTPUT_ARE_USE >=14
	// Output 13
	MyOutputStruct[13].PORT = OP13_PORT;
	MyOutputStruct[13].Pin =  OP13_PIN;	
	MyOutputStruct[13].OP_Mode = OP13_MODE;
	#endif
	
	#if NUMBERS_OF_OUTPUT_ARE_USE >=15
	// Output 14
	MyOutputStruct[14].PORT = OP14_PORT;
	MyOutputStruct[14].Pin =  OP14_PIN;	
	MyOutputStruct[14].OP_Mode = OP14_MODE;
	#endif
	
	#if NUMBERS_OF_OUTPUT_ARE_USE >=16
	// Output 15
	MyOutputStruct[15].PORT = OP15_PORT;
	MyOutputStruct[15].Pin =  OP15_PIN;
	MyOutputStruct[15].OP_Mode = OP15_MODE;
	#endif
	
	#if NUMBERS_OF_OUTPUT_ARE_USE >=17
	// Output 16
	MyOutputStruct[16].PORT = OP16_PORT;
	MyOutputStruct[16].Pin =  OP16_PIN;
	MyOutputStruct[16].OP_Mode = OP16_MODE;
	#endif
	
	#if NUMBERS_OF_OUTPUT_ARE_USE >=18
	// Output 17
	MyOutputStruct[17].PORT = OP17_PORT;
	MyOutputStruct[17].Pin =  OP17_PIN;
	MyOutputStruct[17].OP_Mode = OP17_MODE;
	#endif
	
	#if NUMBERS_OF_OUTPUT_ARE_USE >=19
	// Output 18
	MyOutputStruct[18].PORT = OP18_PORT;
	MyOutputStruct[18].Pin =  OP18_PIN;
	MyOutputStruct[18].OP_Mode = OP18_MODE;
	#endif
	
	#if NUMBERS_OF_OUTPUT_ARE_USE >=20
	// Output 19
	MyOutputStruct[19].PORT = OP19_PORT;
	MyOutputStruct[19].Pin =  OP19_PIN;
	MyOutputStruct[19].OP_Mode = OP19_MODE;
	#endif
	
	#if NUMBERS_OF_OUTPUT_ARE_USE >=21
	// Output 20
	MyOutputStruct[20].PORT = OP20_PORT;
	MyOutputStruct[20].Pin =  OP20_PIN;
	MyOutputStruct[20].OP_Mode = OP20_MODE;
	#endif
	
	#if NUMBERS_OF_OUTPUT_ARE_USE >=22
	// Output 21
	MyOutputStruct[21].PORT = OP21_PORT;
	MyOutputStruct[21].Pin =  OP21_PIN;
	MyOutputStruct[21].OP_Mode = OP21_MODE;
	#endif
	
	#if NUMBERS_OF_OUTPUT_ARE_USE >=23
	// Output 22
	MyOutputStruct[22].PORT = OP22_PORT;
	MyOutputStruct[22].Pin =  OP22_PIN;
	MyOutputStruct[22].OP_Mode = OP22_MODE;
	#endif
	
	#if NUMBERS_OF_OUTPUT_ARE_USE >=24
	// Output 23
	MyOutputStruct[23].PORT = OP23_PORT;
	MyOutputStruct[23].Pin =  OP23_PIN;
	MyOutputStruct[23].OP_Mode = OP23_MODE;
	#endif
	
	#if NUMBERS_OF_OUTPUT_ARE_USE >=25
	// Output 24
	MyOutputStruct[24].PORT = OP24_PORT;
	MyOutputStruct[24].Pin =  OP24_PIN;
	MyOutputStruct[24].OP_Mode = OP24_MODE;
	#endif
	
	#if NUMBERS_OF_OUTPUT_ARE_USE >=26
	// Output 25
	MyOutputStruct[25].PORT = OP25_PORT;
	MyOutputStruct[25].Pin =  OP25_PIN;
	MyOutputStruct[25].OP_Mode = OP25_MODE;
	#endif
	
	#if NUMBERS_OF_OUTPUT_ARE_USE >=27
	// Output 26
	MyOutputStruct[26].PORT = OP26_PORT;
	MyOutputStruct[26].Pin =  OP26_PIN;
	MyOutputStruct[26].OP_Mode = OP26_MODE;
	#endif
	
	#if NUMBERS_OF_OUTPUT_ARE_USE >=28
	// Output 27
	MyOutputStruct[27].PORT = OP27_PORT;
	MyOutputStruct[27].Pin =  OP27_PIN;
	MyOutputStruct[27].OP_Mode = OP27_MODE;
	#endif
	
	#if NUMBERS_OF_OUTPUT_ARE_USE >=29
	// Output 28
	MyOutputStruct[28].PORT = OP28_PORT;
	MyOutputStruct[28].Pin =  OP28_PIN;
	MyOutputStruct[28].OP_Mode = OP28_MODE;
	#endif
	
	#if NUMBERS_OF_OUTPUT_ARE_USE >=30
	// Output 29
	MyOutputStruct[29].PORT = OP29_PORT;
	MyOutputStruct[29].Pin =  OP29_PIN;
	MyOutputStruct[29].OP_Mode = OP29_MODE;
	#endif
	
	#if NUMBERS_OF_OUTPUT_ARE_USE >=31
	// Output 30
	MyOutputStruct[30].PORT = OP30_PORT;
	MyOutputStruct[30].Pin =  OP30_PIN;
	MyOutputStruct[30].OP_Mode = OP30_MODE;
	#endif
	
	#if NUMBERS_OF_OUTPUT_ARE_USE >=32
	// Output 31
	MyOutputStruct[31].PORT = OP31_PORT;
	MyOutputStruct[31].Pin =  OP31_PIN;
	MyOutputStruct[31].OP_Mode = OP31_MODE;
	#endif
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA | 
												RCC_APB2Periph_GPIOB |
												RCC_APB2Periph_GPIOC |
												RCC_APB2Periph_GPIOD |
												RCC_APB2Periph_GPIOE 
												,ENABLE);
	for (int i = 0; i<NUMBERS_OF_OUTPUT_ARE_USE; i++)
	{
		GPIO_InitTypeDef GPIO_InitStructure;

		GPIO_InitStructure.GPIO_Pin = MyOutputStruct[i].Pin;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_InitStructure.GPIO_Mode = MyOutputStruct[i].OP_Mode;
		GPIO_Init((MyOutputStruct+i)->PORT, &GPIO_InitStructure);
	}
}



