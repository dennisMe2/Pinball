/*
 * ABController.h
 *
 *  Created on: Nov 15, 2018
 *      Author: dennis
 */

#ifndef ABCONTROLLER_H_
#define ABCONTROLLER_H_

#include "DumbLed.h"
#include "Utils.h"

class ABController {
public:
	ABController(DumbLed* a, DumbLed* b, DumbLed* tl, DumbLed* tr, DumbLed* bl, DumbLed* br);
	void setA();
	void setB();
private:
	DumbLed* a;
	DumbLed* b;
	DumbLed* tl;
	DumbLed* tr;
	DumbLed* bl;
	DumbLed* br;
};

#endif /* ABCONTROLLER_H_ */
