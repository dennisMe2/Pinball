/*
 * BoatController.cpp
 *
 *  Created on: Nov 13, 2018
 *      Author: dennis
 */

#include "BoatController.h"

#include "../Utils.h"

BoatController::BoatController(BasicLed* ledY, BasicLed* ledG, BasicLed* ledB,BasicLed* ledR) {
	yellow = ledY;
	green = ledG;
	blue = ledB;
	red = ledR;

	allOff();
}

void BoatController::yellowOn(){
	yellow->setColor(YELLOW);
	isYellowOn = true;
}

bool BoatController::yellowIsOn(){
	return isYellowOn;
}

void BoatController::greenOn(){
	green->setColor(GREEN);
	isGreenOn = true;
}

bool BoatController::greenIsOn(){
	return isGreenOn;
}

void BoatController::blueOn(){
	blue->setColor(BLUE);
	isBlueOn = true;
}

bool BoatController::blueIsOn(){
	return isBlueOn;
}

void BoatController::redOn(){
	red->setColor(RED);
	isRedOn = true;
}
bool BoatController::redIsOn(){
	return isRedOn;
}

void BoatController::allOff(){
	yellow->setColor(BLACK);
	isYellowOn = false;
	green->setColor(BLACK);
	isGreenOn = false;
	blue->setColor(BLACK);
	isBlueOn = false;
	red->setColor(BLACK);
	isRedOn = false;
}

bool BoatController::areAllOn(){
	return (isYellowOn && isGreenOn && isBlueOn && isRedOn);
}
