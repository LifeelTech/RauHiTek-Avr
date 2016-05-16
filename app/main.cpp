/*
 * main.c
 *
 *  Created on: Apr 27, 2016
 *      Author: Phu Quach
 */


#include "stdlib.h"
#include <Arduino.h>
#include <util/delay.h>

#include "thermistor.h"
#include "brightness.h"
#include "moisture.h"
#include "valve.h"
#include "light.h"

/* List of used analog pins */
#define	THERMISTOR_PIN		A0
#define BRIGHTNESS_PIN		A1
#define MOISTURE_PIN		A2
#define VALVE_PIN			8
#define LIGHT_PIN			9

void initialization(void);
void loop(void);

int
main (void)
{
	/* Initialize port/pin */
	initialization();
#if defined(DEBUG_MODE)
	Serial.begin(9600);
	Serial.println("Initialized successful");
#endif
	while (1)
	{
		loop();
	}
	return 0;
}

void
initialization (void)
{
	init();
	pinMode(13, OUTPUT);
	Ther_Init(THERMISTOR_PIN);
	Bri_Init(BRIGHTNESS_PIN);
	Moi_Init(MOISTURE_PIN);
	Val_Init(VALVE_PIN);
	Light_Init(LIGHT_PIN);
}

void
loop (void)
{
	float TherCelsius, BrightValue, MoistureValue;

	TherCelsius = Ther_GetTempCelsius();
	if (TherCelsius >= 30 && TherCelsius <= 50)
	{
		digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
	}

	BrightValue = Bri_GetBrightValue();
	if (BrightValue <= 1000)
	{
		Light_Open();
	}

	MoistureValue = Moi_GetMoistureValue();
	if (MoistureValue < 300)
	{
#if defined(DEBUG_MODE)
		Serial.println("Open valve to supply more water.");
#endif
		Val_Open();
	}
	else
	{
#if defined(DEBUG_MODE)
		Serial.println("Enough water! Close valve.");
#endif
		Val_Close();
	}

	delay(1000);              // wait for a second
}

