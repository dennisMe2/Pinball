/*
 * Sound.h
 *
 *  Created on: Nov 20, 2018
 *      Author: dennis
 */

#define CHIME_HIGH 1
#define CHIME_MED 2
#define CHIME_LOW 10
#define AMBIENT_BOAT 3
#define SOUND_COIN_IN 4
#define AMBIENT_WAVES 5
#define BELL_LOW 6
#define FOG_HORN 7
#define TUNE_HISCORE 8
#define TUNE_GAME_OVER 9

#ifndef SOUND_H_
#define SOUND_H_
#include <Arduino.h>
#include "../Utils.h"

class Sound {
public:
	Sound();
	void play(uint8_t number);
	void begin(Stream &stream);
	void volume(uint8_t vol);
	void processCommands();
private:
	int8_t commands[9] = {0,0,0,0,0,0,0,0,0};// negative is volume, positive = sound nr [1..127] in folder 001
	int8_t commandPtr = -1; //-1 == no commands
	uint8_t lastSound = 0;
	uint8_t currentVolume = 0;
	Stream* mySerial = 0;
	bool dfpExecute(uint8_t CMD, uint8_t Par1, uint8_t Par2);
	bool isRepeatable(uint8_t number);
	unsigned int lastCommandTime = 0;
};

#endif /* SOUND_H_ */
