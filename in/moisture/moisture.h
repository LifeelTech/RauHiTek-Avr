/*
 * moisture.h
 *
 *  Created on: May 17, 2016
 *      Author: Phu Quach
 */

#ifndef RAUHITEK_AVR_MOISTURE_MOISTURE_H_
#define RAUHITEK_AVR_MOISTURE_MOISTURE_H_

#include "stdint.h"
#include "std_types.h"

typedef StdDeviceType MoistureType;
typedef struct {
    uint8_t num;
    const MoistureType *moisChannel;
}MoisConfigSetType;

#ifdef __cplusplus
extern "C"{
#endif


extern void Moi_Init (const MoisConfigSetType *cfgPtr);
extern int32_t Moi_GetMoistureValue (uint8_t channelId);

#ifdef __cplusplus
}
#endif

#endif /* RAUHITEK_AVR_MOISTURE_MOISTURE_H_ */
