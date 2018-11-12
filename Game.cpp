/*
 * Game.cpp
 *
 *  Created on: Oct 5, 2018
 *      Author: dennis
 */

#include "Game.h"
#include "Utils.h"

Game::Game(int ballC, Player* player1, Player* player2, Player* player3, Player* player4) {
	ballCount = ballC;
	players[0] = player1;
	players[1] = player2;
	players[2] = player3;
	players[3] = player4;
}

void Game::setMultiplier(uint8_t multi) {
	multiplier = multi;
}

uint8_t Game::getState(){
	return state;
}

void Game::setState(uint8_t newState){
	if(newState == PLAYER_UP || newState == FIRST_PLAYER_UP){
		if (state == COIN_IN) {
			for(int i=0; i<4; i++){
				players[i]->ballsLeft = ballCount;
				players[i]->gameIsOver = false;
				players[i]->score = 0;
				players[i]->bonusBalls = 0;
			}
			activePlayer = 0;
			multiplier = 1;
		}
	}
	state = newState;

}

void Game::update(){

}

void Game::addScore(uint8_t points) {

	players[activePlayer]->score += points * multiplier;

	if (players[activePlayer]->score >= 2300 && players[activePlayer]->bonusBalls == 0) {
		players[activePlayer]->ballsLeft++;
		players[activePlayer]->bonusBalls++;
	}

	if (players[activePlayer]->score >= 4000 && players[activePlayer]->bonusBalls == 1) {
		players[activePlayer]->ballsLeft++;
		players[activePlayer]->bonusBalls++;
	}

	if (players[activePlayer]->score >= 7000 && players[activePlayer]->bonusBalls == 2) {
		players[activePlayer]->ballsLeft++;
		players[activePlayer]->bonusBalls++;
	}
}

unsigned int Game::getScore() {
	return players[activePlayer]->score;
}

unsigned char Game::getBalls() {
	return players[activePlayer]->ballsLeft;
}

unsigned int Game::getNumPlayers(){
	return numberOfPlayers;
}

void Game::lostBall() {
	uint8_t startPlayerIndex = activePlayer;

	players[activePlayer]->ballsLeft--; //subtract ball from active player

	if (players[activePlayer]->ballsLeft == 0) players[activePlayer]->gameIsOver = true;

	do{
		if(++activePlayer > (numberOfPlayers-1)) activePlayer = 0;
	}while(players[activePlayer]->gameIsOver && (activePlayer != startPlayerIndex));
	//keep checking until we find a player with balls or back to the player we began with

	//if we were unable to find any player with balls, declare the game over
	if(players[activePlayer]->gameIsOver){
		state = GAME_OVER;
		numberOfPlayers = 0;
	}else{
		state = PLAYER_UP;
	}
}


bool Game::addPlayer(){
	state = COIN_IN;

	if(numberOfPlayers < 4) {
		numberOfPlayers++;
		return true;
	}else{
		return false;
	}
}

