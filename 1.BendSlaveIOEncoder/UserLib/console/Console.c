/** file : console.h
** author: dungnb@havicom.vn
**/

#include "console.h"
#include "Ring_buffer.h"
#include "command.h"
#include "my_flash.h"
#pragma import(__use_no_semihosting_swi)

struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f)
{
    while(USART_GetFlagStatus(CONSOLE_USART, USART_FLAG_TXE) == RESET);
 
  USART_SendData(CONSOLE_USART, ch);
 
  return(ch);
}
 
int fgetc(FILE *f)
{
    char ch;
 
    while(USART_GetFlagStatus(CONSOLE_USART, USART_FLAG_RXNE) == RESET);
 
    ch = USART_ReceiveData(CONSOLE_USART);
 
  return((int)ch);
}
 
int ferror(FILE *f)
{
  /* Your implementation of ferror */
  return EOF;
}
 
void _ttywrch(int ch)
{
    while(USART_GetFlagStatus(CONSOLE_USART, USART_FLAG_TXE) == RESET);
 
  USART_SendData(CONSOLE_USART, ch);
}
void _sys_exit(int return_code)
{
label:  goto label;  /* endless loop */
}



BUFFER_typdef Console_Rx;
ring_buffer_typdef Console_Rx_buffer;


char * check_ip;
//extern int encoder_zero;

void Console_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
		/* Configure the system clocks */
	//RCC_Configuration();	
	RCC_APB2PeriphClockCmd(CONSOLE_GPIO_CLOCK , ENABLE);
	/* 
	  *	configure UART pins	
	  */	
	
	/* Enable UART clock, if using USART2 or USART3 ... we must use RCC_APB1PeriphClockCmd(RCC_APB1Periph_USARTx, ENABLE) */
	CONSOLE_CLK_ENABLE(); 
	
	/* Configure the NVIC Preemption Priority Bits */  

	/* Enable the USART1 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = CONSOLE_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = CONSOLE_PREEMP_PRIORITY;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = CONSOLE_SUB_PRIORITY;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);


	/* Configure PA9 for USART Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = CONSOLE_TX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(CONSOLE_GPIO, &GPIO_InitStructure);

	/* Configure PA10 for USART Rx as input floating */
	GPIO_InitStructure.GPIO_Pin = CONSOLE_RX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(CONSOLE_GPIO, &GPIO_InitStructure);	
	
	/* USARTx configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  	*/
	USART_InitStructure.USART_BaudRate = CONSOLE_BAUDRATE;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	

	/* USART configuration */
	USART_Init(CONSOLE_USART, &USART_InitStructure);
	
	USART_ITConfig(CONSOLE_USART, USART_IT_RXNE, ENABLE);
	//USART_ITConfig(USART1, USART_IT_TXE, ENABLE);

	/* Enable USART */
	USART_Cmd(CONSOLE_USART, ENABLE);	
	
}





/*
---------------------------------------CONSOLE_DECODE-----------------------------------------------------------
----------------------------------------------------------------------------------------------------------------
*/
unsigned char Convert2ByteASCIIToData8(char * DataIn);
unsigned short Convert4ByteASCIIToData16(char* DataIn);
int32_t Convert8ByteASCIIToData32(char* DataIn);
extern bool IsTogle;
/*
	Console_Decode
	This Function find Command in String *buffer 
	and operate Command if found
*/
#include "crc.h"
#include "encoder_x.h"
#include "handwheel.h"
#include "GOutput.h"

