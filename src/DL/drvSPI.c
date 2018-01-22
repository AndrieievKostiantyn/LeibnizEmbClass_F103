/*
 * drvSPI.c
 *
 *  Created on: 26.09.2017
 *      Author: kostiantyn_andreev
 */

#include "drvSPI.h"
#include "drvGPIO.h"
#include <string.h>

static uint16_t rxValue = 0;

void drvSPI_Init(void) {
	SPI_InitTypeDef drvSPI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

	NVIC_InitStruct.NVIC_IRQChannel = SPI1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	NVIC_EnableIRQ(SPI1_IRQn);

	SPI_I2S_DeInit(SPI1);
	drvSPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	drvSPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	drvSPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
	drvSPI_InitStruct.SPI_CPOL = SPI_CPOL_High;
	drvSPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;
	drvSPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
	drvSPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
	drvSPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	drvSPI_InitStruct.SPI_CRCPolynomial = 7;

	SPI_Init(SPI1, &drvSPI_InitStruct);
	SPI_Cmd(SPI1, ENABLE);

	//SPI_NSSInternalSoftwareConfig(SPI1, SPI_NSSInternalSoft_Set);
	SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_RXNE, ENABLE);
}

void drvSPI_SendByte(uint8_t dataTX) {
	SPI_I2S_SendData(SPI1, dataTX);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
}

void drvSPI_ReadByte(uint8_t *dataRX) {
	drvSPI_SendByte(0x00);
	*dataRX = rxValue;
}

void SPI1_IRQHandler(void) {
	if(SPI_I2S_GetITStatus(SPI1, SPI_I2S_IT_RXNE) == SET) {
		SPI_I2S_ClearITPendingBit(SPI1, SPI_I2S_IT_RXNE);
		rxValue = SPI_I2S_ReceiveData(SPI1);
	}
}
