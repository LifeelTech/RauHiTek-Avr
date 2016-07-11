/*
 * main.c
 *
 *  Created on: Apr 27, 2016
 *      Author: Phu Quach
 */

#include "stdlib.h"
#include <Arduino.h>
#include <util/delay.h>
#include "TimerOne.h"

#include "thermistor.h"
#include "brightness.h"
#include "moisture.h"
#include "valve.h"
#include "light.h"
#include "humidity.h"
#include "wireless.h"

#include "man.h"

static uint32_t RxFlag = 0U;
static uint16_t RxSourceId = 0U;
static uint8_t RxCommand = 0U;
void Wifi_RxHandler(uint16_t SourceId, uint8_t Command);

static const Wifi_ConfigType wificfgset =
{
     2U,
     3U,
     "RauSachHiTek",
     "0123456@mnbvc",
     false,
     "80",
     &Wifi_RxHandler,
     BAUDRATE_9600
};

SoftwareSerial esp8266(wificfgset.WifiRxPin, wificfgset.WifiTxPin);

void initialization(void);
void loop(void);

void
Wifi_RxHandler(uint16_t SourceId, uint8_t Command)
{
    RxFlag = 1U;
    RxCommand = Command;
    RxSourceId = SourceId;
}

void
TIMER1_IRQHandler (void)
{
    Man_TimerHandler();
}

int
main (void)
{
    /* Initialize port/pin */
    initialization();
    while (1)
    {
        loop();
    }
    return 0;
}

void
initialization (void)
{
    init();
#if defined(DEBUG_MODE)
    Serial.begin(9600);
    Serial.println("Initialized successful");
#endif
    Timer1.initialize(10000000);
    Timer1.attachInterrupt(TIMER1_IRQHandler);
    pinMode(13, OUTPUT);
    pinMode(8, OUTPUT);
    Man_Init();
    delay(2000);
    digitalWrite(8, HIGH);
    esp8266.begin(9600);
    Wifi_Init(&esp8266, &wificfgset);
}

void
loop (void)
{
    Man_Poll_Plant();
#if defined(DEBUG_MODE)
    Serial.println("#######################################");
#endif
    Wifi_MainFunction_Receive();
    digitalWrite(13, LOW);
    delay(1000);              // wait for a second
}

