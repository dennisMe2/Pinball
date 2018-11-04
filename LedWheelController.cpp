/*
 * LedWheelController.cpp
 *
 *  Created on: Oct 12, 2018
 *      Author: dennis
 */

#include "LedWheelController.h"
#include "utils.h"

LedWheelController::LedWheelController() {
	// TODO Auto-generated constructor stub

}
void LedWheelController::addLed(SmartLed* led, int index){
	leds[index] = led;
}
void LedWheelController::animate(){
	if(intMillis() > nextTime){
		leds[currentLed]->off();
		if(++currentLed > 9) currentLed = 0;
		leds[currentLed]->normal();
		nextTime = intMillis() + animationDelay;
	}
}
