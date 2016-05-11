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

float
Bri_GetBrightValue (uint8_t AnalogPin)
{
	int32_t rawValue = analogRead(AnalogPin);

	return Bri_Raw2Lux(rawValue);
}

float
Bri_Raw2Lux (int32_t raw)
{
	float logLux = (raw * LOG_RANGE * 1.0) / RAW_RANGE;
	return pow(10, logLux);
}
