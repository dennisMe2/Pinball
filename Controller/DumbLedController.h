/*
 * DumbLedController.h
 *
 *  Created on: Nov 12, 2018
 *      Author: dennis
 */

#ifndef DUMBLEDCONTROLLER_H_
#define DUMBLEDCONTROLLER_H_
#include "../Led/DumbLed.h"
#include <Arduino.h>

class DumbLedController {
public:
	DumbLedController();
	void addLed(DumbLed* led);
	void changeColors(uint8_t r, uint8_t g, uint8_t b);
private:
	DumbLed* dumbLeds[14];
	uint8_t numLeds = 0;
};

#endif /* DUMBLEDCONTROLLER_H_ */
