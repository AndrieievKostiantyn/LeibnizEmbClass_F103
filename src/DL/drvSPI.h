/*
 * drvSPI.h
 *
 *  Created on: 26.09.2017
 *  Author: kostiantyn_andreev
 */

#ifndef DRVSPI_H_
#define DRVSPI_H_

#include "stm32f10x.h"

void drvSPI_Init(void);
void drvSPI_SendByte(uint8_t dataTX);
void drvSPI_ReadByte(uint8_t *dataRX);

#endif /* DRVSPI_H_ */
