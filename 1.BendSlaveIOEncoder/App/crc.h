

#ifndef _CRC_H_

#define _CRC_H_

/* -- Sử dụng thuật toán: CRC-16/CCITT-FALSE --*/

/*
* Generate_crc16_Code
* Hàm này dùng tạo mã CRC16
*/
unsigned short Generate_crc16_Code(const char* data_p, unsigned char length);
unsigned char Generate_crc8_Code(const char *data, unsigned char len);

#endif

