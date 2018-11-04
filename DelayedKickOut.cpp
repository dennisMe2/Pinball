/*
 * DelayedKickOut.cpp
 *
 *  Created on: Oct 10, 2018
 *      Author: dennis
 */

#include "DelayedKickOut.h"
#include "utils.h"

DelayedKickOut::DelayedKickOut() : Solenoid() {

}
DelayedKickOut::DelayedKickOut(unsigned int delayMaxMs) : Solenoid() {
	maxDelay = delayMaxMs;
}


void DelayedKickOut::activate(){
	activationStart = intMillis() + random(500,maxDelay);
	//activationStart = intMillis() + 1000;
}

void DelayedKickOut::activateDelayed(){
	activationStart = 0;
	Solenoid::activate();
}

 void DelayedKickOut::checkDelayedActivation(){
	 if((activationStart != 0) && (intMillis() >= activationStart)){
		 activateDelayed();
	 }
 };
