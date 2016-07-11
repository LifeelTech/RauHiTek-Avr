/*
 * light.h
 *
 *  Created on: May 17, 2016
 *      Author: Phu Quach
 */

#ifndef RAUHITEK_AVR_LIGHT_LIGHT_H_
#define RAUHITEK_AVR_LIGHT_LIGHT_H_

#include "stdint.h"
#include "std_types.h"

typedef StdDeviceType LightType;
typedef struct {
    uint8_t num;
    const LightType *lighChannel;
}LighConfigSetType;

#ifdef __cplusplus
extern "C"{
#endif

extern void Light_Init (const LighConfigSetType *cfgPtr);
extern uint8_t Light_Open (uint8_t channelId);
extern uint8_t Light_Close (uint8_t channelId);

#ifdef __cplusplus
}
#endif

#endif /* RAUHITEK_AVR_LIGHT_LIGHT_H_ */
