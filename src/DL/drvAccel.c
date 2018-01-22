/*
 * drvAccel.c
 *
 *  Created on: 17.01.2018
 *      Author: kostiantyn_andrieiev
 */

#include "drvAccel.h"
#include "drvSPI.h"
#include "drvGPIO.h"

drvAccel_Message_t drvAccel_isAlive(void) {
	uint8_t accRX = 0;
	drvAccel_Message_t status = drvAccel_ERROR;

	drvAccel_ReadRegister(0x00, &accRX);

	if(accRX == 0xe5) {
		status = drvAccel_OK;
	} else {
		status = drvAccel_ERROR;
	}

	return status;
}

void drvAccel_Init(void) {
	drvAccel_WriteRegister(0x2D, 0x00); //Drive into Stand By Mode
	drvAccel_WriteRegister(0x31, 0x0B); //Set to 16g, full res
	drvAccel_WriteRegister(0x2C, 0x0A); //Set bandwidth to 100Hz
	drvAccel_WriteRegister(0x2D, 0x08); //Drive into measure mode
}

void drvAccel_PowerOn(void) {
	drvAccel_WriteRegister(0x2D, 0x08);
}

void drvAccel_WriteRegister(uint8_t regAddr, uint8_t data) {
	drvGPIO_ResetPin(drvGPIO_SPI_CS);

	drvSPI_SendByte(regAddr);
	drvSPI_SendByte(data);

	drvGPIO_SetPin(drvGPIO_SPI_CS);
}

void drvAccel_ReadRegister(uint8_t regAddr, uint8_t* retVal) {
	uint8_t readAddr = 0;
	uint8_t mask = 0x01;

	readAddr = (regAddr) | (mask << 7);

	drvGPIO_ResetPin(drvGPIO_SPI_CS);

	drvSPI_SendByte(readAddr);
	drvSPI_ReadByte(retVal);

	drvGPIO_SetPin(drvGPIO_SPI_CS);
}
