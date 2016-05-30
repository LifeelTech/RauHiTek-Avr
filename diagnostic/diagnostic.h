/*
 * diagnostic.h
 *
 *  Created on: May 30, 2016
 *      Author: Phu Quach
 */

#ifndef RAUHITEK_AVR_DIAGNOSTIC_DIAGNOSTIC_H_
#define RAUHITEK_AVR_DIAGNOSTIC_DIAGNOSTIC_H_

#include "stdint.h"

extern void Diag_Init ();
extern void Diag_CheckError ();
extern uint8_t Diag_ReportError ();
extern uint8_t Diag_RecordEvent ();

#endif /* RAUHITEK_AVR_DIAGNOSTIC_DIAGNOSTIC_H_ */
