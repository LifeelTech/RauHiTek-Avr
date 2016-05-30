/*
 * wireless.h
 *
 *  Created on: May 29, 2016
 *      Author: Phu Quach
 */

#ifndef RAUHITEK_AVR_COM_WIRELESS_WIRELESS_H_
#define RAUHITEK_AVR_COM_WIRELESS_WIRELESS_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "stdint.h"
#include "SoftwareSerial.h"
#include "Arduino.h"

typedef enum {
	BAUDRATE_9600 = 9600U,
	BAUDRATE_19200 = 19200U,
	BAUDRATE_38400 = 38400U,
	BAUDRATE_74880 = 74880U,
	BAUDRATE_115200 = 115200U,
	BAUDRATE_23040 = 230400U,
	BAUDRATE_460800 = 460800U,
	BAUDRATE_921600 = 921600U
}Wifi_BaudrateType;

typedef struct
{
	uint8_t WifiRxPin;
	uint8_t WifiTxPin;
	char* WifiSSID;
	char* WifiPassword;
	boolean WifiEnableMultipleConnection;
	uint32_t WifiPort;
	void (*WifiReceiveData) (char* RxBuffer);
	Wifi_BaudrateType WifiSerialBaudrate;
}Wifi_ConfigType;

extern void Wifi_Init (const Wifi_ConfigType *ConfigPtr);
extern void Wifi_DeInit (void);
extern void Wifi_Send (char* TxBuffer);
extern void Wifi_MainFunction_Receive (void);

#ifdef __cplusplus
}
#endif

#endif /* RAUHITEK_AVR_COM_WIRELESS_WIRELESS_H_ */
