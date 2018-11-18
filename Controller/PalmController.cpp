/*
 * LedPalmController.cpp
 *
 *  Created on: Oct 12, 2018
 *      Author: dennis
 */

#include "PalmController.h"

PalmController::PalmController() {
	ledsOff();

}
void PalmController::ledsOff() {
	for (int i = 0; i < 5; i++) {
		leds[i]->off();
	}
	currentLed = 0;
}
void PalmController::addLed(SmartLed* led, int index, uint8_t multiplier) {
	leds[index] = led;
	multipliers[index] = multiplier;
}
void PalmController::animate() {
	if(animationStopped) return;

	if(millis() > nextTime){
		if (currentLed > 4) {
			ledsOff();
			currentLed = 0;
		} else {
			leds[currentLed]->on();
			currentLed++;
		}
		nextTime = millis() + animationDelay;
	}

}

void PalmController::increment(){
	if((millis() - lastActivated) < debounceDelay) return;

	leds[currentLed]->on();
	if(++currentLed > 5) {
		currentLed = 0;
		ledsOff();
	}
	lastActivated = millis();
}

void PalmController::stopAnimation(){
	if(animationStopped) return;
	ledsOff();
	currentLed = 0;
	animationStopped = true;
}

void PalmController::startAnimation(){
	currentLed = 0;
	animationStopped = false;
}
