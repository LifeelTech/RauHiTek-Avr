/*
 * man.h
 *
 *  Created on: May 30, 2016
 *      Author: Phu Quach
 */

#ifndef RAUHITEK_AVR_MANAGER_MAN_H_
#define RAUHITEK_AVR_MANAGER_MAN_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "stdint.h"
//#include "wireless.h"

typedef struct {
	uint8_t UnitId;
	uint8_t PinId;
}Man_DeviceType;

typedef Man_DeviceType Man_HumidityType;
typedef Man_DeviceType Man_MoistureType;
typedef Man_DeviceType Man_ThermistorType;
typedef Man_DeviceType Man_BrightnessType;
typedef Man_DeviceType Man_LightType;
typedef Man_DeviceType Man_ValveType;
typedef Man_DeviceType Man_OtherType;

typedef struct {
	uint8_t num;
	Man_HumidityType *humiPtr;
}Man_HumidityConfigSetType;

typedef struct {
	uint8_t num;
	Man_MoistureType *moisPtr;
}Man_MoistureConfigSetType;

typedef struct {
	uint8_t num;
	Man_ThermistorType *therPtr;
}Man_ThermistorConfigSetType;

typedef struct {
	uint8_t num;
	Man_BrightnessType *brigPtr;
}Man_BrightnessConfigSetType;

typedef struct {
	uint8_t num;
	Man_LightType *lighPtr;
}Man_LightConfigSetType;

typedef struct {
	uint8_t num;
	Man_ValveType *vavlPtr;
}Man_ValveConfigSetType;

typedef struct {
	uint8_t num;
	Man_OtherType *otherPtr;
}Man_OtherConfigSetType;

typedef struct {
	Man_MoistureConfigSetType *moisConfig;
	Man_ThermistorConfigSetType *therConfig;
	Man_BrightnessConfigSetType *brigConfig;
	Man_HumidityConfigSetType *humiConfig;
	Man_LightConfigSetType *lighConfig;
	Man_ValveConfigSetType *valvConfig;
	Man_OtherConfigSetType *otheConfig;
//	const Wifi_ConfigType *wifiConfig;
}Man_ConfigType;

extern void Man_Init (const Man_ConfigType* ConfigPtr);
extern void Man_Reset (void);

#ifdef __cplusplus
}
#endif

#endif /* RAUHITEK_AVR_MANAGER_MAN_H_ */
