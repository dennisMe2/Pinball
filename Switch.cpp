/*
 * Switch.cpp
 *
 *  Created on: Oct 5, 2018
 *      Author: dennis
 */

#include "Switch.h"
#include "utils.h"

Switch::Switch() : PortUser() {
	activeLow = true;
	trig =false;
	previousStatus=false;
}

Switch::Switch(uint8_t polarity) : PortUser(){
	activeLow = true;
	trig =false;
	previousStatus=false;

	if(polarity == HIGH){
		activeLow = false;
	}
}

bool Switch::on(){
	if(activeLow){
		return !PortUser::getStatus();
	}
	return PortUser::getStatus();
}

void Switch::setStatus(uint8_t stat){
	if( intMillis() > nextChangeTime && stat != previousStatus ){
		PortUser::setStatus(stat);
		nextChangeTime = intMillis() + debounceDelay;
		previousStatus = stat;
		//trigger only on rising/falling edges
		if(activeLow && (stat == LOW)) trig = true;
		if(!activeLow && (stat == HIGH)) trig = true;
	}
}

void Switch::resetTriggers(){
	trig = false;
}

bool Switch::triggered(){
	return trig;
}
