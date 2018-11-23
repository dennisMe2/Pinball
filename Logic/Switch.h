/*
 * Switch.h
 *
 *  Created on: Oct 5, 2018
 *      Author: dennis
 */

#ifndef SWITCH_H_
#define SWITCH_H_
#define TRANSIENT_DELAY 3

#include "PortUser.h"
#include "../Utils.h"

class Switch: public PortUser {
public:
	Switch();
	Switch(uint8_t polarity);
	bool on();
	bool triggered();
	virtual void resetTriggers();
	virtual void setStatus(uint8_t stat);

private:
	unsigned int lastChangeTime = 0;
	uint8_t transientDelay = TRANSIENT_DELAY;
	bool activeLow:1;
	bool trig:1;
	bool previousStatus:1;

};

#endif /* SWITCH_H_ */
