/*
 * Game.h
 *
 *  Created on: Oct 5, 2018
 *      Author: dennis
 */

#ifndef GAME_H_
#define GAME_H_

	#define GAME_OVER 0
	#define COIN_IN 1
	#define FIRST_PLAYER_UP 2
	#define PLAYER_UP 3
	#define PLAYER_PLAYING 4
	#define TILT 5
	#define PLAYER_LOST_BALL 6
	#define PLAY_AGAIN 7
	#define BEFORE_PLAY 8
	#define LOCATE_BALL 9

#include <Arduino.h>
#include "../Game/Player.h"


class Game {
public:
	Game(int ballC, Player* player1, Player* player2, Player* player3, Player* player4);
	void addScore(uint8_t points);
	unsigned int getScore();
	unsigned char getBalls();
	void lostBall();
	void update();
	void setReplay();
	boolean getReplay();
	void setState(uint8_t newState);
	uint8_t getState();
	bool addPlayer();
	unsigned int getNumPlayers();
	unsigned int getActivePlayer(){return activePlayer;};
	void setMultiplier(uint8_t multi);
private:
	uint8_t state = LOCATE_BALL;
	uint8_t multiplier = 1;
	uint8_t ballCount = 3;
	uint8_t activePlayer = 0;
	uint8_t numberOfPlayers = 0;
	Player* players[4];
	bool replay:1;
	bool replayUsed:1;
	void resetReplay();
};

#endif /* GAME_H_ */
