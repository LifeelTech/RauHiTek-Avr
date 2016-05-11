/*
 * main.c
 *
 *  Created on: Apr 27, 2016
 *      Author: Phu Quach
 */


#include "stdlib.h"
#include <Arduino.h>
#include <util/delay.h>

#include "thermistor.h"
#include "brightness.h"
#include "humidity.h"
#include "HardwareSerial.h"

/* List of used analog pins */
#define	THERMISTOR_PIN		A0
#define LIGHT_PIN			A1
#define HUMIDITY_PIN		A2

void initialization(void);
void loop(void);

int
main (void)
{
	/* Initialize port/pin */
	initialization();
#if defined(DEBUG_MODE)
	HardwareSerial Serial(&rx_buffer1, &UBRR1H, &UBRR1L, &UCSR1A, &UCSR1B, &UDR1, RXEN1, TXEN1, RXCIE1, UDRE1, U2X1);
	Serial.begin(9600);
	Serial.println("Initialized successful");
#endif
	while (1)
	{
		loop();
	}
	return 0;
}

void
initialization (void)
{
	pinMode(13, OUTPUT);
	pinMode(THERMISTOR_PIN, INPUT);
}

void
loop (void)
{
	float TherCelsius, BrightValue;
	TherCelsius = Ther_GetTempCelsius(THERMISTOR_PIN);
	if (TherCelsius >= 30 && TherCelsius <= 50)
		digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
	BrightValue = Bri_GetBrightValue(LIGHT_PIN);
	if (BrightValue <= 1000)
		digitalWrite(13, HIGH);
	delay(1000);              // wait for a second
}

