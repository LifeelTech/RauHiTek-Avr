/*
 * Wireless.c
 *
 *  Created on: May 29, 2016
 *      Author: Phu Quach
 */

#include "wireless.h"

static uint8_t Wifi_State = 0U;
static uint8_t Wifi_RxPin;
static uint8_t Wifi_TxPin;
static uint8_t EnabledMultipleConnection = 0U;

void
Wifi_Init (const Wifi_ConfigType *ConfigPtr)
{
	if (Wifi_State == 1U)
	{
		return;
	}
	else
	{

	}
}
void
Wifi_DeInit (void)
{

}
void
Wifi_Send (char* TxBuffer)
{

}
void
Wifi_MainFunction_Receive (void)
{

}
