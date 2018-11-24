/*
 * DelayedKickOut.h
 *
 *  Created on: Oct 10, 2018
 *      Author: dennis
 */

#ifndef DELAYEDKICKOUT_H_
#define DELAYEDKICKOUT_H_

#include "../Controller/WheelController.h"
#include "Solenoid.h"
#include "../Sound/MechSound.h"

class DelayedKickOut: public Solenoid {
public:
	DelayedKickOut();
	DelayedKickOut(unsigned int delayMaxMs, uint8_t maxActive);
	virtual void activate();
	virtual void checkDelayedActivation();
	void activateImmediate();
	bool isInUse();
	void setWheelController(WheelController* wheelController);
	void setMechSound(MechSound* mechSound);
private:
	unsigned int activationStart = 0;
	unsigned int maxDelay = 2000;
	WheelController* wheel = 0;
	bool isWaitingToFire = false;
	MechSound* mechSound = 0;

};

#endif /* DELAYEDKICKOUT_H_ */
