/*
 * valve.c
 *
 *  Created on: May 12, 2016
 *      Author: Phu Quach
 */
#include "Arduino.h"
#include "valve.h"

static uint8_t ValDPin = 0U;
static uint8_t Val_State = 0U;

void
Val_Init (uint8_t DigitalPin)
{
	ValDPin = DigitalPin;
	pinMode(ValDPin, OUTPUT);
	Val_State = 1U;
}

uint8_t
Val_Open (void)
{
	uint8_t ret_val;
	if (Val_State == 1U)
	{
		digitalWrite(ValDPin, HIGH);
		ret_val = 1U;
	}
	else
		ret_val = 0U;
	return ret_val;
}

uint8_t
Val_Close (void)
{
	uint8_t ret_val;
	if (Val_State == 1U)
	{
		digitalWrite(ValDPin, LOW);
		ret_val = 1U;
	}
	else
		ret_val = 0U;
	return ret_val;
}
