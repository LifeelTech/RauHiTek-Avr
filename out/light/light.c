/*
 * light.c
 *
 *  Created on: May 17, 2016
 *      Author: Phu Quach
 */

#include "light.h"
#include "Arduino.h"

static uint8_t LigDPin = 0U;
static uint8_t Light_State = 0U;

void
Light_Init (uint8_t DigitalPin)
{
	LigDPin = DigitalPin;
	pinMode(LigDPin, OUTPUT);
	Light_State = 1U;
}

uint8_t
Light_Open (void)
{
	uint8_t ret_val;
	if (Light_State == 1U)
	{
		digitalWrite(LigDPin, HIGH);
		ret_val = 1U;
	}
	else
		ret_val = 0U;
	return ret_val;
}

uint8_t
Light_Close (void)
{
	uint8_t ret_val;
	if (Light_State == 1U)
	{
		digitalWrite(LigDPin, LOW);
		ret_val = 1U;
	}
	else
		ret_val = 0U;
	return ret_val;
}
