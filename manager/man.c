/*
 * man.c
 *
 *  Created on: May 30, 2016
 *      Author: Phu Quach
 */

#include "man.h"
#include "eeprom.h"
#include "diagnostic.h"
#include "man_cfg.h"

#define EEPROM_ADD_SECOND           (0U)
#define EEPROM_ADD_FLOOR            (1U)
#define EEPROM_ADD_AUTO_PLANT       (2U)
#define MAX_DEVICE_TYPE             (10U)
#define MAX_ELEMENT                 (20U)

#define ORDER_MOIS                  (0U)
#define ORDER_TEMP                  (1U)
#define ORDER_BRIGHT                (2U)
#define ORDER_HUMI                  (3U)
#define HOUR2SECOND                 (60U*60U)

enum {
    LIGHT_OFF,
    LIGHT_ON,
    LIGHT_UNSPECIFIED
}Man_LightLevel;

static uint8_t Man_State = 0U;
//static const Man_ConfigType *ManConfigSet;
static uint8_t isInitialized = 0U;
static uint8_t NumofFloor = 0U;
static uint8_t AutoPlant = 0U;
static int32_t MesuredData[MAX_DEVICE_TYPE][MAX_ELEMENT];
uint32_t LifeTimeinSecond = 0;
static uint32_t StartLightTime = 0;
static uint8_t FlagLightSwitch = LIGHT_ON;
static boolean StartedLightTime = true;
static int32_t ResiDualTime = 0;

void
Man_Init (void)
{
    if (Man_State == 1U)
    {
        return;
    }
    else
    {
        isInitialized = eeprom_read_byte((uint8_t *)EEPROM_ADD_SECOND);
        if (isInitialized == 0U)
        {
            eeprom_write_byte((uint8_t *)EEPROM_ADD_SECOND, 0x01U);
            eeprom_busy_wait();
            if (eeprom_read_byte((uint8_t *)EEPROM_ADD_SECOND) != 0x01U)
                return;
            eeprom_write_byte((uint8_t *)EEPROM_ADD_FLOOR, 0x01U);
            eeprom_busy_wait();
            if (eeprom_read_byte((uint8_t *)EEPROM_ADD_FLOOR) != 0x01U)
                return;
            eeprom_write_byte((uint8_t *)EEPROM_ADD_AUTO_PLANT, 0x01U);
            eeprom_busy_wait();
            if (eeprom_read_byte((uint8_t *)EEPROM_ADD_AUTO_PLANT) != 0x01U)
                return;
        }
        NumofFloor = eeprom_read_byte((uint8_t *)EEPROM_ADD_FLOOR);
        AutoPlant = eeprom_read_byte((uint8_t *)EEPROM_ADD_AUTO_PLANT);

        //ManCfgSet = cfgPtr;
        if (ManCfgSet.brigConfig != NULL)
        {
            Bri_Init(ManCfgSet.brigConfig);
        }

/*
        if (ManConfigSet->humiConfig != NULL)
        {
            Hum_Init(ManConfigSet->humiConfig);
        }
*/

        if (ManCfgSet.lighConfig != NULL)
        {
            Light_Init(ManCfgSet.lighConfig);
        }

        if (ManCfgSet.moisConfig != NULL)
        {
            Moi_Init(ManCfgSet.moisConfig);
        }

        if (ManCfgSet.valveConfig != NULL)
        {
            Val_Init(ManCfgSet.valveConfig);
        }

        if (ManCfgSet.therConfig != NULL)
        {
            Ther_Init(ManCfgSet.therConfig);
        }
    }

    Man_State = 1U;
}

