/*
 * thermistor.c
 *
 *  Created on: Apr 27, 2016
 *      Author: Phu Quach
 */

#include "thermistor.h"
#include <util/delay.h>
#include <Arduino.h>

/* resistance at 25 degrees C */
#define THERMISTOR_NOMINAL 		(10000U)
/* temp. for nominal resistance (almost always 25 C) */
#define TEMPERATURE_NOMINAL 	(25U)
/* how many samples to take and average, more takes longer  */
/* but is more 'smooth' */
#define NUM_SAMPLES 			(5U)
/* The beta coefficient of the thermistor (usually 3000-4000) */
#define BCOEFFICIENT 			(3950U)
/* the value of the 'other' resistor */
#define SERIES_RESISTOR 		(10000U)

/* Declare global variales */
static int32_t samples[NUM_SAMPLES];
static uint8_t TherAPin = 0U;
static uint8_t Ther_State = 0U;

void
Ther_Init (uint8_t AnalogPin)
{
	TherAPin = AnalogPin;
	pinMode(TherAPin, INPUT);
	Ther_State = 1U;
}

float
Ther_GetTempCelsius (void)
{
	uint8_t i;
	float average;
	float steinhart;
	float ret_val;
	if (Ther_State == 1U)
	{
		// take N samples in a row, with a slight delay
		for (i = 0; i < NUM_SAMPLES; i++)
		{
			samples[i] = analogRead(TherAPin);
			delay(10);
		}

		// average all the samples out
		average = 0;
		for (i = 0; i < NUM_SAMPLES; i++)
		{
			average += samples[i];
		}
		average /= NUM_SAMPLES;

		// convert the value to resistance
		average = 1023 / average - 1;
		average = SERIES_RESISTOR / average;

		steinhart = average / THERMISTOR_NOMINAL;     // (R/Ro)
		steinhart = log(steinhart);                  // ln(R/Ro)
		steinhart /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
		steinhart += 1.0 / (TEMPERATURE_NOMINAL + 273.15); // + (1/To)
		steinhart = 1.0 / steinhart;                 // Invert
		steinhart -= 273.15;                         // convert to C
		ret_val = steinhart;
	}
	else
	{
		ret_val = 0U;
	}
	return ret_val;
}