void Console_Decode(BUFFER_typdef *buffer)
{
	char *Cmdbuff;
	Cmdbuff = ( char *)buffer->buffer;
	
	unsigned Cmd_code = Convert2ByteASCIIToData8(Cmdbuff +1);
	switch(Cmd_code)
	{
		case SL_CMD_SETENC_PLS:	// Cài tọa độ encoder X (theo xung)
			{
				unsigned char CRC8 = 0xFF;
				unsigned char Crc8 = 0xff;
				CRC8 = Convert2ByteASCIIToData8(Cmdbuff +11);
				Crc8 = Generate_crc8_Code(Cmdbuff,11);
				
				if (CRC8 == Crc8)
				{
					int32_t EncVal = Convert8ByteASCIIToData32(Cmdbuff+3);
					SetENXValueAsPulse(EncVal);
				}
			}
			break;
		case SL_CMD_SETHW_PLS:	// Cài tọa độ Handwheel (theo xung)
			{
				unsigned char CRC8 = 0xFF;
				unsigned char Crc8 = 0xff;
				CRC8 = Convert2ByteASCIIToData8(Cmdbuff +11);
				Crc8 = Generate_crc8_Code(Cmdbuff,11);
				
				if (CRC8 == Crc8)
				{
					int32_t HWVal = Convert8ByteASCIIToData32(Cmdbuff+3);
					SetHWValueAsPulse(HWVal);
				}
			}
			break;
		case SL_CMD_TNOFF_ENC: 	// Tắt Encoder x
			{
				unsigned char CRC8 = 0xFF;
				unsigned char Crc8 = 0xff;
				CRC8 = Convert2ByteASCIIToData8(Cmdbuff +3);
				Crc8 = Generate_crc8_Code(Cmdbuff,3);
				
				if (CRC8 == Crc8)
				{
					DisableEncoderX();
				}
			}
			break;
		case SL_CMD_TNOFF_HW:		// Tắt handwheel
			{
				unsigned char CRC8 = 0xFF;
				unsigned char Crc8 = 0xff;
				CRC8 = Convert2ByteASCIIToData8(Cmdbuff +3);
				Crc8 = Generate_crc8_Code(Cmdbuff,3);
				
				if (CRC8 == Crc8)
				{
					DisableHandwheel();
				}
			}
			
			break;
		case SL_CMD_SET_OUTPUT:	// Cài Output
			{
				unsigned char CRC8 = 0xFF;
				unsigned char crc8 = 0xff;
				CRC8 = Convert2ByteASCIIToData8(Cmdbuff +7);
				crc8 = Generate_crc8_Code(Cmdbuff,7);
				if (CRC8 == crc8)
				{
					unsigned char Index = Convert2ByteASCIIToData8(Cmdbuff + 3);
					unsigned char Value = Convert2ByteASCIIToData8(Cmdbuff + 5);
					
					Value  &= 0x01;
					if (Index == 0xFF)
					{
						SetAllOutput(Value);
					}
					else
						SetOutput(Index, Value);
				}
			}
			break;
		case SL_CMD_TNON_ENC:		// Bật Encoder x
			{
				unsigned char CRC8 = 0xFF;
				unsigned char Crc8 = 0xff;
				CRC8 = Convert2ByteASCIIToData8(Cmdbuff +3);
				Crc8 = Generate_crc8_Code(Cmdbuff,3);
				
				if (CRC8 == Crc8)
				{
					DisableHandwheel(); // Tắt handwheel trước
					EnableEncoderX();
				}
			}
			
			break;
		case SL_CMD_TNON_HW:		// Bật handwheel
			{
				unsigned char CRC8 = 0xFF;
				unsigned char Crc8 = 0xff;
				CRC8 = Convert2ByteASCIIToData8(Cmdbuff +3);
				Crc8 = Generate_crc8_Code(Cmdbuff,3);
				
				if (CRC8 == Crc8)
				{
					DisableEncoderX(); // Tắt encoder X trước
					EnableHandwheel();
				}
			}
			
			break;
		case SL_CMD_RESET_IC:		// Reset chip
			{
				unsigned char CRC8 = 0xFF;
				unsigned char Crc8 = 0xff;
				CRC8 = Convert2ByteASCIIToData8(Cmdbuff +3);
				Crc8 = Generate_crc8_Code(Cmdbuff,3);
				
				if (CRC8 == Crc8)
				{
					NVIC_SystemReset();
					// Reset chip here
				}
			}
			break;
		case SL_CMD_TOGGLE_ENHW:		// Đổi chiều đọc Encoder / Handwheel
		{
			unsigned char CRC8 = 0xFF;
			unsigned char Crc8 = 0xff;
			CRC8 = Convert2ByteASCIIToData8(Cmdbuff +3);
			Crc8 = Generate_crc8_Code(Cmdbuff,3);
			
			if (CRC8 == Crc8)
			{
				if (IsTogle) IsTogle = false;
				else IsTogle = true;
				INFLASH_Save_Config();
			}
		}
		break;
		default: break;
	}
}
//



