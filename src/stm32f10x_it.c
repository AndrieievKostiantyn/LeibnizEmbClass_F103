/*
 * stm32f4_it.c
 *
 *  Created on: 10 November 2017
 *  Author: Kostiantyn Andrieiev
 */

#include "stm32f1xx_it.h"
#include "DL/drvSysClock.h"

void SysTick_Handler(void) {
	drvSysClock_Run();
}
