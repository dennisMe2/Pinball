/*
 * Kicker.h
 *
 *  Created on: Dec 4, 2018
 *      Author: dennis
 */

#ifndef KICKER_H_
#define KICKER_H_

#include "Solenoid.h"
#include "../Led/BasicLed.h"
#include "../Utils.h"

class Kicker: public Solenoid {
public:
	Kicker();
	void setLed(BasicLed* led);
	virtual void activate();
	virtual void deactivate();
	void setColor(uint8_t r, uint8_t g, uint8_t b);
private:
	BasicLed* led = 0;
	uint8_t color[3] = {0,0,0};
};


#endif /* KICKER_H_ */
