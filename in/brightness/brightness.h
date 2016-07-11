/*
 * brightness.h
 *
 *  Created on: Apr 27, 2016
 *      Author: Phu Quach
 */

#ifndef RAUHITEK_AVR_BRIGHTNESS_BRIGHTNESS_H_
#define RAUHITEK_AVR_BRIGHTNESS_BRIGHTNESS_H_

#include "stdint.h"
#include "std_types.h"

typedef StdDeviceType BrightnessType;
typedef struct {
    uint8_t num;
    const BrightnessType *brigChannel;
}BrigConfigSetType;

#ifdef __cplusplus
extern "C"{
#endif

extern void Bri_Init (const BrigConfigSetType* cfgPtr);
extern float Bri_GetBrightValue (uint8_t channelId);

#ifdef __cplusplus
}
#endif

#endif /* RAUHITEK_AVR_BRIGHTNESS_BRIGHTNESS_H_ */
