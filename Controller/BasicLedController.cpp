/*
 * DumbLedController.cpp
 *
 *  Created on: Nov 12, 2018
 *      Author: dennis
 */

#include "BasicLedController.h"

BasicLedController::BasicLedController() {
	// TODO Auto-generated constructor stub

}
void BasicLedController::addLed(BasicLed* led){
	dumbLeds[numLeds] = led;
	numLeds++;
}

void BasicLedController::changeColors(uint8_t r, uint8_t g, uint8_t b){
	for(int i=0; i<numLeds; i++){
		dumbLeds[i]->setColor(r,g,b);
	}
}

