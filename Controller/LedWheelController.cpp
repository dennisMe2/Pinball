/*
 * LedWheelController.cpp
 *
 *  Created on: Oct 12, 2018
 *      Author: dennis
 */

#include "LedWheelController.h"

#include "../Utils.h"

LedWheelController::LedWheelController(BoatController* boatie) {
	boat = boatie;
}
void LedWheelController::addLed(SmartLed* led, int index){
	leds[index] = led;
}
void LedWheelController::addLed10(SmartLed* led){
	led10x = led;
	led10x->off();
}

void LedWheelController::reset(){
	led10x->off();
	isPaused = false;
	boat->allOff();
}

void LedWheelController::setGame(Game* game){
	this->game = game;
}

uint8_t LedWheelController::getPoints(){
	if (boat->blueOn() && colours[currentLed] == WHEEL_B)
		return points[currentLed] * 10;

	if (boat->greenOn() && colours[currentLed] == WHEEL_G)
			return points[currentLed] * 10;

	if (boat->yellowOn() && colours[currentLed] == WHEEL_Y)
			return points[currentLed] * 10;

	if (boat->redOn() && colours[currentLed] == WHEEL_R)
			return points[currentLed] * 10;

	return points[currentLed];

}

void LedWheelController::pause(){
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
		if(currentLed == 0){
			game->setReplay();
		}
	}

}

void LedWheelController::unPause(){
	isPaused = false;
}

void LedWheelController::animate(){
	if (isPaused) return;

	if(millis() > nextTime){
		leds[currentLed]->off();
		if(++currentLed > 9) currentLed = 0;
		leds[currentLed]->on();
		nextTime = millis() + animationDelay;
	}
}
