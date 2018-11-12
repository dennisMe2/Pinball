/*
 * Solenoid.h
 *
 *  Created on: Oct 5, 2018
 *      Author: dennis
 */

#ifndef SOLENOID_H_
#define SOLENOID_H_

#include "PortUser.h"


class Solenoid: public PortUser {
public:
	Solenoid();
	Solenoid(uint8_t tMaxOn);
	virtual ~Solenoid(){};

	uint8_t maxOnTime = 20; //milliseconds
	unsigned int deactivateAfter = 0;
	virtual void activate();
	virtual void deactivate();
	virtual bool isExpired();
	virtual void checkDelayedActivation(){};
};

#endif /* SOLENOID_H_ */
