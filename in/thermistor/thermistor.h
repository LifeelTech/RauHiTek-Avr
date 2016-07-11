/*
 * thermistor.h
 *
 *  Created on: Apr 27, 2016
 *      Author: Phu Quach
 */

#ifndef RAUHITEK_AVR_THERMISTOR_THERMISTOR_H_
#define RAUHITEK_AVR_THERMISTOR_THERMISTOR_H_

#include "stdint.h"
#include "std_types.h"

typedef StdDeviceType ThermistorType;
typedef struct {
    uint8_t num;
    const ThermistorType *therChannel;
}TherConfigSetType;

#ifdef __cplusplus
extern "C"{
#endif

/* Declare external service */
extern void Ther_Init (const TherConfigSetType *cfgPtr);
extern float Ther_GetTempCelsius (uint8_t channelId);

#ifdef __cplusplus
}
#endif

#endif /* RAUHITEK_AVR_THERMISTOR_THERMISTOR_H_ */
