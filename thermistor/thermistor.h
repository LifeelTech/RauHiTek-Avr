/*
 * thermistor.h
 *
 *  Created on: Apr 27, 2016
 *      Author: Phu Quach
 */

#ifndef RAUHITEK_AVR_THERMISTOR_THERMISTOR_H_
#define RAUHITEK_AVR_THERMISTOR_THERMISTOR_H_

#include "stdint.h"

/* Declare external service */
extern float Ther_GetTempCelsius (uint8_t AnalogPin);

#endif /* RAUHITEK_AVR_THERMISTOR_THERMISTOR_H_ */
