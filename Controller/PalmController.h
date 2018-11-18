/*
 * LedPalmController.h
 *
 *  Created on: Oct 12, 2018
 *      Author: dennis
 */

#ifndef PALMCONTROLLER_H_
#define PALMCONTROLLER_H_

#include <Arduino.h>

#include "../Led/SmartLed.h"
class PalmController {
public:
	PalmController();
	void addLed(SmartLed* led, int index, uint8_t multiplier);
	void ledsOff();
	void animate();
	void stopAnimation();
	void startAnimation();
	void increment();
	void setDelay(unsigned int delay){animationDelay=delay;};
	uint8_t getMultiplier(){return multipliers[currentLed];};
private:
	SmartLed* leds[5];
	uint8_t multipliers[5];
	uint8_t currentLed = 0;
	unsigned long lastActivated = 0;
	uint8_t debounceDelay = 255;
	unsigned long nextTime = 0;
	unsigned int animationDelay = 15000;
	bool animationStopped = false;
};

#endif /* PALMCONTROLLER_H_ */
