/*
 * SmartLed.h
 *
 *  Created on: Nov 12, 2018
 *      Author: dennis
 */

#ifndef DUMBLED_H_
#define DUMBLED_H_
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class DumbLed {
public:
	DumbLed(Adafruit_NeoPixel* strip, unsigned char pos,uint8_t r, uint8_t g, uint8_t b);
	void setColor(uint8_t r, uint8_t g, uint8_t b);

private:
	Adafruit_NeoPixel* myStrip;
	uint8_t stripPos;
};

#endif /* DUMBLED_H_ */
