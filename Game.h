/*
 * Game.h
 *
 *  Created on: Oct 5, 2018
 *      Author: dennis
 */

#ifndef GAME_H_
#define GAME_H_
#include <Arduino.h>
#include "Player.h"

class Game {
public:
	Game(int ballC, Player* player1, Player* player2, Player* player3, Player* player4);
	bool isGameOver();
	void addScore(uint8_t points);
	unsigned int getScore();
	unsigned char getBalls();
	void lostBall();
	void playBall();
	bool addPlayer();
	unsigned int getNumPlayers();
	unsigned int getActivePlayer(){return activePlayer;};
	void setMultiplier(uint8_t multi);
private:
	uint8_t multiplier = 1;
	uint8_t ballCount = 3;
	bool gameIsOver = true;
	uint8_t activePlayer = 0;
	uint8_t numberOfPlayers = 0;
	Player* players[4];
};

#endif /* GAME_H_ */
