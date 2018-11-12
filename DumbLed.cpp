/*
 * SmartLed.cpp
 *
 *  Created on: Nov 12, 2018
 *      Author: dennis
 */

#include "Arduino.h"
#include "DumbLed.h"
#include <Adafruit_NeoPixel.h>

//cons
DumbLed::DumbLed(Adafruit_NeoPixel* strip, unsigned char pos) {
	stripPos = pos;
	myStrip = strip;
	normal();
}

void DumbLed::normal() {
	myStrip->setPixelColor(stripPos, 255, 245, 245);
}
void DumbLed::off() {
	myStrip->setPixelColor(stripPos, 0, 0, 0);
}

