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

class Sound {
public:
	Sound();
	void playFolder(uint8_t folder, uint8_t number);
	void play(uint8_t number);
	void begin(Stream &stream);
	void volume(uint8_t vol);
private:
	uint8_t lastSound = 0;
	Stream* mySerial = 0;
	void dfpExecute(uint8_t CMD, uint8_t Par1, uint8_t Par2);
	bool isRepeatable(uint8_t number);
};

#endif /* SOUND_H_ */
