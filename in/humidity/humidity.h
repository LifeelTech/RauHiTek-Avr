/*
 * humidity.h
 *
 *  Created on: Apr 27, 2016
 *      Author: Phu Quach
 */

#ifndef RAUHITEK_AVR_HUMIDITY_HUMIDITY_H_
#define RAUHITEK_AVR_HUMIDITY_HUMIDITY_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "stdint.h"

extern void Hum_Init (uint8_t AnalogPin);
extern float Hum_GetHumidityValue (uint8_t AnalogPin);

#ifdef __cplusplus
}
#endif

#endif /* RAUHITEK_AVR_HUMIDITY_HUMIDITY_H_ */
