/*
 * Man_Cfg.h
 *
 *  Created on: May 30, 2016
 *      Author: Phu Quach
 */

#ifndef RAUHITEK_AVR_APP_MAN_CFG_H_
#define RAUHITEK_AVR_APP_MAN_CFG_H_

#ifdef __cplusplus
extern "C"{
#endif

#include "man.h"
#include "Arduino.h"

Man_BrightnessType bricfg[1] = {
	{
		.UnitId = 1U,
		.PinId = A0
	},
};

Man_MoistureType moicfg[1] = {
	{
		.UnitId = 1U,
		.PinId = A1
	},
};

Man_ThermistorType thecfg[1] = {
	{
		.UnitId = 1U,
		.PinId = A2
	},
};

Man_BrightnessConfigSetType brigcfgset = {
	.num = 1,
	.brigPtr = &bricfg[0]
};

Man_MoistureConfigSetType moiscfgset= {
	.num = 1,
	.moisPtr = &moicfg[0]
};

Man_ThermistorConfigSetType thercfgset = {
	.num = 1,
	.therPtr = &thecfg[0]
};

Man_ConfigType ManCfgSet = {
	&moiscfgset,
	&thercfgset,
	&brigcfgset,
	NULL,
	NULL,
	NULL,
	NULL
};

#ifdef __cplusplus
}
#endif

#endif /* RAUHITEK_AVR_APP_MAN_CFG_H_ */
