/*
 * drvAccel.h
 *
 *  Created on: 17.01.2018
 *      Author: kostiantyn_andrieiev
 */

#ifndef DL_DRVACCEL_H_
#define DL_DRVACCEL_H_

#include "stm32f10x.h"

typedef struct {
	int16_t X;
	int16_t Y;
	int16_t Z;
}drvAccel_AccelVector_t;

typedef enum {
	drvAccel_OK,
	drvAccel_ERROR
}drvAccel_Message_t;

drvAccel_Message_t drvAccel_isAlive(void);
void drvAccel_Init(void);
void drvAccel_PowerOn(void);
void drvAccel_ReadAll(drvAccel_AccelVector_t *ptrVector);

#endif /* DL_DRVACCEL_H_ */
