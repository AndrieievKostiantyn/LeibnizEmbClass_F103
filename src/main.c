/**
 ******************************************************************************
 * @file    main.c
 * @author  Ac6
 * @version V1.0
 * @date    01-December-2013
 * @brief   Default main function.
 ******************************************************************************
 */

#include "stm32f10x.h"
#include "DL/drvRCC.h"
#include "DL/drvSysClock.h"
#include "DL/drvIWDG.h"
#include "DL/drvGPIO.h"
#include "DL/drvSPI.h"
#include "DL/drvAccel.h"

static drvAccel_Message_t BL_AccStatus = drvAccel_ERROR;

void BSP_Init(void);

int main(void) {

	BSP_Init();

	uint8_t rx = 0;


	while (1) {
		BL_AccStatus = drvAccel_isAlive();
		drvAccel_ReadRegister(0x00, &rx);
	}
}

void BSP_Init(void) {
	drvRCC_Init();
	drvSysClock_Init();
	drvGPIO_Init();
	drvSPI_Init();
	drvAccel_Init();
}