void
Man_Poll_Plant (void)
{
    float MeasuredValue;
    uint8_t f, i, j;
    if (AutoPlant == 1U)
    {
        for (f = 0; f < NumofFloor; f++)
        {
            for (i = 0; i < ManCfgSet.floorConfig[f].NumofTher; i++)
            {
                MeasuredValue = Ther_GetTempCelsius(ManCfgSet.therConfig->therChannel[ManCfgSet.floorConfig[f].TherChannelList[i]].UnitId);
                if (MeasuredValue > 40)
                {
                    Diag_ReportError(ManCfgSet.therConfig->therChannel[ManCfgSet.floorConfig[f].TherChannelList[i]].PinId, MEASURED_TEMP_HOT);
                }
                else if (MeasuredValue < 20)
                {
                    Diag_ReportError(ManCfgSet.therConfig->therChannel[ManCfgSet.floorConfig[f].TherChannelList[i]].PinId, MEASURED_TEMP_COLD);
                }
                else if (MeasuredValue > 35)
                {
                    if (AutoPlant == 0x01U)
                    {
                        for (j = 0; j < ManCfgSet.floorConfig[f].NumofSpra; j++)
                        {
                            ValSpray_Open(ManCfgSet.valveConfig->valvSprayChannel[ManCfgSet.floorConfig[f].SpraChannelList[j]].UnitId);
                        }
                    }
                }
                else if (MeasuredValue < 25)
                {
                    if (AutoPlant == 0x01U)
                    {
                        for (j = 0; j < ManCfgSet.floorConfig[f].NumofSpra; j++)
                        {
                            ValSpray_Open(ManCfgSet.valveConfig->valvSprayChannel[ManCfgSet.floorConfig[f].SpraChannelList[j]].UnitId);
                        }
                    }
                }
                MesuredData[ORDER_TEMP][ManCfgSet.floorConfig[f].TherChannelList[i]] = (int8_t)MeasuredValue;
/*
#if defined(DEBUG_MODE)
                Serial.print("Temperature of Thermal Sensor ");
                Serial.print(i);
                Serial.print(" = ");
                Serial.print(MeasuredValue);
                Serial.print(" oC");
#endif
*/
            }

            for (i = 0; i < ManCfgSet.floorConfig[f].NumofMois; i++)
            {
                MeasuredValue = Moi_GetMoistureValue(ManCfgSet.moisConfig->moisChannel[ManCfgSet.floorConfig[f].MoisChannelList[i]].UnitId);
                if (MeasuredValue > 600)
                {
                    Diag_ReportError(ManCfgSet.moisConfig->moisChannel[ManCfgSet.floorConfig[f].MoisChannelList[i]].PinId, MEASURED_MOIS_FLOOD);
                }
                else if (MeasuredValue < 300)
                {
                    Diag_ReportError(ManCfgSet.moisConfig->moisChannel[ManCfgSet.floorConfig[f].MoisChannelList[i]].PinId, MEASURED_MOIS_DROUGHT);
                }
                else if (MeasuredValue > 550)
                {
                    if (AutoPlant == 0x01U)
                    {
                        for (j = 0; j < ManCfgSet.floorConfig[f].NumofDrip; j++)
                        {
                            ValDrip_Close(ManCfgSet.valveConfig->valvDripChannel[ManCfgSet.floorConfig[f].DripChannelList[j]].UnitId);
                        }
                    }
                }
                else if (MeasuredValue < 350)
                {
                    if (AutoPlant == 0x01U)
                    {
                        for (j = 0; j < ManCfgSet.floorConfig[f].NumofDrip; j++)
                        {
                            ValDrip_Open(ManCfgSet.valveConfig->valvDripChannel[ManCfgSet.floorConfig[f].DripChannelList[j]].UnitId);
                        }
                    }
                }
                MesuredData[ORDER_MOIS][ManCfgSet.floorConfig[f].MoisChannelList[i]] = (int8_t)MeasuredValue;
/*
#if defined(DEBUG_MODE)
                Serial.print("Soil moisture of Moisture Sensor ");
                Serial.print(i);
                Serial.print(" = ");
                Serial.print(MeasuredValue);
#endif
*/
            }
            if (FlagLightSwitch == LIGHT_ON)
            {
                for (i = 0; i < ManCfgSet.floorConfig[f].NumofLigh; i++)
                {
                    Light_Open(ManCfgSet.lighConfig->lighChannel[ManCfgSet.floorConfig[f].LighChannelList[i]].UnitId);
                    StartedLightTime = true;
                    FlagLightSwitch = LIGHT_UNSPECIFIED;
                }
            }
            if (FlagLightSwitch == LIGHT_OFF)
            {
                for (i = 0; i < ManCfgSet.floorConfig[f].NumofLigh; i++)
                {
                    Light_Close(ManCfgSet.lighConfig->lighChannel[ManCfgSet.floorConfig[f].LighChannelList[i]].UnitId);
                    StartedLightTime = false;
                    FlagLightSwitch = LIGHT_UNSPECIFIED;
                }
            }
            for (i = 0; i < ManCfgSet.floorConfig[f].NumofBrig; i++)
            {
                MeasuredValue = Bri_GetBrightValue(ManCfgSet.brigConfig->brigChannel[ManCfgSet.floorConfig[f].BrigChannelList[i]].UnitId);
                if (MeasuredValue > 50000)
                {
                    Diag_ReportError(ManCfgSet.brigConfig->brigChannel[ManCfgSet.floorConfig[f].BrigChannelList[i]].PinId, MEASURED_LIGHT_BRIGHT);
                }
                else if (MeasuredValue < 15000 && StartedLightTime == true)
                {
                    Diag_ReportError(ManCfgSet.brigConfig->brigChannel[ManCfgSet.floorConfig[f].BrigChannelList[i]].PinId, MEASURED_LIGHT_LESS);
                }
                MesuredData[ORDER_BRIGHT][ManCfgSet.floorConfig[f].BrigChannelList[i]] = (int8_t)MeasuredValue;
/*
#if defined(DEBUG_MODE)
                Serial.print("Brightness of Light Sensor ");
                Serial.print(i);
                Serial.print(" = ");
                Serial.print(MeasuredValue);
                Serial.print(" Lx");
#endif
*/
            }
        }
    }
}


