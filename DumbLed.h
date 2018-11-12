/*
 * SmartLed.h
 *
 *  Created on: Nov 12, 2018
 *      Author: dennis
 */

#ifndef DUMBLED_H_
#define DUMBLED_H_

#include <Adafruit_NeoPixel.h>

class DumbLed {
public:
	Adafruit_NeoPixel* myStrip;
	uint8_t stripPos;

	DumbLed(Adafruit_NeoPixel* strip, unsigned char pos);

	void normal();
	void off();

};

#endif /* DUMBLED_H_ */
