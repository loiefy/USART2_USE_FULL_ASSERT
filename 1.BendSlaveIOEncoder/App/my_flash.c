#include "my_flash.h"
#include "stdio.h"
#include "stm32f10x_flash.h"
#include "stdbool.h"

extern bool IsTogle;

// đối với stm32f103xx medium destiny thì Page size = 1Kbyte

FLASH_Status MyFlashStt;	// biến xác định trạng thái ghi/đọc Flash



unsigned short INFLASH_ReadShort(unsigned int Address)
{
    return *((unsigned short *) Address);
}
//

void INFLASH_ReadConfig(void)		// Read the Configuration from Flash
{
	unsigned short Tem = INFLASH_ReadShort(FLASH_APP_START+FLASH_IS_TOG_ENHW);
	if ((uint16_t)Tem == 0xFFFF)
		IsTogle = 0;
	if (Tem > 0) IsTogle = true; else IsTogle = false;
}
//




void INFLASH_Save_Config(void)		/* Hàm lưu các cài đặt vào Flash */
{	
	FLASH_Unlock();	
	FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);

	MyFlashStt = FLASH_ErasePage(FLASH_APP_START);	// xóa Page 1
	if (MyFlashStt != FLASH_COMPLETE) // có lỗi gì đó xảy ra
	{
			switch (MyFlashStt)
			{
				case FLASH_BUSY:
						//printf("\r\nFlash Err Busy");
						break;
				case FLASH_ERROR_PG:
						//printf("\r\nFlash Err PG");
						break;
				case FLASH_ERROR_WRP:
						//printf("\r\nFlash Err write Protect");
						break;
				case FLASH_TIMEOUT:
						//printf("\r\nFlash Err time out");
						break;
				default: break;
			}
	}
	else
	{
		FLASH_ProgramHalfWord(FLASH_APP_START + FLASH_IS_TOG_ENHW, IsTogle);	
	}
	FLASH_Lock();
	
}
//

