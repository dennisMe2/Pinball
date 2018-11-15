/*
 * BoatController.h
 *
 *  Created on: Nov 13, 2018
 *      Author: dennis
 */

#ifndef BOATCONTROLLER_H_
#define BOATCONTROLLER_H_
#include "../Led/DumbLed.h"
#include <Arduino.h>

class BoatController {
public:
	BoatController(DumbLed* ledY, DumbLed* ledG, DumbLed* ledB, DumbLed* ledR);
	bool yellowOn();
	bool greenOn();
	bool blueOn();
	bool redOn();
	bool areAllOn();
	void allOff();
private:
	DumbLed* yellow;
	DumbLed* green;
	DumbLed* blue;
	DumbLed* red;
	bool isYellowOn:1;
	bool isGreenOn:1;
	bool isBlueOn:1;
	bool isRedOn:1;
};

#endif /* BOATCONTROLLER_H_ */