/*
* Hàm chuyển char-hex sang char
* Ví dụ: 'F' -> 0x0F
*/
char Number1[] = {0,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09};
char Number2[] = {0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
char ConvertHexASCIIToChar(char asciihex)
{
	if ((asciihex >= 0x30 )&&(asciihex <= 0x39)) return Number1[asciihex - 0x30];
	else 
	if ((asciihex >= 0x41 )&&(asciihex <= 0x46)) return Number2[asciihex - 0x41];
	else
		return -1;
}


/*
* Convert2ByteASCIIToData8
* hàm này chuyển 2 byte char-hex thành 1 byte
* Ví dụ: {'3','4'} => 0x34
*/
unsigned char Convert2ByteASCIIToData8(char * DataIn)
{
	char Byte1 = ConvertHexASCIIToChar(*(DataIn));
	char Byte2 = ConvertHexASCIIToChar(*(DataIn+1));
	
	unsigned char res  = (Byte1<<4) + (Byte2&0x0F);
	return res;
}



/*
* Hàm chuyển 4byte char-hex thành 1 ushort 16bit
* Ví dụ: {'E','3','4','C'} => 58188 (decimal)
*/
unsigned short Convert4ByteASCIIToData16(char* DataIn)
{
	char Byte1 = *(DataIn);
	char Byte2 = *(DataIn+1);
	char Byte3 = *(DataIn+2);
	char Byte4 = *(DataIn+3);
	Byte1 = ConvertHexASCIIToChar(Byte1);
	Byte2 = ConvertHexASCIIToChar(Byte2);
	Byte3 = ConvertHexASCIIToChar(Byte3);
	Byte4 = ConvertHexASCIIToChar(Byte4);

	unsigned short Result = 0;
	Result =((((((Result + Byte1)<<4)+Byte2)<<4)+Byte3)<<4) + Byte4;
	return Result;
}
//

/*
* hàm chuyển 8 byte char-hex thành 1 Int32bit
* Ví dụ: {'0','0','F','0','0','0','C','E'} = > 15728846 (decimal)
*/
int32_t Convert8ByteASCIIToData32(char* DataIn)
{
	char Byte[8] = {0};
	for (int i = 0; i<= 7; i++) Byte[i] = ConvertHexASCIIToChar(DataIn[i]);
	
	int32_t Result  = 0;
	for (int i = 0; i< 7; i++) Result = (Result + Byte[i])<<4;
	
	return Result + Byte[7];
}








/*
------------------CONSOLE PROCESS--------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------
*/


void Console_Process(void)
{
	char c;
	while ((c=ring_buffer_pop(&Console_Rx_buffer)) >0)
	{
		if (c == START_CODE) 
		{
			Console_Rx.buffer[0] = c; 
			Console_Rx.leng = 1;
		}
		else
		if (c == END_CODE)
		{
				Console_Rx.buffer[Console_Rx.leng] = c;
				Console_Rx.buffer[Console_Rx.leng+1] = 0; // Tạo ký tự kết thúc chuuỗi
				Console_Decode(&Console_Rx);
		}
		else
		{
				Console_Rx.buffer[Console_Rx.leng] = c;
				Console_Rx.leng++;
				
		}
		if (Console_Rx.leng > 31) Console_Rx.leng = 31;
	
	} // End while

} // End




