/*
 * SmartLed.cpp
 *
 *  Created on: Nov 12, 2018
 *      Author: dennis
 */

#include "Arduino.h"
#include "DumbLed.h"
#include <Adafruit_NeoPixel.h>
#include "Utils.h"

//cons
DumbLed::DumbLed(Adafruit_NeoPixel* strip, unsigned char pos, uint8_t r, uint8_t g, uint8_t b) {
	stripPos = pos;
	myStrip = strip;
	setColor(r,g,b);
}

void DumbLed::setColor(uint8_t r, uint8_t g, uint8_t b) {
	myStrip->setPixelColor(stripPos, r, g, b);
}
