#include "main.h"
#include "GInput.h"

int32_t MyInputValue = 0;	// Đây là giá trị của toàn bộ 32Input sẽ gửi lên master

typedef struct 
{
		GPIO_TypeDef* PORT;		 // GPIOx
		uint16_t Pin;					 // GPIO_Pin_x
		unsigned char IP_Mode; // Floatting, Pull Up, Pull Down, Analog In 
		char Value;						 // Value after filter (Giá trị của Input sau lọc)
		unsigned char TempVal; // temporary value (to caculate Value)
} InputStruct;

InputStruct MyInputStruct[32] = {NULL};

//InputStruct* P = MyInputStruct; // Just for Debug

/*
* BuildGInput
* Hàm này dùng để gộp 32 Input vào biến MyInputValue để gửi lên Master
*/
void BuildGInput(void)
{
	int32_t Temp =0;
	int32_t Temp2 = 0;
	for (int i = 0;i<32; i++)
	{
		if (i >= NUMBER_OF_INPUT_ARE_USE) break;
		Temp2 = MyInputStruct[i].Value;
		Temp2 = Temp2 &0x01;
		Temp2 = Temp2 << i;
		Temp = Temp | Temp2;
	}
	MyInputValue = Temp;
}


/*
* ReadInput
* Hàm này dùng để đọc các Input tính từ Input 0 -> 255
* Nếu Index >= NUMBER_OF_INPUT_ARE_USE thì Return -1
* Nếu k có vấn đề gì thì Return giá trị cần đọc
*/
char ReadGInput(unsigned char Index)
{
	if (Index >= NUMBER_OF_INPUT_ARE_USE) return -1;
	char res = GPIO_ReadInputDataBit(MyInputStruct[Index].PORT, MyInputStruct[Index].Pin);
	return res;
}


/*
* ReadGInputLoop
* Hàm này dùng để đọc các Input
* Lọc và chốt dữ liệu
*/
uint16_t ReadCnt = 0;
void ReadGInputLoop(void)
{
	for (int i = 0;i< 32; i++)
	{
		if (i >= NUMBER_OF_INPUT_ARE_USE) break;
		char IpVal = ReadGInput(i);
		if (IpVal > 0) MyInputStruct[i].TempVal ++;
	}
	ReadCnt ++;
	
	if (ReadCnt >= MAX_READ_CNT)
	{
		for (int i = 0; i<32; i++)
		{
			if (i >= NUMBER_OF_INPUT_ARE_USE ) break;
			if ((float)(MyInputStruct[i].TempVal / ReadCnt) > PERCENTAGE_SET_HIGHT_STATE)
				MyInputStruct[i].Value = 1;
			else MyInputStruct[i].Value = 0;
			
			MyInputStruct[i].TempVal = 0;
		}
		
		ReadCnt = 0;
	}
}




