/*
 * BoatController.h
 *
 *  Created on: Nov 13, 2018
 *      Author: dennis
 */

#ifndef BOATCONTROLLER_H_
#define BOATCONTROLLER_H_
#include "../Led/BasicLed.h"
#include <Arduino.h>

class BoatController {
public:
	BoatController(BasicLed* ledY, BasicLed* ledG, BasicLed* ledB, BasicLed* ledR);
	void yellowOn();
	bool yellowIsOn();
	void greenOn();
	bool greenIsOn();
	void blueOn();
	bool blueIsOn();
	void redOn();
	bool redIsOn();
	bool areAllOn();
	void allOff();
private:
	BasicLed* yellow;
	BasicLed* green;
	BasicLed* blue;
	BasicLed* red;
	bool isYellowOn:1;
	bool isGreenOn:1;
	bool isBlueOn:1;
	bool isRedOn:1;
};

#endif /* BOATCONTROLLER_H_ */
