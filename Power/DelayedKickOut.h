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
	DelayedKickOut(unsigned int delayMaxMs, uint8_t maxActive, bool* blockSlow);
	virtual void activate();
	virtual void deActivate();
	virtual void checkDelayedActivation();
	void activateImmediate();
	bool isInUse();
	void setWheelController(WheelController* wheelController);
	void setMechSound(MechSound* mechSound);

private:
	DelayedKickOut();
	unsigned int activationStart = 0;
	unsigned int maxDelay = 2000;
	WheelController* wheel = 0;
	bool isWaitingToFire = false;
	MechSound* mechSound = 0;
	bool* blockSlow = 0;

};

#endif /* DELAYEDKICKOUT_H_ */
