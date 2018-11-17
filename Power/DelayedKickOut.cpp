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
DelayedKickOut::DelayedKickOut(unsigned int delayMaxMs) : Solenoid() {
	maxDelay = delayMaxMs;
}

void DelayedKickOut::setWheelController(WheelController* wheelController){
	wheel = wheelController;
}

void DelayedKickOut::activate(){
	activationStart = intMillis() + random(500, maxDelay);
	if(wheel !=0) wheel->pause();
}

void DelayedKickOut::activateImmediate(){
	activationStart = 0;
	Solenoid::activate();
	if(wheel !=0) wheel->unPause();
}

 void DelayedKickOut::checkDelayedActivation(){
	 if((activationStart != 0) && ((signed int)(intMillis() - activationStart) > 0)){
		 activateImmediate();
	 }
 };
