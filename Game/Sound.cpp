/*
 * Sound.cpp
 *
 *  Created on: Nov 20, 2018
 *      Author: dennis
 */

#include "Sound.h"

Sound::Sound() : DFRobotDFPlayerMini() {

}

void Sound::play(uint8_t number){
	playFolder(1,number);
}

bool Sound::isRepeatable(uint8_t number) {
	return (
			number == CHIME_HIGH ||
			number == CHIME_MED ||
			number == CHIME_LOW ||
			number == BELL_LOW ||
			number == FOG_HORN ||
			number == SOUND_COIN_IN);
}

void Sound::playFolder(uint8_t folder, uint8_t number){
	if(lastSound == number) return;

	DFRobotDFPlayerMini::playFolder(folder, number);

	if (isRepeatable(number)) {
		lastSound = 0;
	}else {
		lastSound = number;
	}
}
