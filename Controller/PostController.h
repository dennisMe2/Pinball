/*
 * PostController.h
 *
 *  Created on: Nov 16, 2018
 *      Author: dennis
 */

#ifndef POSTCONTROLLER_H_
#define POSTCONTROLLER_H_

#include "../Led/DumbLed.h"
#include "../Power/Solenoid.h"
#include "../Utils.h"

class PostController {
public:
	PostController(DumbLed* led1, DumbLed* led2, Solenoid* up, Solenoid* down);
	void postUp();
	void postDown();
private:
	DumbLed* led1;
	DumbLed* led2;
	Solenoid* up;
	Solenoid* down;
};

#endif /* POSTCONTROLLER_H_ */
