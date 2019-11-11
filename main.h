/*
 * main.h
 *
 *  Created on: Apr 29, 2019
 *	  Author: SD
 */

#ifndef MAIN_H_

#define MAIN_H_
#include "Drivers/SD_UART.h"
#include "Drivers/SD_Delay.h"
#include "Drivers/SD_I2C.h"
#include "Drivers/SD_PIT.h"
#include "Drivers/SD_GPIO.h"
#include "Drivers/SD_I2C.h"
#include "Drivers/SD_TSI.h"
#include "os.h"
//#include "k60_i2c.h"
#include "common/common.h"

#define EEPROM_WRITE 0xAE
#define EEPROM_READ 0xAF
#define CCR_WRITE 0xDE
#define CCR_READ 0xDF
#define HR_FMT_12 0x80
#define PM 0x20
#define AM 0x00
#define RTC_ADD_START 0x30 
#define RTC_ADD_END  0x37


typedef struct __attribute__((packed)) {
	int8_t Y2K;
	int8_t DW;
	int8_t YR;
	int8_t MO;
	int8_t DT;
	int8_t HR;
	int8_t MN;
	int8_t SC;
}rtc_data;

signed char convert(signed char input);

#endif /* MAIN_H_ */
