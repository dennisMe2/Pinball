/*
 * DelayedKickOut.cpp
 *
 *  Created on: Oct 10, 2018
 *      Author: dennis
 */

#include "DelayedKickOut.h"

#include "../Utils.h"

DelayedKickOut::DelayedKickOut() : Solenoid() {

}

DelayedKickOut::DelayedKickOut(unsigned int delayMaxMs, uint8_t maxActive) : Solenoid() {
	maxDelay = delayMaxMs;
	maxOnTime = maxActive;
}

void DelayedKickOut::setWheelController(WheelController* wheelController){
	wheel = wheelController;
}

void DelayedKickOut::setMechSound(MechSound* mechSound){
	this->mechSound = mechSound;
}


void DelayedKickOut::activate(){
	if (isWaitingToFire) return;
	mechSound->rattle(200);
	activationStart = intMillis() + random(500, maxDelay);
	if(wheel !=0) wheel->pause();
	isWaitingToFire = true;
}

bool DelayedKickOut::isInUse(){
	return isWaitingToFire;
}

void DelayedKickOut::activateImmediate(){
	isWaitingToFire = false;
	activationStart = 0;
	mechSound->stop();
	Solenoid::activate();
	if(wheel !=0) wheel->unPause();
}

 void DelayedKickOut::checkDelayedActivation(){
	 if((activationStart != 0) && ((signed int)(intMillis() - activationStart) > 0)){
		 activateImmediate();
	 }
 };
