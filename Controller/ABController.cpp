/*
 * ABController.cpp
 *
 *  Created on: Nov 15, 2018
 *      Author: dennis
 */

#include "ABController.h"

ABController::ABController(DumbLed* a, DumbLed* b, DumbLed* tl, DumbLed* tr, DumbLed* bl, DumbLed* br) {
	this->a = a;
	this->a->setColor(BLACK);

	this->b = b;
	this->b->setColor(BLACK);


	this->tl = tl;
	this->tl->setColor(BLACK);

	this->tr = tr;
	this->tr->setColor(BLACK);

	this->bl = bl;
	this->bl->setColor(BLACK);

	this->br = br;
	this->br->setColor(BLACK);

}

void ABController::setA(){
	a->setColor(RED);
	tr->setColor(WHITE);
	bl->setColor(WHITE);
}

void ABController::setB(){
	b->setColor(RED);
	tl->setColor(WHITE);
	br->setColor(WHITE);
}
