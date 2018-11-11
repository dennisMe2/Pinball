/*
 * DelayedKickOut.cpp
 *
 *  Created on: Oct 10, 2018
 *      Author: dennis
 */

#include "DelayedKickOut.h"

DelayedKickOut::DelayedKickOut() : Solenoid() {

}
DelayedKickOut::DelayedKickOut(unsigned int delayMaxMs) : Solenoid() {
	maxDelay = delayMaxMs;
}


void DelayedKickOut::activate(){
	activationStart = millis() + random(500, maxDelay);
}

void DelayedKickOut::activateDelayed(){
	activationStart = 0;
	Solenoid::activate();
}

 void DelayedKickOut::checkDelayedActivation(){
	 if((activationStart != 0) && (millis() >= activationStart)){
		 activateDelayed();
	 }
 };
