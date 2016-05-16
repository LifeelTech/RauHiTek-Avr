/*
 * brightness.c
 *
 *  Created on: Apr 27, 2016
 *      Author: Phu Quach
 */

#include "brightness.h"
#include <Arduino.h>

#define LOG_RANGE	(5U)
#define RAW_RANGE	(1024)
float Bri_Raw2Lux(int32_t raw);

static uint8_t BriAPin = 0U;
static uint8_t Bri_State = 0U;

void
Bri_Init (uint8_t AnalogPin)
{
	BriAPin = AnalogPin;
	pinMode(BriAPin,INPUT);
	Bri_State = 1U;
}

float
Bri_GetBrightValue (void)
{
	float ret_value;
	if (Bri_State == 1U)
	{
		int32_t rawValue = analogRead(BriAPin);
		ret_value = Bri_Raw2Lux(rawValue);
	}
	else
	{
		ret_value = 0U;
	}
	return ret_value;
}

float
Bri_Raw2Lux (int32_t raw)
{
	float logLux = (raw * LOG_RANGE * 1.0) / RAW_RANGE;
	return pow(10, logLux);
}
