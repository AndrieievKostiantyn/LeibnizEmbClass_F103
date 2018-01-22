/*
 *  drvSysClock.c
 *
 *  Created on: 10 November 2017
 *  Author: Kostiantyn Andrieiev
 */

#include "drvSysClock.h"

static volatile uint32_t currentTime = 0;

void drvSysClock_Init(void) {
	RCC_ClocksTypeDef rccClocks;
	RCC_GetClocksFreq(&rccClocks);
	SysTick_Config(rccClocks.HCLK_Frequency / 1000);
}

uint32_t drvSysClock_GetTime(void) {
	return currentTime;
}

uint8_t drvSysClock_isTimeSpent(uint32_t startTime, uint32_t delay) {
	uint8_t returnValue = 0;
	uint32_t spentTime = 0;

	spentTime = currentTime - startTime;

	if (spentTime >= delay) {
		returnValue = 1;
	} else {
		returnValue = 0;
	}

	return returnValue;
}

void drvSysClock_Run(void) {
	currentTime++;
}

