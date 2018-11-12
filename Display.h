/*
 * Display.h
 *
 *  Created on: Oct 9, 2018
 *      Author: dennis
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_
#define SEG_DP  0b10000000
#define SHOW_INSERT_COIN 0
#define SHOW_SCORE 1
#define SHOW_GAME_OVER 2
#define SHOW_HIGH_SCORE 3
#define SHOW_PLAYER 4
#define SHOW_NUM_PLAYERS 5
#define SHOW_PLAYER_UP 6
#define SHOW_SWITCHES 7


#include "Arduino.h"
#include "Game.h"
#include <TM1637Display.h>

class Display : public TM1637Display {
	//
	//  AAA
	// F   B
	// F   B
	//  GGG
	// E   C
	// E   C
	//  DDD  DP

public:
	const uint8_t SEG_OFF[4] = {0,0,0,0	};

	const uint8_t SEG_PLAYER_UP_A[1] = {
		SEG_A | SEG_F | SEG_B | SEG_G | SEG_E | SEG_DP    	// P.
	};

	const uint8_t SEG_PLAYER_UP_B[1] = {
		SEG_F | SEG_G | SEG_E | SEG_C | SEG_D | SEG_DP 		// b.
	};

	const uint8_t SEG_INS[4] = {
		SEG_F | SEG_E ,           							// I
		SEG_E | SEG_G | SEG_C ,   							// n
		SEG_A | SEG_F | SEG_G | SEG_C | SEG_D | SEG_DP, 	// S.
		0
	};

	const uint8_t SEG_COIN[4] = {
		SEG_A | SEG_F | SEG_E | SEG_D ,           			// C
		SEG_G | SEG_E | SEG_D | SEG_C ,   					// o
		SEG_E  ,                           					// i
		SEG_E | SEG_G | SEG_C            					// n
	};

	const uint8_t SEG_PLAY[4] = {
		SEG_A | SEG_F | SEG_B | SEG_G | SEG_E ,    			// P
		SEG_F | SEG_E | SEG_D ,			   					// L
		SEG_E | SEG_F| SEG_A| SEG_B| SEG_C| SEG_G ,			// A
		SEG_F | SEG_B | SEG_G| SEG_E | SEG_DP				// Y.
	};

	const uint8_t SEG_HIGH[4] = {
		SEG_F | SEG_B | SEG_G | SEG_E | SEG_C ,         // H
		SEG_E  ,   										// i
		SEG_A | SEG_F | SEG_B | SEG_G | SEG_C | SEG_D  ,// g
		SEG_F | SEG_G | SEG_E | SEG_C            		// h
	};

	const uint8_t SEG_SCOR[4] = {
		SEG_A | SEG_F | SEG_G | SEG_C | SEG_D  ,        // S
		SEG_G | SEG_E | SEG_D ,           				// c
		SEG_G | SEG_E | SEG_D | SEG_C ,  				// o
		SEG_E | SEG_G | SEG_DP        					// r.
	};



	Display(uint8_t pinClk, uint8_t pinDIO);
	void refreshDisplay();
	void showInsertCoin();
	void showScore();
	void showPlayer();
	void showNumPlayers();
	void showHighScore();
	void showGameOver();
	void showPlayerUp();
	void showSwitches(unsigned int switches);

	void setGame(Game* gamePtr);
	uint8_t function = SHOW_INSERT_COIN;
	unsigned long nextSegmentTime = millis();
	uint8_t nextSegmentIndex = 0;
	unsigned int period = 1000;
	unsigned int refresh = 500; //10Hz refresh rate
	unsigned int switchData = 0;
private:
	Game* gamePointer = 0;
	void setFunction(int function);
};

#endif /* DISPLAY_H_ */
