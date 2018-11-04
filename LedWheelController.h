/*
 * LedWheelController.h
 *
 *  Created on: Oct 12, 2018
 *      Author: dennis
 */

#ifndef LEDWHEELCONTROLLER_H_
#define LEDWHEELCONTROLLER_H_

#include "SmartLed.h"

class LedWheelController {
public:
	LedWheelController();
	void addLed(SmartLed* led, int index);
	void animate();
	void setDelay(unsigned int delay){animationDelay=delay;};
private:
	SmartLed* leds[10];
	uint8_t currentLed = 0;
	unsigned int nextTime = 0;
	unsigned int animationDelay = 3000;
};

#endif /* LEDWHEELCONTROLLER_H_ */
