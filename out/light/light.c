/*
 * light.c
 *
 *  Created on: May 17, 2016
 *      Author: Phu Quach
 */

#include "light.h"
#include "Arduino.h"

static const LighConfigSetType* Lig_ConfigPtr;
static uint8_t LigLastChannel = 0U;
static uint8_t Light_State = 0U;

void
Light_Init (const LighConfigSetType *cfgPtr)
{
    uint8_t i = 0;
    if (cfgPtr != NULL)
    {
        Lig_ConfigPtr = cfgPtr;
        for (; i < Lig_ConfigPtr->num; i++)
        {
            pinMode(Lig_ConfigPtr->lighChannel[i].PinId, OUTPUT);
        }
        LigLastChannel = i - 1;
        Light_State = 1U;
    }
    else
    {
        return;
    }
    Light_State = 1U;
}

uint8_t
Light_Open (uint8_t channelId)
{
    uint8_t ret_val;
    if (Light_State == 1U)
    {
        if (channelId <= LigLastChannel)
        {
            digitalWrite(Lig_ConfigPtr->lighChannel[channelId].PinId, HIGH);
            ret_val = 1U;
        }
        else
            ret_val = 0U;
    }
    else
        ret_val = 0U;
    return ret_val;
}

uint8_t
Light_Close (uint8_t channelId)
{
    uint8_t ret_val;
    if (Light_State == 1U)
    {
        if (channelId <= LigLastChannel)
        {
            digitalWrite(Lig_ConfigPtr->lighChannel[channelId].PinId, LOW);
            ret_val = 1U;
        }
        else
            ret_val = 0U;
    }
    else
        ret_val = 0U;
    return ret_val;
}
