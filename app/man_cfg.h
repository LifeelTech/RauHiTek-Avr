/*
 * Man_Cfg.h
 *
 *  Created on: May 30, 2016
 *      Author: Phu Quach
 */

#ifndef RAUHITEK_AVR_APP_MAN_CFG_H_
#define RAUHITEK_AVR_APP_MAN_CFG_H_

#include "man.h"
#include "Arduino.h"

#define NUMBER_OF_SOURCE    (5U)

const BrightnessType bricfg[1] = {
     {
          .UnitId = 0U,
          .PinId = 14U
     }/*,
     {
          .UnitId = 1U,
          .PinId = 14U
     },
     {
          .UnitId = 2U,
          .PinId = 14U
     },*/
};

const MoistureType moicfg[2] = {
     {
         .UnitId = 0U,
         .PinId = 15U
     },
     {
             .UnitId = 1U,
             .PinId = 15U
     }/*,
     {
             .UnitId = 2U,
             .PinId = 15U
     },
     {
             .UnitId = 3U,
             .PinId = 15U
     },
     {
             .UnitId = 4U,
             .PinId = 15U
     },
     {
             .UnitId = 5U,
             .PinId = 15U
     },*/
};

const ThermistorType thecfg[1] = {
     {
             .UnitId = 0U,
          .PinId = 16U
     }/*,
     {
             .UnitId = 1U,
          .PinId = 16U
     },
     {
             .UnitId = 2U,
          .PinId = 16U
     },*/
};

const ValveType dripcfg[1] = {
     {
             .UnitId = 0U,
             .PinId = 9U
     }/*,
     {
             .UnitId = 1U,
             .PinId = 9U
     },
     {
             .UnitId = 2U,
             .PinId = 9U
     },*/
};

const ValveType spraycfg[1] = {
     {
             .UnitId = 0U,
             .PinId = 10U
     }/*,
     {
             .UnitId = 1U,
             .PinId = 10U
     },
     {
             .UnitId = 2U,
             .PinId = 10U
     },*/
};

const LightType lighcfg[1] = {
     {
             .UnitId = 0U,
          .PinId = 11U
     }/*,
     {
             .UnitId = 1U,
          .PinId = 11U
     },
     {
             .UnitId = 2U,
          .PinId = 11U
     },*/
};

const BrigConfigSetType brigcfgset = {
     .num = 1U,
     .brigChannel = &bricfg[0U]
};

const MoisConfigSetType moiscfgset= {
     .num = 1U,
     .moisChannel = &moicfg[0U]
};

const TherConfigSetType thercfgset = {
     .num = 1U,
     .therChannel = &thecfg[0U]
};

const ValvConfigSetType valvecfgset = {
        .numofDrip = 1U,
     .numofSpray = 1U,
     .valvDripChannel = &dripcfg[0],
     .valvSprayChannel = &spraycfg[0]
};

const LighConfigSetType lighcfgset = {
     .num = 1U,
     .lighChannel = &lighcfg[0]
};

const uint8_t moisList_Floor1[2] = {
    0U, 1U
};
/*
const uint8_t moisList_Floor2[2] = {
    2U, 3U
};
const uint8_t moisList_Floor3[2] = {
    4U, 5U
};
*/

const uint8_t therList_Floor1[1] = {
    0U
};
/*
const uint8_t therList_Floor2[1] = {
    1U
};
const uint8_t therList_Floor3[1] = {
    2U
};
*/

const uint8_t brigList_Floor1[1] = {
    0U
};
/*const uint8_t brigList_Floor2[1] = {
    1U
};
const uint8_t brigList_Floor3[1] = {
    2U
};*/

const uint8_t lighList_Floor1[1] = {
    0U
};
/*const uint8_t lighList_Floor2[1] = {
    1U
};
const uint8_t lighList_Floor3[1] = {
    2
};*/

const uint8_t dripList_Floor1[1] = {
    0U
};
/*const uint8_t dripList_Floor2[1] = {
    1U
};
const uint8_t dripList_Floor3[1] = {
    2
};*/

const uint8_t spraList_Floor1[1] = {
    0U
};
/*
const uint8_t spraList_Floor2[1] = {
    1U
};
const uint8_t spraList_Floor3[1] = {
    2
};
*/

const Man_FloorConfigSetType floorcfgset[1] = {
     {
          .FloorId = 0U,
          .MoisChannelList = &moisList_Floor1[0],
          .TherChannelList = &therList_Floor1[0],
          .BrigChannelList = &brigList_Floor1[0],
          .LighChannelList = &lighList_Floor1[0],
          .DripChannelList = &dripList_Floor1[0],
          .SpraChannelList = &spraList_Floor1[0],
          .NumofMois = 2U,
          .NumofTher = 1U,
          .NumofBrig = 1U,
//          0U,
          .NumofLigh = 1U,
          .NumofDrip = 1U,
          .NumofSpra = 1U
     }/*,
     {
             .FloorId = 1U,
             .MoisChannelList = &moisList_Floor2[0],
             .TherChannelList = &therList_Floor2[0],
             .BrigChannelList = &brigList_Floor2[0],
             .LighChannelList = &lighList_Floor2[0],
             .DripChannelList = &dripList_Floor2[0],
             .SpraChannelList = &spraList_Floor2[0],
             .NumofMois = 2U,
             .NumofTher = 1U,
             .NumofBrig = 1U,
   //          0U,
             .NumofLigh = 1U,
             .NumofDrip = 1U,
             .NumofSpra = 1U
     },
     {
             .FloorId = 2U,
             .MoisChannelList = &moisList_Floor3[0],
             .TherChannelList = &therList_Floor3[0],
             .BrigChannelList = &brigList_Floor3[0],
             .LighChannelList = &lighList_Floor3[0],
             .DripChannelList = &dripList_Floor3[0],
             .SpraChannelList = &spraList_Floor3[0],
             .NumofMois = 2U,
             .NumofTher = 1U,
             .NumofBrig = 1U,
   //          0U,
             .NumofLigh = 1U,
             .NumofDrip = 1U,
             .NumofSpra = 1U
     },*/
};

const Man_ConfigType ManCfgSet = {
     .moisConfig = &moiscfgset,
     .therConfig = &thercfgset,
     .brigConfig = &brigcfgset,
     .lighConfig = &lighcfgset,
     .valveConfig = &valvecfgset,
     .floorConfig = &floorcfgset[0],
     .NumofFloor = 1U
};

#endif /* RAUHITEK_AVR_APP_MAN_CFG_H_ */
