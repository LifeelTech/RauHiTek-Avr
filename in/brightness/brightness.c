/*
 * brightness.c
 *
 *  Created on: Apr 27, 2016
 *      Author: Phu Quach
 */

#include "brightness.h"
#include <Arduino.h>
#include "diagnostic.h"

#define LOG_RANGE    (5U)
#define RAW_RANGE    (1024)
float Bri_Raw2Lux(int32_t raw);

static uint8_t BriLastChannel = 0U;
static uint8_t Bri_State = 0U;
static const BrigConfigSetType *Bri_ConfigPtr;
void
Bri_Init (const BrigConfigSetType *cfgPtr)
{
    uint8_t i = 0;
    if (cfgPtr != NULL)
    {
        Bri_ConfigPtr = cfgPtr;
        for (; i < Bri_ConfigPtr->num; i++)
        {
            pinMode(Bri_ConfigPtr->brigChannel[i].PinId, INPUT);
        }
        BriLastChannel = i - 1;
        Bri_State = 1U;
    }
    else
    {
        return;
    }
}

float
Bri_GetBrightValue (uint8_t channelId)
{
    float ret_value;
    if (Bri_State == 1U)
    {
        if (channelId > BriLastChannel)
            ret_value = 0U;
        else
        {
            int32_t rawValue = analogRead(Bri_ConfigPtr->brigChannel[channelId].PinId);
            ret_value = Bri_Raw2Lux(rawValue);
            if (ret_value > 35000)
            {
                Diag_ReportError(Bri_ConfigPtr->brigChannel[channelId].PinId, HARDWARE_FAILED);
            }
        }
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
