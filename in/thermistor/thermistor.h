/*
 * thermistor.h
 *
 *  Created on: Apr 27, 2016
 *      Author: Phu Quach
 */

#ifndef RAUHITEK_AVR_THERMISTOR_THERMISTOR_H_
#define RAUHITEK_AVR_THERMISTOR_THERMISTOR_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "stdint.h"

/* Declare external service */
extern void Ther_Init (uint8_t AnalogPin);
extern float Ther_GetTempCelsius (void);

#ifdef __cplusplus
}
#endif

#endif /* RAUHITEK_AVR_THERMISTOR_THERMISTOR_H_ */
