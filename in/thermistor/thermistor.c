/*
 * thermistor.c
 *
 *  Created on: Apr 27, 2016
 *      Author: Phu Quach
 */

#include "thermistor.h"
#include <util/delay.h>
#include <Arduino.h>
#include "diagnostic.h"

/* resistance at 25 degrees C */
#define THERMISTOR_NOMINAL      (3300U)
/* temp. for nominal resistance (almost always 25 C) */
#define TEMPERATURE_NOMINAL     (25U)
/* how many samples to take and average, more takes longer  */
/* but is more 'smooth' */
#define NUM_SAMPLES             (5U)
/* The beta coefficient of the thermistor (usually 3000-4000) */
#define BCOEFFICIENT            (3950U)
/* the value of the 'other' resistor */
#define SERIES_RESISTOR         (10000U)

/* Declare global variales */
static int32_t samples[NUM_SAMPLES];
static const TherConfigSetType* The_ConfigPtr;
static uint8_t TheLastChannel = 0U;
static uint8_t Ther_State = 0U;

void
Ther_Init (const TherConfigSetType *cfgPtr)
{
    uint8_t i = 0;
    if (cfgPtr != NULL)
    {
        The_ConfigPtr = cfgPtr;
        for (; i < The_ConfigPtr->num; i++)
        {
            pinMode(The_ConfigPtr->therChannel[i].PinId, INPUT);
        }
        TheLastChannel = i - 1;
        Ther_State = 1U;
    }
    else
    {
        return;
    }
    Ther_State = 1U;
}

float
Ther_GetTempCelsius (uint8_t channelId)
{
    uint8_t i;
    float average, steinhart, ret_val;
    if (Ther_State == 1U)
    {
        if (channelId <= TheLastChannel)
        {
            // take N samples in a row, with a slight delay
            for (i = 0; i < NUM_SAMPLES; i++)
            {
                samples[i] = analogRead(The_ConfigPtr->therChannel[channelId].PinId);
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
            if (ret_val < 5 || ret_val > 80)
            {
                Diag_ReportError(The_ConfigPtr->therChannel[channelId].PinId, HARDWARE_FAILED);
            }
        }
        else
            ret_val = 0U;
    }
    else
    {
        ret_val = 0U;
    }
    return ret_val;
}
