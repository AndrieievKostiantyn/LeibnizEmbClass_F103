/*
 *  drvIWDG.c
 *
 *  Created on: 11 December 2017
 *  Author: Kostiantyn Andrieiev
 */

/*
 * Driver to work with the independent watchdog timer (IWDG).
 * It must be run in while(1) loop of the main.c
 * If the value of the IWDG was not reset by MCU,
 * hardware reset should be performed.
 *
 * */

#include "drvIWDG.h"

/**
 * @brief	Initializes the IWDG timer.
 */
void drvIWDG_Init(void) {
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_32);
	IWDG_SetReload(500);

	IWDG_ReloadCounter();
	IWDG_Enable();
}

/**
 * @brief	Resets the value of the IWDG.
 * @note	In while(1) loop to be called.
 */
void drvIWDG_Run(void) {
	IWDG_ReloadCounter();
}
