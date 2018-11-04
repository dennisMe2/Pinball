/*
 * PortExpander.h
 *
 *  Created on: Oct 5, 2018
 *      Author: dennis
 */

#ifndef PORTEXPANDER_H_
#define PORTEXPANDER_H_
#include "MCP23S17.h"
#include <SPI.h>

#include "PortUser.h"

class PortExpander : public MCP23S17{
public:
	void refreshOutputs();
	void refreshInputs();
	void resetTriggers();
	void addSolenoid( PortUser* portUser, unsigned char number);
	void addSwitch( PortUser* portUser, unsigned char number);
	PortExpander(SPIClass *spi, unsigned char chipSelect, unsigned char address);
private:
	PortUser* portUsers[16] {};

	void setOutputPins();
};


#endif /* PORTEXPANDER_H_ */
