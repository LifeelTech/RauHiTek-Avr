/*
 * diagnostic.cpp
 *
 *  Created on: May 30, 2016
 *      Author: Phu Quach
 */

#include "diagnostic.h"
//#include "man_cfg.h"

extern uint32_t LifeTimeinSecond;
Diag_ErrorType DiagEventList[NUMBER_OF_SOURCE][NUMBER_OF_ELEMENTS];
static uint32_t DiagEventCurrentIndex[NUMBER_OF_SOURCE] = {0};
static uint8_t Diag_State = 0U;

void
Diag_Init (void)
{
    for (uint16_t i = 0; i < NUMBER_OF_SOURCE; i++)
    {
        DiagEventCurrentIndex[i] = (uint32_t)&DiagEventList[0];
    }
    Diag_State = 1U;
}

void
Diag_ReportError (uint16_t SourceId, Diag_ErrorValueType ErrorId)
{
    Diag_ErrorType *EventTemp;
    EventTemp = (Diag_ErrorType *)DiagEventCurrentIndex[SourceId];
    EventTemp->ErrorId = ErrorId;
    EventTemp->atTime = LifeTimeinSecond;
    EventTemp->Id = (EventTemp--)->Id+1;
    if (DiagEventCurrentIndex[SourceId] == (uint32_t)&DiagEventList[SourceId][NUMBER_OF_ELEMENTS-1])
    {
        DiagEventCurrentIndex[SourceId] = (uint32_t)&DiagEventList[SourceId][0];
    }
}

/*
uint8_t
Diag_GetErrorLog (uint16_t SourceId, String *LogBuf)
{
    Diag_ErrorType *EventTemp = &DiagEventList[SourceId];
    for (uint32_t i; i < NUMBER_OF_ELEMENTS; i+=sizeof(Diag_ErrorType), EventTemp++)
    {
        uint8_t *getChar = (uint8_t *)EventTemp;
        for (uint32_t j = 0; j < sizeof(Diag_ErrorType); j++, getChar++)
        {
            *LogBuf += (char)(*getChar & 0xF);
        }
    }
    return 1;
}
*/
