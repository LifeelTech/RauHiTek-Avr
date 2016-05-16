/*
 * moisture.h
 *
 *  Created on: May 17, 2016
 *      Author: Phu Quach
 */

#ifndef RAUHITEK_AVR_MOISTURE_MOISTURE_H_
#define RAUHITEK_AVR_MOISTURE_MOISTURE_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "stdint.h"

extern void Moi_Init (uint8_t AnalogPin);
extern int32_t Moi_GetMoistureValue (void);

#ifdef __cplusplus
}
#endif

#endif /* RAUHITEK_AVR_MOISTURE_MOISTURE_H_ */
