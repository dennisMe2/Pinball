/*
 * Solenoid.cpp
 *
 *  Created on: Oct 5, 2018
 *      Author: dennis
 */

#include "Solenoid.h"
#include "PortUser.h"
#include "Utils.h"


Solenoid::Solenoid() : PortUser(){
	PortUser::setStatus(LOW);
}

Solenoid::Solenoid(uint8_t tMaxOn) : PortUser(){
	PortUser::setStatus(LOW);
	maxOnTime = tMaxOn;
}

void Solenoid::activate(){
	this->setStatus(HIGH);

	if (maxOnTime == 0){
		deactivateAfter = 0;
	} else{
		deactivateAfter = intMillis() + maxOnTime;
	}
}

void Solenoid::deactivate(){
	this->setStatus(LOW);
	deactivateAfter = 0;
}

bool Solenoid::isExpired(){
	if(this->getStatus() == LOW) return true;//for tilt

	if(0 == maxOnTime || 0 == deactivateAfter){
		return false;
	}
	return ((signed int)(intMillis() - deactivateAfter ) > 0);
}
