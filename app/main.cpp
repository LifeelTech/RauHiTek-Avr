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
#include "humidity.h"
#include "man_cfg.h"
//#include "wireless.h"

#include "man.h"

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
	Man_Init(&ManCfgSet);
}

void
loop (void)
{
	float TherCelsius, BrightValue, MoistureValue;

	TherCelsius = Ther_GetTempCelsius();
	Serial.print("Temperature = ");
	Serial.println(TherCelsius);
	if (TherCelsius >= 30 && TherCelsius <= 50)
	{
		digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
	}

	BrightValue = Bri_GetBrightValue();
	Serial.print("Brightness Value = ");
	Serial.println(BrightValue);
	if (BrightValue <= 1000)
	{
		Light_Open();
	}

	MoistureValue = Moi_GetMoistureValue();
	Serial.print("Moisture Value = ");
	Serial.println(MoistureValue);
	if (MoistureValue < 300)
	{
#if defined(DEBUG_MODE)
		//Serial.print("Open valve to supply more water.");
#endif
		Val_Open();
	}
	else
	{
#if defined(DEBUG_MODE)
		//Serial.println("Enough water! Close valve.");
#endif
		Val_Close();
	}
	Serial.println("#######################################");
	delay(1000);              // wait for a second
}

