/*
 * Kicker.cpp
 *
 *  Created on: Dec 4, 2018
 *      Author: dennis
 */

#include "Kicker.h"

Kicker::Kicker() : Solenoid(){
	Solenoid::maxOnTime = 50;
}

void Kicker::setLed(BasicLed* led){
	this->led = led;
}

void Kicker::setColor(uint8_t r, uint8_t g, uint8_t b){
	led->setColor(r, g, b);
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

void Kicker::activate(){
	Solenoid::activate();
	led->setColor(BLUE);
}

void Kicker::deactivate(){
	Solenoid::deactivate();
	led->setColor(color[0],color[1],color[2]);
}
