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
#include "Display.h"

PortExpander::PortExpander(SPIClass* spi, unsigned char chipSelect,
		unsigned char address) :
		MCP23S17(spi, chipSelect, address) {

	MCP23S17::begin();
	for (uint8_t i = 0; i < 16; i++) {
		MCP23S17::pinMode(i, INPUT_PULLUP);//prevent floating inputs
	}
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

void PortExpander::showPinsOn7Segment(Display* disp){

	uint8_t SEG_DISP[4] = {0,0,0,0};

	if(MCP23S17::digitalRead(0)) SEG_DISP[0] |= SEG_F;
	if(MCP23S17::digitalRead(1)) SEG_DISP[0] |= SEG_B;

	if(MCP23S17::digitalRead(2)) SEG_DISP[1] |= SEG_F;
	if(MCP23S17::digitalRead(3)) SEG_DISP[1] |= SEG_B;

	if(MCP23S17::digitalRead(4)) SEG_DISP[2] |= SEG_F;
	if(MCP23S17::digitalRead(5)) SEG_DISP[2] |= SEG_B;

	if(MCP23S17::digitalRead(6)) SEG_DISP[3] |= SEG_F;
	if(MCP23S17::digitalRead(7)) SEG_DISP[3] |= SEG_B;

	if(MCP23S17::digitalRead(8)) SEG_DISP[0] |= SEG_E;
	if(MCP23S17::digitalRead(9)) SEG_DISP[0] |= SEG_C;

	if(MCP23S17::digitalRead(10)) SEG_DISP[1] |= SEG_E;
	if(MCP23S17::digitalRead(11)) SEG_DISP[1] |= SEG_C;

	if(MCP23S17::digitalRead(12)) SEG_DISP[2] |= SEG_E;
	if(MCP23S17::digitalRead(13)) SEG_DISP[2] |= SEG_C;

	if(MCP23S17::digitalRead(14)) SEG_DISP[3] |= SEG_E;
	if(MCP23S17::digitalRead(15)) SEG_DISP[3] |= SEG_C;

	disp->setSegments(SEG_DISP);

}

void PortExpander::resetTriggers(){
	for (uint8_t i = 0; i < 16; i++) {
		if (portUsers[i] != NULL) {
			portUsers[i]->resetTriggers();
		}
	}
}

