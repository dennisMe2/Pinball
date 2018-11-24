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
#define TEST_MODE 10
#define NEW_HISCORE_GAMEOVER 11
#define NEW_HISCORE_NEXT_PLAYER 12
#define RESET 13

#include <Arduino.h>
#include <EEPROM.h>
#include "../Game/Player.h"
#include "../Sound/MechSound.h"


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
	unsigned int getHiScore();
	unsigned int getNumPlayers();
	unsigned int getActivePlayer(){return activePlayer;};
	unsigned int getHiScorePlayer(){return hiScorePlayer;};
	void setMultiplier(uint8_t multi);
	void resetHighScore();
	void resetPlayers(){numberOfPlayers=0;};
	void setMechSound(MechSound* mechSound);
private:
	uint8_t state = RESET;
	uint8_t multiplier = 1;
	uint8_t ballCount = 3;
	uint8_t activePlayer = 0;
	uint8_t numberOfPlayers = 0;
	Player* players[4];
	bool replay:1;
	bool replayUsed:1;
	void resetReplay();
	unsigned int hiScore = 0;
	int8_t hiScorePlayer =-1;
	MechSound* mechSound = 0;
};

#endif /* GAME_H_ */
