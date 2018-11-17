/*
 * SmartLed.h
 *
 *  Created on: Nov 12, 2018
 *      Author: dennis
 */

#ifndef BASICLED_H_
#define BASICLED_H_
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class BasicLed {
public:
	BasicLed(Adafruit_NeoPixel* strip, unsigned char pos,uint8_t r, uint8_t g, uint8_t b);
	void setColor(uint8_t r, uint8_t g, uint8_t b);

private:
	Adafruit_NeoPixel* myStrip;
	uint8_t stripPos;
};

#endif /* BASICLED_H_ */
