/*
 * SmartLed.cpp
 *
 *  Created on: Oct 4, 2018
 *      Author: dennis
 */

#include "Arduino.h"
#include "SmartLed.h"
#include <Adafruit_NeoPixel.h>

//cons
SmartLed::SmartLed(Adafruit_NeoPixel* strip, unsigned char pos) {
	stripPos = pos;
	stdColorR = 255;
	stdColorG = 255;
	stdColorB = 255;
	myStrip = strip;
	on();
}

SmartLed::SmartLed(Adafruit_NeoPixel* strip, unsigned char pos,
		unsigned char stdR, unsigned char stdG, unsigned char stdB) {
	stripPos = pos;
	stdColorR = stdR;
	stdColorG = stdG;
	stdColorB = stdB;
	myStrip = strip;
	on();
}

// Member Functions()

void SmartLed::on() {
	myStrip->setPixelColor(stripPos, stdColorR, stdColorG, stdColorB);
}
void SmartLed::off() {
	myStrip->setPixelColor(stripPos, 0, 0, 0);
}

