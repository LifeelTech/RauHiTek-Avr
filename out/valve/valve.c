/*
 * valve.c
 *
 *  Created on: May 12, 2016
 *      Author: Phu Quach
 */
#include "Arduino.h"
#include "valve.h"

static const ValvConfigSetType* Val_ConfigPtr;
static uint8_t ValDripLastChannel = 0U;
static uint8_t ValSprayLastChannel = 0U;
static uint8_t Val_State = 0U;

void
Val_Init (const ValvConfigSetType *cfgPtr)
{
    uint8_t i = 0;
    if (cfgPtr != NULL)
    {
        Val_ConfigPtr = cfgPtr;
        for (; i < Val_ConfigPtr->numofDrip; i++)
        {
            pinMode(Val_ConfigPtr->valvDripChannel[i].PinId, OUTPUT);
        }
        ValDripLastChannel = i - 1;
        for (i = 0; i < Val_ConfigPtr->numofSpray; i++)
        {
            pinMode(Val_ConfigPtr->valvSprayChannel[i].PinId, OUTPUT);
        }
        ValSprayLastChannel = i - 1;
        Val_State = 1U;
    }
    else
    {
        return;
    }
    Val_State = 1U;
}

uint8_t
ValDrip_Open (uint8_t channelId)
{
    uint8_t ret_val;
    if (Val_State == 1U)
    {
        if (channelId <= ValDripLastChannel)
        {
            digitalWrite(Val_ConfigPtr->valvDripChannel[channelId].PinId, HIGH);
        }
        else
            ret_val = 0U;
        ret_val = 1U;
    }
    else
        ret_val = 0U;
    return ret_val;
}

uint8_t
ValDrip_Close (uint8_t channelId)
{
    uint8_t ret_val;
    if (Val_State == 1U)
    {
        if (channelId <= ValDripLastChannel)
        {
            digitalWrite(Val_ConfigPtr->valvDripChannel[channelId].PinId, LOW);
        }
        else
            ret_val = 0U;
        ret_val = 1U;
    }
    else
        ret_val = 0U;
    return ret_val;
}

uint8_t
ValSpray_Open (uint8_t channelId)
{
    uint8_t ret_val;
    if (Val_State == 1U)
    {
        if (channelId <= ValSprayLastChannel)
        {
            digitalWrite(Val_ConfigPtr->valvSprayChannel[channelId].PinId, HIGH);
        }
        else
            ret_val = 0U;
        ret_val = 1U;
    }
    else
        ret_val = 0U;
    return ret_val;
}

uint8_t
ValSpray_Close (uint8_t channelId)
{
    uint8_t ret_val;
    if (Val_State == 1U)
    {
        if (channelId <= ValSprayLastChannel)
        {
            digitalWrite(Val_ConfigPtr->valvSprayChannel[channelId].PinId, LOW);
        }
        else
            ret_val = 0U;
        ret_val = 1U;
    }
    else
        ret_val = 0U;
    return ret_val;
}
