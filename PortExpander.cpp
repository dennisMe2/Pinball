/*
 * PortExpander.cpp
 *
 *  Created on: Oct 5, 2018
 *      Author: dennis
 */

#include "PortExpander.h"
#include "MCP23S17.h"
#include <SPI.h>
#include <Arduino.h>

PortExpander::PortExpander(SPIClass* spi, unsigned char chipSelect,
		unsigned char address) :
		MCP23S17(spi, chipSelect, address) {
	MCP23S17::begin();
	//all the magic happens in the base class
}

void PortExpander::addSolenoid(PortUser* portUser, uint8_t number) {
	portUsers[number] = portUser;
	MCP23S17::pinMode(number, OUTPUT);
}

void PortExpander::addSwitch(PortUser* portUser, unsigned char number) {
	portUsers[number] = portUser;
	MCP23S17::pinMode(number, INPUT_PULLUP);
}

void PortExpander::refreshOutputs() {
	uint16_t portStatus = MCP23S17::readPort();
	for (uint8_t i = 0; i < 16; i++) {
		PortUser* portUser = portUsers[i];
		if (portUser != NULL) {

			portUser->checkDelayedActivation(); //in case of kick outs

			if (portUser->isExpired()) {
				portUser->deactivate();
				portStatus &= ~(1UL << i); //clear bit
			}else if(HIGH == portUser->getStatus()){
				portStatus |= (0b1 << i);  //set if status is HIGH else leave alone
			}
		}
	}
	MCP23S17::writePort(portStatus); //NB: doesn't impact Switch types, only Solenoids!
}

void PortExpander::refreshInputs() {
	uint16_t portStatus = MCP23S17::readPort();
	for (uint8_t i = 0; i < 16; i++) {
		if (portUsers[i] != NULL) {
			portUsers[i]->setStatus((portStatus >> i) & 0B0000000000000001);
		}
	}

}

void PortExpander::resetTriggers(){
	for (uint8_t i = 0; i < 16; i++) {
		if (portUsers[i] != NULL) {
			portUsers[i]->resetTriggers();
		}
	}
}

