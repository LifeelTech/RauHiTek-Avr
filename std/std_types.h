/*
 * std_types.h
 *
 *  Created on: Jun 25, 2016
 *      Author: Phu Quach
 */

#ifndef RAUHITEK_AVR_STD_STD_TYPES_H_
#define RAUHITEK_AVR_STD_STD_TYPES_H_

#include "stdint.h"

typedef struct {
    uint8_t UnitId;
    uint8_t PinId;
}StdDeviceType;

typedef enum {
    OK,
    NOT_OK
}StdReturnTypes;

typedef enum {
    UNINIT,
    INITIALIZED,
    BUSY
}StdDriverState;

#endif /* RAUHITEK_AVR_STD_STD_TYPES_H_ */
