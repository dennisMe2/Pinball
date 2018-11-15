/*
 * BoatController.cpp
 *
 *  Created on: Nov 13, 2018
 *      Author: dennis
 */

#include "BoatController.h"

#include "../Utils.h"

BoatController::BoatController(DumbLed* ledY, DumbLed* ledG, DumbLed* ledB,DumbLed* ledR) {
	yellow = ledY;
	green = ledG;
	blue = ledB;
	red = ledR;

	allOff();
}

bool BoatController::yellowOn(){
	yellow->setColor(YELLOW);
	isYellowOn = true;
	return isYellowOn;
}

bool BoatController::greenOn(){
	green->setColor(GREEN);
	isGreenOn = true;
	return isGreenOn;
}

bool BoatController::blueOn(){
	blue->setColor(BLUE);
	isBlueOn = true;
	return isBlueOn;
}

bool BoatController::redOn(){
	red->setColor(RED);
	isRedOn = true;
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
