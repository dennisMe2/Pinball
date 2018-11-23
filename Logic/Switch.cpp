/*
 * Switch.cpp
 *
 *  Created on: Oct 5, 2018
 *      Author: dennis
 */

#include "Switch.h"

Switch::Switch() :
		PortUser() {
	activeLow = true;
	trig = false;
	previousStatus = true;
}

Switch::Switch(uint8_t polarity) :
		PortUser() {
	activeLow = true;
	trig = false;
	previousStatus = true;

	if (polarity == HIGH) {
		activeLow = false;
	}
}

bool Switch::on() {
	if (activeLow) {
		return !PortUser::getStatus();
	}
	return PortUser::getStatus();
}

void Switch::setStatus(uint8_t stat) {
	if (stat == previousStatus) return;

	if (--transientDelay == 0 && ((intMillis() - lastChangeTime) > 50) ) {

		PortUser::setStatus(stat);
		lastChangeTime = intMillis();
		previousStatus = stat;

		//trigger only on rising/falling edges
		if (activeLow && (stat == LOW))
			trig = true;
		if (!activeLow && (stat == HIGH))
			trig = true;

		transientDelay = TRANSIENT_DELAY;
	}
}

void Switch::resetTriggers() {
	trig = false;
}

bool Switch::triggered() {
	return trig;
}
