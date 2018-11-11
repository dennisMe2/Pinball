/*
 * Solenoid.cpp
 *
 *  Created on: Oct 5, 2018
 *      Author: dennis
 */

#include "Solenoid.h"
#include "PortUser.h"


Solenoid::Solenoid() : PortUser(){
	PortUser::setStatus(LOW);
}

Solenoid::Solenoid(unsigned int tMaxOn){
	PortUser::setStatus(LOW);
	maxOnTime = tMaxOn;
}

void Solenoid::activate(){
	this->setStatus(HIGH);

	if (maxOnTime == 0){
		deactivateAfter = 0;
	} else{
		deactivateAfter = millis() + maxOnTime;
	}
}

void Solenoid::deactivate(){
	this->setStatus(LOW);
	deactivateAfter = 0;
}

bool Solenoid::isExpired(){
	if(0 == deactivateAfter){
		return false;
	}
	return (millis() > deactivateAfter);
}
