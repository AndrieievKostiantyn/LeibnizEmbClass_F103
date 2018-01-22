/*
 * drvAccel.h
 *
 *  Created on: 17.01.2018
 *      Author: kostiantyn_andrieiev
 */

#ifndef DL_DRVACCEL_H_
#define DL_DRVACCEL_H_

#include "stm32f10x.h"

typedef enum {
	drvAccel_OK,
	drvAccel_ERROR
}drvAccel_Message_t;


void drvAccel_WriteRegister(uint8_t regAddr, uint8_t data);
void drvAccel_ReadRegister(uint8_t regAddr, uint8_t* retVal);

drvAccel_Message_t drvAccel_isAlive(void);
void drvAccel_Init(void);
void drvAccel_PowerOn(void);
void drvAccel_Init(void);

#endif /* DL_DRVACCEL_H_ */
