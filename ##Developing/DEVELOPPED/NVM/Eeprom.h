/*
 * eeprom.h
 *
 *  Created on: Jun 29, 2018
 *      Author: MHmed Hatem
 */

#ifndef EEPROM_EEPROM_H_
#define EEPROM_EEPROM_H_


#include "DriverIncludes.h"

#include "ECU_CONFIGURATION.h"


#define ID_1    1 //Steering Angle Initialize
#define ID_2    2
#define ID_3    3
#define ID_4    4
#define ID_5    5


void Eeprom_init(void);

uint8_t Eeprom_readByte(uint32_t address);
void Eeprom_writeByte(uint32_t address, uint8_t data);

void Eeprom_writeArray(uint32_t address, uint8_t *array, uint8_t size);
void Eeprom_readArray(uint32_t address, uint8_t *array, uint8_t size);

void Eeprom_writeArrayID(uint8_t ID, uint8_t *array, uint8_t size);
void Eeprom_readArrayID(uint8_t ID, uint8_t *array, uint8_t *size);


#endif /* EEPROM_EEPROM_H_ */
