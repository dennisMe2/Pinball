/*
 * PostController.cpp
 *
 *  Created on: Nov 16, 2018
 *      Author: dennis
 */

#include "PostController.h"

PostController::PostController(BasicLed* led1, BasicLed* led2, Solenoid* up, Solenoid* down) {
	this->led1 = led1;
	this->led2 = led2;
	this->up = up;
	this->down = down;
	down->activate();
	isPostUp = false;
}

void PostController::postUp(){
	if (isPostUp) return;

	led1->setColor(RED);
	led2->setColor(RED);
	up->activate();
	isPostUp = true;
}
void PostController::postDown(){
	if (!isPostUp) return;

	led1->setColor(BLACK);
	led2->setColor(BLACK);
	down->activate();
	isPostUp = false;
}
