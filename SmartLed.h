/*
 * SmartLed.h
 *
 *  Created on: Oct 4, 2018
 *      Author: dennis
 */

#ifndef SMARTLED_H_
#define SMARTLED_H_

#include <Adafruit_NeoPixel.h>

class SmartLed {
public:
	Adafruit_NeoPixel* myStrip;
	uint8_t stripPos;

	uint8_t stdColorR;
	uint8_t stdColorG;
	uint8_t stdColorB;

	SmartLed(Adafruit_NeoPixel* strip, unsigned char pos);
	SmartLed(Adafruit_NeoPixel* strip, unsigned char pos, unsigned char stdR,
			unsigned char stdG, unsigned char stdB);

	void normal();
	void off();

};

#endif /* SMARTLED_H_ */