uint8_t
Man_ChangeAuto (boolean val)
{
    uint8_t retval = OK;
    if (val == true)
    {
        eeprom_write_byte((uint8_t *)EEPROM_ADD_AUTO_PLANT, 0x01U);
        eeprom_busy_wait();
        if (eeprom_read_byte((uint8_t *)EEPROM_ADD_AUTO_PLANT) != 0x01U)
            retval = NOT_OK;
    }
    else
    {
        eeprom_write_byte((uint8_t *)EEPROM_ADD_AUTO_PLANT, 0x00U);
        eeprom_busy_wait();
        if (eeprom_read_byte((uint8_t *)EEPROM_ADD_AUTO_PLANT) != 0x00U)
            retval = NOT_OK;
    }
    return retval;
}

uint8_t
Man_ConfigAmoutFloor (uint8_t amount)
{
    uint8_t retval = OK;
    eeprom_write_byte((uint8_t *)EEPROM_ADD_FLOOR, amount);
    eeprom_busy_wait();
    if (eeprom_read_byte((uint8_t *)EEPROM_ADD_FLOOR) != amount)
        retval = NOT_OK;
    return retval;
}

void
Man_Reset (uint8_t FloorId)
{
}

void
Man_ConfigActualGlobalTime (uint32_t ElapsedTimeinSecond)
{
    ResiDualTime = ElapsedTimeinSecond - 21600U;
}

void
Man_TimerHandler (void)
{
    LifeTimeinSecond++;
    if (ResiDualTime < 11U * HOUR2SECOND)
    {
        StartLightTime += ResiDualTime;
    }
    else
    {
        StartLightTime += (18U * HOUR2SECOND - ResiDualTime);
    }
    if (LifeTimeinSecond == StartLightTime || StartLightTime == 0)
    {
        FlagLightSwitch = LIGHT_ON;
    }
    if ((LifeTimeinSecond - StartLightTime) == 11U * HOUR2SECOND) /* Limited light time 11 Hours */
    {
        FlagLightSwitch = LIGHT_OFF;
        StartLightTime = LifeTimeinSecond + 13U * HOUR2SECOND; /* Take 1 day */
    }
}
