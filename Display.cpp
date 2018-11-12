/*
 * Display.cpp
 *
 *  Created on: Oct 9, 2018
 *      Author: dennis
 */

#include "Display.h"

Display::Display(uint8_t pinClk, uint8_t pinDIO) :
		TM1637Display(pinClk, pinDIO) {
}

void Display::setGame(Game* gamePtr) {
	gamePointer = gamePtr;
}

void Display::showInsertCoin() {
	setFunction(SHOW_INSERT_COIN);
}

void Display::showScore() {
	setFunction(SHOW_SCORE);
}
void Display::showPlayer() {
	setFunction(SHOW_PLAYER);
}
void Display::showPlayerUp() {
	setFunction(PLAYER_UP);
}
void Display::showNumPlayers() {
	setFunction(SHOW_NUM_PLAYERS);
}
void Display::showGameOver() {
	setFunction(GAME_OVER);
}

void Display::showHighScore() {
	setFunction(SHOW_HIGH_SCORE);
}

void Display::setFunction(int func) {
	nextSegmentTime = millis();
	nextSegmentIndex = 0;
	function = func;
}

void Display::showSwitches(unsigned int switches){
	switchData = switches;
}

void Display::refreshDisplay() {
	if (millis() < nextSegmentTime)
		return;

	switch (function) {
	case SHOW_INSERT_COIN:
		if (++nextSegmentIndex > 2)
			nextSegmentIndex = 0;
		if (nextSegmentIndex == 0)
			TM1637Display::setSegments(SEG_INS);
		if (nextSegmentIndex == 1)
			TM1637Display::setSegments(SEG_COIN);
		if (nextSegmentIndex == 2)
			TM1637Display::setSegments(SEG_OFF);
		nextSegmentTime = millis() + period;
		break;

	case SHOW_SCORE:
		if (gamePointer != 0) {
			TM1637Display::showNumberDec(gamePointer->getScore(), false, 4, 0);
			nextSegmentTime = millis() + refresh;
		}
		break;

	case SHOW_HIGH_SCORE:
		if (++nextSegmentIndex > 3)
			nextSegmentIndex = 0;
		if (nextSegmentIndex == 0)
			TM1637Display::setSegments(SEG_HIGH);
		if (nextSegmentIndex == 1)
			TM1637Display::setSegments(SEG_SCOR);
		if (nextSegmentIndex == 2)
			TM1637Display::showNumberDec(gamePointer->getScore(), false, 4, 0);
		if (nextSegmentIndex == 3)
			TM1637Display::setSegments(SEG_OFF);
		nextSegmentTime = millis() + period;
		break;

	case SHOW_PLAYER:
		TM1637Display::setSegments(SEG_PLAY);
		nextSegmentTime = millis() + refresh;
		break;
	case PLAYER_UP:

			TM1637Display::setSegments(SEG_PLAYER_UP_A, 1,0);
			TM1637Display::showNumberDec(gamePointer->getActivePlayer() + 1, false, 1, 1);
			TM1637Display::setSegments(SEG_PLAYER_UP_B, 1,2);
			TM1637Display::showNumberDec(gamePointer->getBalls(), false, 1, 3);
			nextSegmentTime = millis() + refresh;
			break;
	case SHOW_NUM_PLAYERS:
		TM1637Display::showNumberDec(gamePointer->getNumPlayers(), false, 4, 0);
		nextSegmentTime = millis() + refresh;
	}
}

