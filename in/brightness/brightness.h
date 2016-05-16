/*
 * brightness.h
 *
 *  Created on: Apr 27, 2016
 *      Author: Phu Quach
 */

#ifndef RAUHITEK_AVR_BRIGHTNESS_BRIGHTNESS_H_
#define RAUHITEK_AVR_BRIGHTNESS_BRIGHTNESS_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "stdint.h"

extern void Bri_Init (uint8_t AnalogPin);
extern float Bri_GetBrightValue (void);

#ifdef __cplusplus
}
#endif

#endif /* RAUHITEK_AVR_BRIGHTNESS_BRIGHTNESS_H_ */
