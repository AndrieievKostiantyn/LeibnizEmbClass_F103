/*
 *  drvGPIO.c
 *
 *  Created on: 10 November 2017
 *  Author: Kostiantyn Andrieiev
 */

#include "drvGPIO.h"

typedef enum {
	PORT_A,
	PORT_B,
	PORT_C
} drvGPIO_PORT_t;

typedef struct {
	drvGPIO_PORT_t PORT;
	uint16_t PIN;
} drvGPIO_ConfigTable_t;

drvGPIO_ConfigTable_t drvGPIO_ConfigTable[drvGPIO_List_Amount]={
		{PORT_B, 0}
};

void drvGPIO_Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef GPIO_SPI_CS_InitStruct;
	GPIO_InitTypeDef spiGPIO_InitTypeDef;

	spiGPIO_InitTypeDef.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	spiGPIO_InitTypeDef.GPIO_Mode = GPIO_Mode_AF_PP;
	spiGPIO_InitTypeDef.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &spiGPIO_InitTypeDef);

	/* Init of the CS pin of the MCU Master (PB0) */
	GPIO_SPI_CS_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_SPI_CS_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_SPI_CS_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOB, &GPIO_SPI_CS_InitStruct);
	GPIO_SetBits(GPIOB, GPIO_Pin_0);
	/* !!! */
}

/**
 * @brief	Sets pin with name @pinName
 * @param	pinName
 */
void drvGPIO_SetPin(drvGPIO_List_t pinName) {
	switch (drvGPIO_ConfigTable[pinName].PORT) {
	case PORT_A:
		GPIO_SetBits(GPIOA, 1 << drvGPIO_ConfigTable[pinName].PIN);
		break;
	case PORT_B:
		GPIO_SetBits(GPIOB, 1 << drvGPIO_ConfigTable[pinName].PIN);
		break;
	case PORT_C:
		GPIO_SetBits(GPIOC, 1 << drvGPIO_ConfigTable[pinName].PIN);
		break;
	}
}

/**
 * @brief	Sets pin with name @pinName
 * @param	pinName
 */
void drvGPIO_ResetPin(drvGPIO_List_t pinName) {
	switch (drvGPIO_ConfigTable[pinName].PORT) {
		case PORT_A:
			GPIO_ResetBits(GPIOA, 1 << drvGPIO_ConfigTable[pinName].PIN);
			break;
		case PORT_B:
			GPIO_ResetBits(GPIOB, 1 << drvGPIO_ConfigTable[pinName].PIN);
			break;
		case PORT_C:
			GPIO_ResetBits(GPIOC, 1 << drvGPIO_ConfigTable[pinName].PIN);
			break;
	}
}

uint8_t drvGPIO_ReadPin(drvGPIO_List_t pinName) {
	uint8_t returnValue = 0;

	switch (drvGPIO_ConfigTable[pinName].PORT) {
		case PORT_A:
			returnValue = GPIO_ReadInputDataBit(GPIOA, 1 << drvGPIO_ConfigTable[pinName].PIN);
			break;
		case PORT_B:
			returnValue = GPIO_ReadInputDataBit(GPIOB, 1 << drvGPIO_ConfigTable[pinName].PIN);
			break;
		case PORT_C:
			returnValue = GPIO_ReadInputDataBit(GPIOC, 1 << drvGPIO_ConfigTable[pinName].PIN);
			break;
	}

	return returnValue;
}
