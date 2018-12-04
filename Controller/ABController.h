/*
 * ABController.h
 *
 *  Created on: Nov 15, 2018
 *      Author: dennis
 */

#ifndef ABCONTROLLER_H_
#define ABCONTROLLER_H_

#include "../Power/Kicker.h"
#include "../Utils.h"

class ABController {
public:
	ABController(BasicLed* a, BasicLed* b, Kicker* tl, Kicker* tr, Kicker* bl, Kicker* br);
	void setA();
	void resetA();
	void setB();
	void resetB();
	bool isSetA();
	bool isSetB();
	void reset();
private:
	BasicLed* a;
	BasicLed* b;
	Kicker* tl;
	Kicker* tr;
	Kicker* bl;
	Kicker* br;
	bool isSetLedA:1;
	bool isSetLedB:1;
};

#endif /* ABCONTROLLER_H_ */
