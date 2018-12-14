#include "main.h"
#include "handwheel.h"
#include "encoder_x.h"
#include "systick.h"
#include "crc.h"
#include "console.h"
#include "GInput.h"
#include "GOutput.h"
#include "stm32f10x_pwr.h"
#include "my_flash.h"

unsigned char EncHWOnOffState = 0;
int32_t MyHWValue = 0;
int32_t MyENCXValue = 0;
extern int32_t MyInputValue; // Extern from file GInput.c
extern int16_t MyOutputValue; // Extern from file GOutput.c

void BuildAndSendFrame(void);
unsigned long OldBuilAndSendFrameTime = 0;

int main(void )
{
	INFLASH_ReadConfig();
	GInputConfig();
	GOutputConfig();
	EncoderXInit(8000000);	// Update Encoder x by Interrupt 800Khz (read pulse 100Khz)
	HandwheelInit(100000); // Update handwheel by Interrupt 100Khz (read pulse 20Khz)
	SystickConfig();
	Console_Init(); 
	
	for (;;)
	{
		MyHWValue = GetHWValueAsPulse();	// Lấy dữ liệu đọc từ handwheel
		MyENCXValue = GetENXValueAsPulse(); // Lấy dữ liệu đọc từ Encoder X
		ReadGInputLoop(); // Lọc và chốt Input
		BuildGInput();		// Gộp các Input thành 1 int32bit để gửi đi
		BuildOutputData();	// Gộp các Output thành 1 int16bit để gửi đi
		Console_Process();
		if (millis() - OldBuilAndSendFrameTime > 20) // 20ms thì gửi dữ liệu 1 lần
		{
			BuildAndSendFrame();	// Xây dựng Frame dữ liệu gửi lên master
			OldBuilAndSendFrameTime = millis();
		}
	
	}
}
//




/*
* BuildAndSendFrame
* Build a Frame and sent to Master 
* (inclue: Current Encoder value, Current Handwheel Value
* Input value)
*/

void ConvertChar8BitTo1ByteASCII(char*OutData, unsigned char Data8);
void ConvertInt16BitTo4ByteASCII(char* OutData, uint16_t Data16);
void ConvertInt32BitTo8ByteASCII(char* OutData , uint32_t Data32);
void ConvertFloat32BitTo8ByteASCII(char* OutData, float Data);
char FrameToSend[36];
void BuildAndSendFrame(void)
{

	uint16_t Crc = 0xFFFF;
	
	FrameToSend[0] = 0x3A;

	/* Edit INPUT first*/
	
	ConvertInt32BitTo8ByteASCII(FrameToSend +1, MyENCXValue);
	ConvertInt32BitTo8ByteASCII(FrameToSend +9, MyHWValue);
	ConvertInt32BitTo8ByteASCII(FrameToSend +17, MyInputValue);
	ConvertInt16BitTo4ByteASCII(FrameToSend +25, MyOutputValue);
	ConvertChar8BitTo1ByteASCII(FrameToSend +29, EncHWOnOffState);
	Crc = Generate_crc16_Code(FrameToSend, 30);
	ConvertInt16BitTo4ByteASCII(FrameToSend+ 30, Crc);
	
	FrameToSend[34] = 0x0D;
	FrameToSend[35] = 0x0A;

	
	
	// Send frame
	#define RS232_PUTC_TO 20000
	for (int i  =0; i< MASTER_FRAME_SIZE; i++)
	{
		unsigned long cnt = 0;
		while(USART_GetFlagStatus(CONSOLE_USART, USART_FLAG_TXE) == RESET)
		{
			 if (cnt ++ > RS232_PUTC_TO)
				 break;
		}
		USART_SendData(CONSOLE_USART, FrameToSend[i]);
	}
}
//


void ConvertInt32BitTo8ByteASCII(char* OutData , uint32_t Data32)
{
	uint8_t p[8];
	for (int i = 1; i<= 8; i++)	p[i-1] = (Data32 >> (32-i*4))&0x0F;
	
	sprintf(OutData, "%X%X%X%X%X%X%X%X", p[0],p[1],p[2],p[3],p[4],p[5],p[6],p[7]);
}
//
void ConvertInt16BitTo4ByteASCII(char* OutData, uint16_t Data16)
{
	uint8_t p[4];
	for (int i = 1; i<=4; i++) p[i-1] = (Data16>>(16-i*4))&0x0F;
	sprintf(OutData, "%X%X%X%X", p[0], p[1], p[2], p[3]);
}
//
void ConvertChar8BitTo1ByteASCII(char*OutData, unsigned char Data8)
{
	sprintf(OutData, "%X",  Data8&0x0F);
}
//


/*-- Chuển số float thành 8 byte ASCII biểu diễn dạng hex của số float --*/
/*-- Ví dụ: Chuyển 0xFFEEBCDA thành {'F','F','E','E','B','C','D','A'}--*/ 
typedef union _floatdata {
  float floatData;
  char  charData[4];
} myfloatdata;

void ConvertFloat32BitTo8ByteASCII(char* OutData, float Data)
{
	myfloatdata  q;
	q.floatData = Data;
	
	sprintf(OutData, "%X%X%X%X%X%X%X%X",
										q.charData[3]>>4,
										q.charData[3]&0x0F,
										q.charData[2]>>4,
										q.charData[2]&0x0F,	
										q.charData[1]>>4,
										q.charData[1]&0x0F,
										q.charData[0]>>4,
										q.charData[0]&0x0F	
										);
}
//

 

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
	/* User can add his own implementation to report the file name and line number,
		ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* Infinite loop */
	while (1)
	{
		char FileName[100];
		sprintf(FileName, "There some error in file %s", (char*)file);
		int c= 10;
	}
}

#endif
//

