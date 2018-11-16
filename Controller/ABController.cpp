/*
 * ABController.cpp
 *
 *  Created on: Nov 15, 2018
 *      Author: dennis
 */

#include "ABController.h"

ABController::ABController(DumbLed* a, DumbLed* b, DumbLed* tl, DumbLed* tr, DumbLed* bl, DumbLed* br) {
	this->a = a;
	this->b = b;
	this->tl = tl;
	this->tr = tr;
	this->bl = bl;
	this->br = br;

	reset();
}

void ABController::setA(){
	a->setColor(RED);
	tr->setColor(WHITE);
	bl->setColor(WHITE);
	isSetLedA = true;
}

void ABController::setB(){
	b->setColor(RED);
	tl->setColor(WHITE);
	br->setColor(WHITE);
	isSetLedB = true;
}

bool ABController::isSetA(){
	return isSetLedA;
}

bool ABController::isSetB(){
	return isSetLedB;
}

void ABController::reset(){
		this->a->setColor(BLACK);
		this->b->setColor(BLACK);
		this->tl->setColor(BLACK);
		this->tr->setColor(BLACK);
		this->bl->setColor(BLACK);
		this->br->setColor(BLACK);

		isSetLedA = false;
		isSetLedB = false;
}
