/*
 * DumbLedController.h
 *
 *  Created on: Nov 12, 2018
 *      Author: dennis
 */

#ifndef BASICLEDCONTROLLER_H_
#define BASICLEDCONTROLLER_H_
#include "../Led/BasicLed.h"
#include <Arduino.h>

class BasicLedController {
public:
	BasicLedController();
	void addLed(BasicLed* led);
	void changeColors(uint8_t r, uint8_t g, uint8_t b);
private:
	BasicLed* dumbLeds[14];
	uint8_t numLeds = 0;
};

#endif /* BASICLEDCONTROLLER_H_ */
