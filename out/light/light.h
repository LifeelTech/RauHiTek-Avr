/*
 * light.h
 *
 *  Created on: May 17, 2016
 *      Author: Phu Quach
 */

#ifndef RAUHITEK_AVR_LIGHT_LIGHT_H_
#define RAUHITEK_AVR_LIGHT_LIGHT_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "stdint.h"

extern void Light_Init (uint8_t DigitalPin);
extern uint8_t Light_Open (void);
extern uint8_t Ligt_Close (void);

#ifdef __cplusplus
}
#endif

#endif /* RAUHITEK_AVR_LIGHT_LIGHT_H_ */
