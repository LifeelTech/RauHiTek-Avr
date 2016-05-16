/*
 * valve.h
 *
 *  Created on: May 12, 2016
 *      Author: Phu Quach
 */

#ifndef RAUHITEK_AVR_VALVE_VALVE_H_
#define RAUHITEK_AVR_VALVE_VALVE_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "stdint.h"

extern void Val_Init (uint8_t DigitalPin);
extern uint8_t Val_Open (void);
extern uint8_t Val_Close (void);

#ifdef __cplusplus
}
#endif

#endif /* RAUHITEK_AVR_VALVE_VALVE_H_ */
