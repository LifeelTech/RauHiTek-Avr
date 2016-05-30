/*
 * man.c
 *
 *  Created on: May 30, 2016
 *      Author: Phu Quach
 */

#include "man.h"

#include "Arduino.h"
#include "brightness.h"
#include "humidity.h"
#include "moisture.h"
#include "thermistor.h"
#include "valve.h"
#include "light.h"

static uint8_t Man_State = 0U;
static const Man_ConfigType *ManConfigSet;

void
Man_Init (const Man_ConfigType* ConfigPtr)
{
	volatile uint8_t i = 0U;
	if (Man_State == 1U)
	{
		return;
	}
	else
	{
		ManConfigSet = ConfigPtr;
		if (ConfigPtr->brigConfig != NULL)
		{
			for (i = 0; i < ConfigPtr->brigConfig->num; i++)
			{
				Bri_Init(ConfigPtr->brigConfig->brigPtr->PinId);
			}
		}

		if (ConfigPtr->humiConfig != NULL)
		{
			for (i = 0; i < ConfigPtr->humiConfig->num; i++)
			{
				Hum_Init(ConfigPtr->humiConfig->humiPtr->PinId);
			}
		}

		if (ConfigPtr->lighConfig != NULL)
		{
			for (i = 0; i < ConfigPtr->lighConfig->num; i++)
			{
				Light_Init(ConfigPtr->lighConfig->lighPtr->PinId);
			}
		}

		if (ConfigPtr->moisConfig != NULL)
		{
			for (i = 0; i < ConfigPtr->moisConfig->num; i++)
			{
				Moi_Init(ConfigPtr->moisConfig->moisPtr->PinId);
			}
		}

		if (ConfigPtr->valvConfig != NULL)
		{
			for (i = 0; i < ConfigPtr->valvConfig->num; i++)
			{
				Val_Init(ConfigPtr->valvConfig->vavlPtr->PinId);
			}
		}

		if (ConfigPtr->therConfig != NULL)
		{
			for (i = 0; i < ConfigPtr->therConfig->num; i++)
			{
				Ther_Init(ConfigPtr->therConfig->therPtr->PinId);
			}
		}

/*		if (ConfigPtr->wifiConfig != NULL)
		{
			Wifi_Init(ConfigPtr->wifiConfig);
		}*/
	}

	Man_State = 1U;
}

void
Man_Reset (void)
{
}
