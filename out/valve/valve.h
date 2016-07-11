/*
 * valve.h
 *
 *  Created on: May 12, 2016
 *      Author: Phu Quach
 */

#ifndef RAUHITEK_AVR_VALVE_VALVE_H_
#define RAUHITEK_AVR_VALVE_VALVE_H_

#include "stdint.h"
#include "std_types.h"

typedef StdDeviceType ValveType;
typedef struct {
    uint8_t numofDrip;
    uint8_t numofSpray;
    const ValveType *valvDripChannel;
    const ValveType *valvSprayChannel;
}ValvConfigSetType;

#ifdef __cplusplus
extern "C"{
#endif

extern void Val_Init (const ValvConfigSetType *cfgPtr);
extern uint8_t ValDrip_Open (uint8_t channelId);
extern uint8_t ValDrip_Close (uint8_t channelId);
extern uint8_t ValSpray_Open (uint8_t channelId);
extern uint8_t ValSpray_Close (uint8_t channelId);

#ifdef __cplusplus
}
#endif

#endif /* RAUHITEK_AVR_VALVE_VALVE_H_ */
