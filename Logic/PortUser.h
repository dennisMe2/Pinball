/*
 * Solenoid.h
 *
 *  Created on: Oct 5, 2018
 *      Author: dennis
 */

#ifndef PORTUSER_H_
#define PORTUSER_H_
#include <Arduino.h>

class PortUser {
public:
	PortUser();
	virtual ~PortUser(){};

	virtual void activate(){};
	virtual void deactivate(){};
	virtual bool isExpired(){return false;};
	virtual void checkDelayedActivation(){};
	virtual void setStatus(uint8_t stat){status = stat;};
	virtual void resetTriggers(){};
	virtual uint8_t getStatus(){return status;};
private:
	uint8_t status = HIGH;
};

#endif /* PORTUSER_H_ */
