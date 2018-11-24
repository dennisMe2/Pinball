/*
 * Switch.cpp
 *
 *  Created on: Oct 5, 2018
 *      Author: dennis
 */

#include "Switch.h"

Switch::Switch() :
		PortUser() {
	init();
}

Switch::Switch(uint8_t polarity) :
		PortUser() {
	init();
	if (polarity == HIGH) {
		activeLow = false;
	}
}

void Switch::init(){
	activeLow = true;
	trig = false;
	previousStatus = true;
	isTransient = true;
}

bool Switch::on() {
	if (activeLow) {
		return !PortUser::getStatus();
	}
	return PortUser::getStatus();
}

void Switch::setStatus(uint8_t stat) {
	if( isTransient){
			isTransient = false;
			return;
	}

	if (stat == previousStatus) return;

	if ((intMillis() - lastChangeTime) > 20) {

		PortUser::setStatus(stat);
		lastChangeTime = intMillis();
		previousStatus = stat;

		//trigger only on rising/falling edges
		if (activeLow && (stat == LOW))
			trig = true;
		if (!activeLow && (stat == HIGH))
			trig = true;

		isTransient = true;
	}
}

void Switch::resetTriggers() {
	trig = false;
}

bool Switch::triggered() {
	return trig;
}
