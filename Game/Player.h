/*
 * Player.h
 *
 *  Created on: Oct 31, 2018
 *      Author: dennis
 */

#ifndef PLAYER_H_
#define PLAYER_H_
#include <Arduino.h>

class Player {
public:
	Player();
	unsigned int score = 0;
	uint8_t ballsLeft = 0;
	uint8_t bonusBalls = 0;
	bool gameIsOver = true;
	bool playing = false;
};

#endif /* PLAYER_H_ */
