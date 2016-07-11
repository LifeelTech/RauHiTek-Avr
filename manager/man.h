/*
 * man.h
 *
 *  Created on: May 30, 2016
 *      Author: Phu Quach
 */

#ifndef RAUHITEK_AVR_MANAGER_MAN_H_
#define RAUHITEK_AVR_MANAGER_MAN_H_

#include "Arduino.h"
#include "stdint.h"
#include "std_types.h"
#include "brightness.h"
#include "humidity.h"
#include "moisture.h"
#include "thermistor.h"
#include "valve.h"
#include "light.h"

#define MAX_ELEMENTS    2U
#define MAX_FLOOR       5U

//typedef MoistureType *MoisGroupDefType[MAX_ELEMENTS];
//typedef ThermistorType *TherGroupDefType[MAX_ELEMENTS];
//typedef BrightnessType *BrigGroupDefType[MAX_ELEMENTS];
//typedef HumidityType *HumiGroupDefType[MAX_ELEMENTS];
//typedef LightType *LighGroupDefType[MAX_ELEMENTS];
//typedef ValveType *ValDripGroupDefType[MAX_ELEMENTS];
//typedef ValveType *ValSprayGroupDefType[MAX_ELEMENTS];
typedef struct {
    uint8_t FloorId;
//    MoisGroupDefType moisPtr;
//    TherGroupDefType therPtr;
//    BrigGroupDefType brigPtr;
//    HumiGroupDefType humiPtr;
//    LighGroupDefType lighPtr;
//    ValDripGroupDefType dripPtr;
//    ValSprayGroupDefType spraPtr;
    const uint8_t *MoisChannelList;
    const uint8_t *TherChannelList;
    const uint8_t *BrigChannelList;
//    uint8_t HumiChannelList[MAX_ELEMENTS];
    const uint8_t *LighChannelList;
    const uint8_t *DripChannelList;
    const uint8_t *SpraChannelList;
    uint8_t NumofMois;
    uint8_t NumofTher;
    uint8_t NumofBrig;
    //uint8_t NumofHumi;
    uint8_t NumofLigh;
    uint8_t NumofDrip;
    uint8_t NumofSpra;
}Man_FloorConfigSetType;

typedef struct {
    const MoisConfigSetType *moisConfig;
    const TherConfigSetType *therConfig;
    const BrigConfigSetType *brigConfig;
//    const HumiConfigSetType *humiConfig;
    const LighConfigSetType *lighConfig;
    const ValvConfigSetType *valveConfig;
    const Man_FloorConfigSetType *floorConfig;
    uint8_t NumofFloor;
}Man_ConfigType;


#ifdef __cplusplus
extern "C"{
#endif
extern void Man_Init (void);
extern void Man_Reset (uint8_t FloorId);
extern void Man_Poll_Plant (void);
extern uint8_t Man_ChangeAuto (boolean val);
extern uint8_t Man_ConfigAmoutFloor (uint8_t amount);
extern void Man_ConfigActualGlobalTime (uint32_t ElapsedTimeinSecond);
extern void Man_TimerHandler (void);
#ifdef __cplusplus
}
#endif

#endif /* RAUHITEK_AVR_MANAGER_MAN_H_ */
