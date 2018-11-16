/*
 * PostController.cpp
 *
 *  Created on: Nov 16, 2018
 *      Author: dennis
 */

#include "PostController.h"

PostController::PostController(DumbLed* led1, DumbLed* led2, Solenoid* up, Solenoid* down) {
	this->led1 = led1;
	this->led2 = led2;
	this->up = up;
	this->down = down;
}

void PostController::postUp(){
	led1->setColor(RED);
	led2->setColor(RED);
	up->activate();
}
void PostController::postDown(){
	led1->setColor(BLACK);
	led2->setColor(BLACK);
	down->activate();
}
