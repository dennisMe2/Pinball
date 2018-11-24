/*
 * LedWheelController.cpp
 *
 *  Created on: Oct 12, 2018
 *      Author: dennis
 */

#include "WheelController.h"

#include "../Utils.h"

WheelController::WheelController(BoatController* boatie) {
	boat = boatie;
}
void WheelController::addLed(SmartLed* led, int index){
	leds[index] = led;
}
void WheelController::addLed10(SmartLed* led){
	led10x = led;
	led10x->off();
}

void WheelController::reset(){
	led10x->off();
	isPaused = false;
	boat->allOff();
}

void WheelController::setGame(Game* game){
	this->game = game;
}

uint8_t WheelController::getPoints(){
	if (boat->blueIsOn() && colours[currentLed] == WHEEL_B)
		return points[currentLed] * 10;

	if (boat->greenIsOn() && colours[currentLed] == WHEEL_G)
			return points[currentLed] * 10;

	if (boat->yellowIsOn() && colours[currentLed] == WHEEL_Y)
			return points[currentLed] * 10;

	if (boat->redIsOn() && colours[currentLed] == WHEEL_R)
			return points[currentLed] * 10;

	return points[currentLed];

}

void WheelController::pause(){
	if (isPaused) return; //prevent repeat triggering

	isPaused = true;

	switch (colours[currentLed]){
		case WHEEL_R:
			boat->redOn();
			break;
		case WHEEL_G:
			boat->greenOn();
			break;
		case WHEEL_B:
			boat->blueOn();
			break;
		case WHEEL_Y:
			boat->yellowOn();
			break;
	}

	if(boat->areAllOn()){
		led10x->on();
		game->setMultiplier(10);
	}
	if(currentLed == 0){
		game->setReplay();
	}

}

void WheelController::unPause(){
	isPaused = false;
}

void WheelController::animate(){
	if (isPaused) return;

	if(millis() > nextTime){
		leds[currentLed]->off();
		if(++currentLed > 9) currentLed = 0;
		leds[currentLed]->on();
		nextTime = millis() + animationDelay;
	}
}
