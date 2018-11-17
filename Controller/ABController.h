/*
 * ABController.h
 *
 *  Created on: Nov 15, 2018
 *      Author: dennis
 */

#ifndef ABCONTROLLER_H_
#define ABCONTROLLER_H_

#include "../Led/BasicLed.h"
#include "../Utils.h"

class ABController {
public:
	ABController(BasicLed* a, BasicLed* b, BasicLed* tl, BasicLed* tr, BasicLed* bl, BasicLed* br);
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
	BasicLed* tl;
	BasicLed* tr;
	BasicLed* bl;
	BasicLed* br;
	bool isSetLedA:1;
	bool isSetLedB:1;
};

#endif /* ABCONTROLLER_H_ */
