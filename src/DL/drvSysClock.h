/*
 * drvSysClock.h
 *
 *  Created on: 12 Apr 2016
 *      Author: kostiantyn_andreev
 */

#ifndef DRVSYSCLOCK_H_
#define DRVSYSCLOCK_H_

#include "stm32f10x.h"

void drvSysClock_Init(void);
void drvSysClock_Run(void);
uint32_t drvSysClock_GetTime(void);
uint8_t drvSysClock_isTimeSpent(uint32_t startTime, uint32_t delay);


#endif /* DRVSYSCLOCK_H_ */
