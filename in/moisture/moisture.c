/*
 * moisture.c
 *
 *  Created on: May 17, 2016
 *      Author: Phu Quach
 */

#include "moisture.h"
#include <Arduino.h>
#include "diagnostic.h"

static uint8_t Moi_State = 0U;
static const MoisConfigSetType* Moi_ConfigPtr;
static uint8_t MoiLastChannel = 0U;
void
Moi_Init (const MoisConfigSetType *cfgPtr)
{
    uint8_t i = 0;
    if (cfgPtr != NULL)
    {
        Moi_ConfigPtr = cfgPtr;
        for (; i < Moi_ConfigPtr->num; i++)
        {
            pinMode(Moi_ConfigPtr->moisChannel[i].PinId, INPUT);
        }
        MoiLastChannel = i - 1;
        Moi_State = 1U;
    }
    else
    {
        return;
    }
}

int32_t
Moi_GetMoistureValue (uint8_t channelId)
{
    int32_t ret_val;
    if (Moi_State == 1U)
    {
        if (channelId <= MoiLastChannel)
        {
            ret_val = analogRead(Moi_ConfigPtr->moisChannel[channelId].PinId);
            if (ret_val == 0 || ret_val > 950)
            {
                Diag_ReportError(Moi_ConfigPtr->moisChannel[channelId].PinId, HARDWARE_FAILED);
            }
        }
        else
            ret_val = 0U;
    }
    else
        ret_val = 0U;
    return ret_val;
}
