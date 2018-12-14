#ifndef __MY_FLASH_H
#define __MY_FLASH_H

#include <stm32f10x.h> 

#define bool char
#define TRUE 1
#define FALSE 0
#define NULL 0


// bộ nhớ Flash = 64Kbyte với stm32f103c8t6, địa chỉ cuối cùng sẽ là 0x08010000
// Chương trình chỉ hơn 30Kbyte 1 chút, nên dùng 59Kbyte lưu chương trình, còn lại để lưu dữ liệu

#define FLASH_APP_START			0x0800EC00

// Pagesize = 1Kbyte đối  với stm32f103xx medium destiny

#define FLASH_IS_TOG_ENHW	0


/* Các hàm đọc ghi cài đặt thông thường */
void INFLASH_ReadConfig(void);
void INFLASH_Save_Config(void);


#endif
//


