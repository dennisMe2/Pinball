/*
 * Sound.cpp
 *
 *  Created on: Nov 20, 2018
 *      Author: dennis
 */

#include "Sound.h"

Sound::Sound() {

}

void Sound::play(uint8_t number) {
	playFolder(1, number);
}

void Sound::begin(Stream &stream) {
	mySerial = &stream;
	while (mySerial->available() < 10) // Wait until initialization parameters are received (10 bytes)
		delay(30);            // have >20ms delays between commands
	dfpExecute(0x06, 0x00, 0x30); // set volume DL=0x00-0x30, default=0x30
//	delay(30);
//	dfpExecute(0x4A, 0x00, 0x00); //mysterious "Keep on" command!
}

void Sound::volume(uint8_t vol) {
	dfpExecute(0x06, 0x00, vol);
}

bool Sound::isRepeatable(uint8_t number) {
	return (number == CHIME_HIGH || number == CHIME_MED || number == CHIME_LOW
			|| number == BELL_LOW || number == FOG_HORN
			|| number == SOUND_COIN_IN);
}

void Sound::playFolder(uint8_t folder, uint8_t number) {
	if (lastSound == number)
		return;

	dfpExecute(0x0F, folder, number);

	if (isRepeatable(number)) {
		lastSound = 0;
	} else {
		lastSound = number;
	}
}

//http://markus-wobisch.blogspot.com/2016/09/arduino-sounds-dfplayer.html
void Sound::dfpExecute(uint8_t CMD, uint8_t Par1, uint8_t Par2) {
# define Start_Byte   0x7E
# define Version_Byte  0xFF
# define Command_Length 0x06
# define Acknowledge  0x00
# define End_Byte    0xEF

	// Calculate the checksum (2 bytes)
	uint16_t checksum = -(Version_Byte + Command_Length + CMD + Acknowledge
			+ Par1 + Par2);

	// Build the command line
	uint8_t Command_line[10] = { Start_Byte, Version_Byte, Command_Length, CMD,
			Acknowledge, Par1, Par2, highByte(checksum), lowByte(checksum),
			End_Byte };

	// Send the command line to DFPlayer
	mySerial->write(Command_line, 10);
}
