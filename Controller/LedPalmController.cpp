/*
 * LedPalmController.cpp
 *
 *  Created on: Oct 12, 2018
 *      Author: dennis
 */

#include "LedPalmController.h"

LedPalmController::LedPalmController() {
	ledsOff();

}
void LedPalmController::ledsOff() {
	for (int i = 0; i < 5; i++) {
		leds[i]->off();
	}
}
void LedPalmController::addLed(SmartLed* led, int index, uint8_t multiplier) {
	leds[index] = led;
	multipliers[index] = multiplier;
}
void LedPalmController::animate() {
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
void LedPalmController::increment(){
	leds[currentLed]->on();
	currentLed++;
}

void LedPalmController::stopAnimation(){
	ledsOff();
	currentLed = 0;
	animationStopped = true;
}

void LedPalmController::startAnimation(){
	currentLed = 0;
	animationStopped = false;
}
