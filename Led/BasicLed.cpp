/*
 * SmartLed.cpp
 *
 *  Created on: Nov 12, 2018
 *      Author: dennis
 */

#include "BasicLed.h"

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include "../Utils.h"

//cons
BasicLed::BasicLed(Adafruit_NeoPixel* strip, unsigned char pos, uint8_t r, uint8_t g, uint8_t b) {
	stripPos = pos;
	myStrip = strip;
	setColor(r,g,b);
}

void BasicLed::setColor(uint8_t r, uint8_t g, uint8_t b) {
	myStrip->setPixelColor(stripPos, r, g, b);
}
