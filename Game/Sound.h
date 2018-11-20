/*
 * Sound.h
 *
 *  Created on: Nov 20, 2018
 *      Author: dennis
 */
//001.wav = HighChime 44,1 kHz
//002.wav = MedChime 44,1
//003.mp3 = sailboat side microphone
//004.mp3 = coin in arcade
//005.mp3 = ambient shore waves
//006.mp3 = very deep bell
//007.mp3 = foghorn
//008.mp3 = hiscore tune
//009.mp3 = gameOver guitar
//010.mp3 = LowChime 44,1

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

#include "DFRobotDFPlayerMini.h"

class Sound : public DFRobotDFPlayerMini {
public:
	Sound();
	void playFolder(uint8_t folder, uint8_t number);
	void play(uint8_t number);
private:
	uint8_t lastSound = 0;

	bool isRepeatable(uint8_t number);
};

#endif /* SOUND_H_ */
