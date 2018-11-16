/*
 * ABController.h
 *
 *  Created on: Nov 15, 2018
 *      Author: dennis
 */

#ifndef ABCONTROLLER_H_
#define ABCONTROLLER_H_

#include "../Led/DumbLed.h"
#include "../Utils.h"

class ABController {
public:
	ABController(DumbLed* a, DumbLed* b, DumbLed* tl, DumbLed* tr, DumbLed* bl, DumbLed* br);
	void setA();
	void setB();
	bool isSetA();
	bool isSetB();
	void reset();
private:
	DumbLed* a;
	DumbLed* b;
	DumbLed* tl;
	DumbLed* tr;
	DumbLed* bl;
	DumbLed* br;
	bool isSetLedA:1;
	bool isSetLedB:1;
};

#endif /* ABCONTROLLER_H_ */
