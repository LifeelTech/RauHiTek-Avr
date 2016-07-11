/*
 * Wireless.c
 *
 *  Created on: May 29, 2016
 *      Author: Phu Quach
 */

#include "wireless.h"
#include "diagnostic.h"

#define NUMBER_OF_DIAG_CHARS    (3000U)
static uint8_t Wifi_State = 0U;
static uint8_t EnabledMultipleConnection = 0U;
static const Wifi_ConfigType *WifiConfigPtr;
static SoftwareSerial *esp8266;
String Wifi_SendCm (String cm, const uint32_t timeout);
String Wifi_SendData(String cm, const uint32_t timeout);
void Wifi_SendHTTPResponse (uint32_t connectionId, String content);
void Wifi_SendCIPData(uint32_t connectionId, String data);

void
Wifi_Init (SoftwareSerial *CurAccess, const Wifi_ConfigType *ConfigPtr)
{
    String initCm;
    if (Wifi_State == 1U)
    {
        return;
    }
    else
    {
        esp8266 = CurAccess;
        WifiConfigPtr = ConfigPtr;
        Wifi_SendCm("AT+RST\r\n", 2000); // reset module
        Wifi_SendCm("AT+CWMODE=2\r\n", 1000); // configure as access point
        initCm = "AT+CWSAP=\"" + WifiConfigPtr->WifiSSID + "\",\"" + WifiConfigPtr->WifiPassword + "\"" + ",5,3\r\n";
        Wifi_SendCm(initCm, 3000);
        delay(5000);
        Wifi_SendCm("AT+CIFSR\r\n", 1000); // get ip address
        initCm = "AT+CIPSERVER=1," + WifiConfigPtr->WifiPort + "\r\n";
        Wifi_SendCm("AT+CIPMUX=0\r\n", 1000); // configure for multiple connections
        Wifi_SendCm(initCm, 1000); // turn on server on port 80

#if defined(DEBUG_MODE)
        Serial.println("Server Ready");
#endif
    }
}
void
Wifi_DeInit (void)
{
    Wifi_State = 0U;
    // make close command
    String closeCommand = "AT+CIPCLOSE\r\n";
    //closeCommand+=connectionId; // append connection id
    //closeCommand+="\r\n";

    Wifi_SendCm(closeCommand, 1000); // close connection
}

void
Wifi_MainFunction_Receive (void)
{
    uint16_t SourceId;
    uint8_t Command;
    if(esp8266->available()) // check if the esp is sending a message
    {
        if(esp8266->find("+IPD,"))
        {
            delay(1000); // wait for the serial buffer to fill up (read all the serial data)
            // get the connection id so that we can then disconnect
            //int connectionId = esp8266->read()-48; /* subtract 48 because the read() function returns
                                                    // the ASCII decimal value and 0 (the first decimal number) starts at 48

            if (esp8266->find("isFst="))
            {

            }
            else
            {

            }

            SourceId = (esp8266->read()) << 8;
            SourceId += (esp8266->read());

            Command = esp8266->read() - 48;

            WifiConfigPtr->WifiReceiveData(SourceId, Command);
            // build string that is send back to device that is requesting pin toggle
            String content = "Rsp=OK";
            Wifi_SendHTTPResponse(0, content);

        }
    }
}

uint8_t
Wifi_SendEventLog (uint16_t SourceId)
{
    uint8_t RetVal = 0U;
    if (Wifi_State == 1U)
    {
        String WifiDiagLog;
        //Diag_GetErrorLog(SourceId, &WifiDiagLog);
        Wifi_SendHTTPResponse(0U, WifiDiagLog);
        RetVal = 1U;
    }
    return RetVal;
}

uint8_t
Wifi_SendSystemData (String Data)
{
    uint8_t RetVal = 0U;
    if (Wifi_State == 1U)
    {
        Wifi_SendHTTPResponse(0U, Data);
        RetVal = 1U;
    }
    return RetVal;
}

String
Wifi_SendCm (String cm, const uint32_t timeout)
{
    String response = "";
    int32_t time;
    esp8266->print(cm);

    time = millis();
    while ((time + timeout) > millis())
    {
        while (esp8266->available())
        {
            char c = esp8266->read();
            response += c;
        }
    }
#if defined(DEBUG_MODE)
    Serial.println(response);
#endif
    return response;
}

String
Wifi_SendData(String cm, const uint32_t timeout)
{
    String response = "";

    uint32_t dataSize = cm.length();
    char data[dataSize];
    cm.toCharArray(data, dataSize);

    esp8266->write(data, dataSize); // send the read character to the esp8266
#if defined(DEBUG_MODE)
    Serial.println("\r\n====== HTTP Response From Arduino ======");
    Serial.write(data,dataSize);
    Serial.println("\r\n========================================");
#endif

    long int time = millis();

    while ((time + timeout) > millis())
    {
        while (esp8266->available())
        {
            // The esp has data so display its output to the serial window
            char c = esp8266->read(); // read the next character.
            response += c;
        }
    }

#if defined(DEBUG_MODE)
    Serial.print(response);
#endif

    return response;
}

void
Wifi_SendHTTPResponse (uint32_t connectionId, String content)
{
    // build HTTP response
    String httpResponse;
    String httpHeader;
    // HTTP Header
    httpHeader = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n";
    httpHeader += "Content-Length: ";
    httpHeader += content.length();
    httpHeader += "\r\n";
    httpHeader +="Connection: close\r\n\r\n";
    httpResponse = httpHeader + content + " "; // There is a bug in this code: the last character of "content" is not sent, I cheated by adding this extra space
    Wifi_SendCIPData(connectionId, httpResponse);
}

void
Wifi_SendCIPData(uint32_t connectionId, String data)
{
    String cipSend = "AT+CIPSEND=";
    cipSend += connectionId;
    cipSend += ",";
    cipSend += data.length();
    cipSend += "\r\n";
    Wifi_SendCm(cipSend, 1000);
    Wifi_SendData(data, 1000);
}
