/*
 * ABController.cpp
 *
 *  Created on: Nov 15, 2018
 *      Author: dennis
 */

#include "ABController.h"

ABController::ABController(BasicLed* a, BasicLed* b, BasicLed* tl, BasicLed* tr, BasicLed* bl, BasicLed* br) {
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

void ABController::resetA(){
	a->setColor(GLOW_B);
	tr->setColor(GLOW_B);
	bl->setColor(GLOW_B);
	isSetLedA = false;
}

void ABController::setB(){
	b->setColor(RED);
	tl->setColor(WHITE);
	br->setColor(WHITE);
	isSetLedB = true;
}

void ABController::resetB(){
	b->setColor(GLOW_B);
	tl->setColor(GLOW_B);
	br->setColor(GLOW_B);
	isSetLedB = false;
}

bool ABController::isSetA(){
	return isSetLedA;
}

bool ABController::isSetB(){
	return isSetLedB;
}

void ABController::reset(){
		this->a->setColor(GLOW_B);
		this->b->setColor(GLOW_B);
		this->tl->setColor(GLOW_B);
		this->tr->setColor(GLOW_B);
		this->bl->setColor(GLOW_B);
		this->br->setColor(GLOW_B);

		isSetLedA = false;
		isSetLedB = false;
}
