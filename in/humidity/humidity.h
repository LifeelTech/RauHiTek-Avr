/*
 * humidity.h
 *
 *  Created on: Apr 27, 2016
 *      Author: Phu Quach
 */

#ifndef RAUHITEK_AVR_HUMIDITY_HUMIDITY_H_
#define RAUHITEK_AVR_HUMIDITY_HUMIDITY_H_

#include "stdint.h"
#include "std_types.h"

typedef StdDeviceType HumidityType;
typedef struct {
    uint8_t num;
    const HumidityType *humiChannel;
}HumiConfigSetType;

#ifdef __cplusplus
extern "C"{
#endif

extern void Hum_Init (const HumiConfigSetType *cfgPtr);
extern float Hum_GetHumidityValue (uint8_t channelId);

#ifdef __cplusplus
}
#endif

#endif /* RAUHITEK_AVR_HUMIDITY_HUMIDITY_H_ */
