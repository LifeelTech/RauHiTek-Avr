/*
 * diagnostic.h
 *
 *  Created on: May 30, 2016
 *      Author: Phu Quach
 */

#ifndef RAUHITEK_AVR_DIAGNOSTIC_DIAGNOSTIC_H_
#define RAUHITEK_AVR_DIAGNOSTIC_DIAGNOSTIC_H_

#include "stdint.h"
#include "Arduino.h"
#include "WString.h"

#define NUMBER_OF_ELEMENTS  (20U)
#define NUMBER_OF_SOURCE    (5U)
typedef enum
{
    HARDWARE_FAILED,
    HARDWARE_UNDETECTED,
    MEASURED_TEMP_COLD,
    MEASURED_TEMP_HOT,
    MEASURED_MOIS_DROUGHT,
    MEASURED_MOIS_FLOOD,
    MEASURED_LIGHT_LESS,
    MEASURED_LIGHT_BRIGHT
}Diag_ErrorValueType;

typedef struct
{
    uint32_t Id;
    uint32_t atTime;
    Diag_ErrorValueType ErrorId;
}Diag_ErrorType;

#ifdef __cplusplus
extern "C"{
#endif

extern void Diag_Init (void);
extern void Diag_ReportError (uint16_t SourceId, Diag_ErrorValueType ErrorId);
//extern uint8_t Diag_GetErrorLog (uint16_t SourceId, String *LogBuf);
extern void Diag_Reset (uint16_t SourceId);

#ifdef __cplusplus
}
#endif

#endif /* RAUHITEK_AVR_DIAGNOSTIC_DIAGNOSTIC_H_ */
