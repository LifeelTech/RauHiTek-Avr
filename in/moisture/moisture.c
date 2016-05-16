/*
 * moisture.c
 *
 *  Created on: May 17, 2016
 *      Author: Phu Quach
 */

#include "moisture.h"
#include <Arduino.h>

static uint8_t MoiAPin = 0U;
static uint8_t Moi_State = 0U;

void
Moi_Init (uint8_t AnalogPin)
{
	MoiAPin = AnalogPin;
	pinMode(MoiAPin, INPUT);
	Moi_State = 1U;
}

int32_t
Moi_GetMoistureValue (void)
{
	int32_t ret_val;
	if (Moi_State == 1U)
	{
		ret_val = analogRead(MoiAPin);
	}
	else
		ret_val = 0U;
	return ret_val;
}
