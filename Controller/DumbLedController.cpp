/*
 * DumbLedController.cpp
 *
 *  Created on: Nov 12, 2018
 *      Author: dennis
 */

#include "DumbLedController.h"

DumbLedController::DumbLedController() {
	// TODO Auto-generated constructor stub

}
void DumbLedController::addLed(DumbLed* led){
	dumbLeds[numLeds] = led;
	numLeds++;
}

void DumbLedController::changeColors(uint8_t r, uint8_t g, uint8_t b){
	for(int i=0; i<numLeds; i++){
		dumbLeds[i]->setColor(r,g,b);
	}
}

