/*
 * LedPalmController.h
 *
 *  Created on: Oct 12, 2018
 *      Author: dennis
 */

#ifndef LEDPALMCONTROLLER_H_
#define LEDPALMCONTROLLER_H_

#include <Arduino.h>

#include "../Led/SmartLed.h"
class LedPalmController {
public:
	LedPalmController();
	void addLed(SmartLed* led, int index, uint8_t multiplier);
	void ledsOff();
	void animate();
	void setDelay(unsigned int delay){animationDelay=delay;};
	uint8_t getMultiplier(){return multipliers[currentLed];};
private:
	SmartLed* leds[5];
	uint8_t multipliers[5];
	uint8_t currentLed = 0;
	unsigned long nextTime = 0;
	unsigned int animationDelay = 15000;
};

#endif /* LEDPALMCONTROLLER_H_ */