/*
* GInputConfig
* Hàm này cấu hình các General Input
* Vào file GInput.h để sửa các Port/Pin/Mode cho các Input
*/
void GInputConfig(void)
{
	#if NUMBER_OF_INPUT_ARE_USE >=1
	// Input 0
	MyInputStruct[0].PORT = IP0_PORT;
	MyInputStruct[0].Pin = 	IP0_PIN;
	MyInputStruct[0].IP_Mode = IP0_MODE;
	#endif
	
	#if NUMBER_OF_INPUT_ARE_USE >=2
	// Input 1
	MyInputStruct[1].PORT = IP1_PORT;
	MyInputStruct[1].Pin = 	IP1_PIN;
	MyInputStruct[1].IP_Mode = IP1_MODE;
	#endif
	
	#if NUMBER_OF_INPUT_ARE_USE >=3
	// Input 2
	MyInputStruct[2].PORT = IP2_PORT;
	MyInputStruct[2].Pin = 	IP2_PIN;
	MyInputStruct[2].IP_Mode = IP2_MODE;
	#endif
	
	#if NUMBER_OF_INPUT_ARE_USE >=4
	// Input 3
	MyInputStruct[3].PORT = IP3_PORT;
	MyInputStruct[3].Pin = 	IP3_PIN;
	MyInputStruct[3].IP_Mode = IP3_MODE;
	#endif
	
	#if NUMBER_OF_INPUT_ARE_USE >=5
	// Input 4
	MyInputStruct[4].PORT = IP4_PORT;
	MyInputStruct[4].Pin = 	IP4_PIN;
	MyInputStruct[4].IP_Mode = IP4_MODE;
	#endif
	
	#if NUMBER_OF_INPUT_ARE_USE >=6
	// Input 5
	MyInputStruct[5].PORT = IP5_PORT;
	MyInputStruct[5].Pin = 	IP5_PIN;
	MyInputStruct[5].IP_Mode = IP5_MODE;
	#endif
	
	#if NUMBER_OF_INPUT_ARE_USE >=7
	// Input 6
	MyInputStruct[6].PORT = IP6_PORT;
	MyInputStruct[6].Pin = 	IP6_PIN;
	MyInputStruct[6].IP_Mode = IP6_MODE;
	#endif
	
	#if NUMBER_OF_INPUT_ARE_USE >=8
	// Input 7
	MyInputStruct[7].PORT = IP7_PORT;
	MyInputStruct[7].Pin = 	IP7_PIN;	
	MyInputStruct[7].IP_Mode = IP7_MODE;
	#endif
	
	#if NUMBER_OF_INPUT_ARE_USE >=9
	// Input 8
	MyInputStruct[8].PORT = IP8_PORT;
	MyInputStruct[8].Pin = 	IP8_PIN;	
	MyInputStruct[8].IP_Mode = IP8_MODE;
	#endif
	
	#if NUMBER_OF_INPUT_ARE_USE >=10
	// Input 9
	MyInputStruct[9].PORT = IP9_PORT;
	MyInputStruct[9].Pin = 	IP9_PIN;	
	MyInputStruct[9].IP_Mode = IP9_MODE;
	#endif
	
	#if NUMBER_OF_INPUT_ARE_USE >=11
	// Input 10
	MyInputStruct[10].PORT = IP10_PORT;
	MyInputStruct[10].Pin =  IP10_PIN;	
	MyInputStruct[10].IP_Mode = IP10_MODE;
	#endif
	
	#if NUMBER_OF_INPUT_ARE_USE >=12
	// Input 11
	MyInputStruct[11].PORT = IP11_PORT;
	MyInputStruct[11].Pin =  IP11_PIN;	
	MyInputStruct[11].IP_Mode = IP11_MODE;
	#endif
	
	#if NUMBER_OF_INPUT_ARE_USE >=13
	// Input 12
	MyInputStruct[12].PORT = IP12_PORT;
	MyInputStruct[12].Pin =  IP12_PIN;	
	MyInputStruct[12].IP_Mode = IP12_MODE;
	#endif
	
	#if NUMBER_OF_INPUT_ARE_USE >=14
	// Input 13
	MyInputStruct[13].PORT = IP13_PORT;
	MyInputStruct[13].Pin =  IP13_PIN;	
	MyInputStruct[13].IP_Mode = IP13_MODE;
	#endif
	
	#if NUMBER_OF_INPUT_ARE_USE >=15
	// Input 14
	MyInputStruct[14].PORT = IP14_PORT;
	MyInputStruct[14].Pin =  IP14_PIN;	
	MyInputStruct[14].IP_Mode = IP14_MODE;
	#endif
	
	#if NUMBER_OF_INPUT_ARE_USE >=16
	// Input 15
	MyInputStruct[15].PORT = IP15_PORT;
	MyInputStruct[15].Pin =  IP15_PIN;
	MyInputStruct[15].IP_Mode = IP15_MODE;
	#endif
	
	#if NUMBER_OF_INPUT_ARE_USE >=17
	// Input 16
	MyInputStruct[16].PORT = IP16_PORT;
	MyInputStruct[16].Pin =  IP16_PIN;
	MyInputStruct[16].IP_Mode = IP16_MODE;
	#endif
	
	#if NUMBER_OF_INPUT_ARE_USE >=18
	// Input 17
	MyInputStruct[17].PORT = IP17_PORT;
	MyInputStruct[17].Pin =  IP17_PIN;
	MyInputStruct[17].IP_Mode = IP17_MODE;
	#endif
	
	#if NUMBER_OF_INPUT_ARE_USE >=19
	// Input 18
	MyInputStruct[18].PORT = IP18_PORT;
	MyInputStruct[18].Pin =  IP18_PIN;
	MyInputStruct[18].IP_Mode = IP18_MODE;
	#endif
	
	#if NUMBER_OF_INPUT_ARE_USE >=20
	// Input 19
	MyInputStruct[19].PORT = IP19_PORT;
	MyInputStruct[19].Pin =  IP19_PIN;
	MyInputStruct[19].IP_Mode = IP19_MODE;
	#endif
	
	#if NUMBER_OF_INPUT_ARE_USE >=21
	// Input 20
	MyInputStruct[20].PORT = IP20_PORT;
	MyInputStruct[20].Pin =  IP20_PIN;
	MyInputStruct[20].IP_Mode = IP20_MODE;
	#endif
	
	#if NUMBER_OF_INPUT_ARE_USE >=22
	// Input 21
	MyInputStruct[21].PORT = IP21_PORT;
	MyInputStruct[21].Pin =  IP21_PIN;
	MyInputStruct[21].IP_Mode = IP21_MODE;
	#endif
	
	#if NUMBER_OF_INPUT_ARE_USE >=23
	// Input 22
	MyInputStruct[22].PORT = IP22_PORT;
	MyInputStruct[22].Pin =  IP22_PIN;
	MyInputStruct[22].IP_Mode = IP22_MODE;
	#endif
	
	#if NUMBER_OF_INPUT_ARE_USE >=24
	// Input 23
	MyInputStruct[23].PORT = IP23_PORT;
	MyInputStruct[23].Pin =  IP23_PIN;
	MyInputStruct[23].IP_Mode = IP23_MODE;
	#endif
	
	#if NUMBER_OF_INPUT_ARE_USE >=25
	// Input 24
	MyInputStruct[24].PORT = IP24_PORT;
	MyInputStruct[24].Pin =  IP24_PIN;
	MyInputStruct[24].IP_Mode = IP24_MODE;
	#endif
	
	#if NUMBER_OF_INPUT_ARE_USE >=26
	// Input 25
	MyInputStruct[25].PORT = IP25_PORT;
	MyInputStruct[25].Pin =  IP25_PIN;
	MyInputStruct[25].IP_Mode = IP25_MODE;
	#endif
	
	#if NUMBER_OF_INPUT_ARE_USE >=27
	// Input 26
	MyInputStruct[26].PORT = IP26_PORT;
	MyInputStruct[26].Pin =  IP26_PIN;
	MyInputStruct[26].IP_Mode = IP26_MODE;
	#endif
	
	#if NUMBER_OF_INPUT_ARE_USE >=28
	// Input 27
	MyInputStruct[27].PORT = IP27_PORT;
	MyInputStruct[27].Pin =  IP27_PIN;
	MyInputStruct[27].IP_Mode = IP27_MODE;
	#endif
	
	#if NUMBER_OF_INPUT_ARE_USE >=29
	// Input 28
	MyInputStruct[28].PORT = IP28_PORT;
	MyInputStruct[28].Pin =  IP28_PIN;
	MyInputStruct[28].IP_Mode = IP28_MODE;
	#endif
	
	#if NUMBER_OF_INPUT_ARE_USE >=30
	// Input 29
	MyInputStruct[29].PORT = IP29_PORT;
	MyInputStruct[29].Pin =  IP29_PIN;
	MyInputStruct[29].IP_Mode = IP29_MODE;
	#endif
	
	#if NUMBER_OF_INPUT_ARE_USE >=31
	// Input 30
	MyInputStruct[30].PORT = IP30_PORT;
	MyInputStruct[30].Pin =  IP30_PIN;
	MyInputStruct[30].IP_Mode = IP30_MODE;
	#endif
	
	#if NUMBER_OF_INPUT_ARE_USE >=32
	// Input 31
	MyInputStruct[31].PORT = IP31_PORT;
	MyInputStruct[31].Pin =  IP31_PIN;
	MyInputStruct[31].IP_Mode = IP31_MODE;
	#endif
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA | 
												RCC_APB2Periph_GPIOB |
												RCC_APB2Periph_GPIOC |
												RCC_APB2Periph_GPIOD |
												RCC_APB2Periph_GPIOE 
												,ENABLE);
	for (int i = 0; i<NUMBER_OF_INPUT_ARE_USE; i++)
	{
		GPIO_InitTypeDef GPIO_InitStructure;

		GPIO_InitStructure.GPIO_Pin = MyInputStruct[i].Pin;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_InitStructure.GPIO_Mode = MyInputStruct[i].IP_Mode;
		GPIO_Init((MyInputStruct+i)->PORT, &GPIO_InitStructure);
	}
}



