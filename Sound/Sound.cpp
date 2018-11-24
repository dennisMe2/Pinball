/*
 * Sound.cpp
 *
 *  Created on: Nov 20, 2018
 *      Author: dennis
 */

#include "../Sound/Sound.h"

Sound::Sound() {

}

void Sound::play(uint8_t number) {
	if (lastSound == number)
			return;

		//dfpExecute(0x0F, folder, number);
		if(++commandPtr > 8) commandPtr = 8; //overwrite last to not reverse order as a ring buffer would
		commands[commandPtr] = number;

		if (isRepeatable(number)) {
			lastSound = 0;
		} else {
			lastSound = number;
		}
}

void Sound::begin(Stream &stream) {
	mySerial = &stream;
	delay(100);
	dfpExecute(0x06, 0x00, 0x30); // set volume DL=0x00-0x30, default=0x30
	currentVolume = 0x30;
}

void Sound::volume(uint8_t vol) {
	if (vol == currentVolume) return;

	//dfpExecute(0x06, 0x00, vol);
	if(++commandPtr > 8) commandPtr = 8; //overwrite last to not reverse order as a ring buffer would
	commands[commandPtr] = -vol;

	currentVolume = vol;
}

bool Sound::isRepeatable(uint8_t number) {
	return (number == CHIME_HIGH || number == CHIME_MED || number == CHIME_LOW
			|| number == BELL_LOW || number == FOG_HORN
			|| number == SOUND_COIN_IN);
}

void Sound::processCommands(){
	bool commandExecuted = false;

	if (commandPtr == -1) return;

	if (commands[commandPtr] < 0){
		commandExecuted = dfpExecute(0x06, 0x00, -commands[commandPtr]);
	} else{
		commandExecuted = dfpExecute(0x0F, 0x01, commands[commandPtr]);
	}
	if (commandExecuted) commandPtr--;
}

//based on: http://markus-wobisch.blogspot.com/2016/09/arduino-sounds-dfplayer.html
bool Sound::dfpExecute(uint8_t CMD, uint8_t Par1, uint8_t Par2) {
# define Start_Byte   0x7E
# define Version_Byte  0xFF
# define Command_Length 0x06
# define Acknowledge  0x00
# define End_Byte    0xEF

	//wait 20 milliseconds between commands to prevent spontaneous resets of the mp3 module
	if(intMillis() - lastCommandTime < 20) return false;

	// Calculate the checksum (2 bytes)
	uint16_t checksum = -(Version_Byte + Command_Length + CMD + Acknowledge
			+ Par1 + Par2);

	// Build the command line
	uint8_t Command_line[10] = { Start_Byte, Version_Byte, Command_Length, CMD,
			Acknowledge, Par1, Par2, highByte(checksum), lowByte(checksum),
			End_Byte };

	// Send the command line to DFPlayer
	mySerial->write(Command_line, 10);
	lastCommandTime = intMillis();
	return true;
}
