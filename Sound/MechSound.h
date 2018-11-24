/*
 * MechSound.h
 *
 *  Created on: Nov 24, 2018
 *      Author: dennis
 */

#ifndef MECHSOUND_H_
#define MECHSOUND_H_

#define TASK_NONE 0
#define TASK_RATTLE 1
#define TASK_KNOCK 2

#include "../Power/Solenoid.h"
#include "../Utils.h"

class MechSound {
public:
	MechSound(Solenoid* solenoid);
	void rattle(uint8_t numer);
	void knock(uint8_t numer);
	void updateSound();
	void stop();
private:
	Solenoid* solenoid;
	uint8_t rattleCounter=0;
	uint8_t oldMaxOnTime = 25;
	uint8_t task = TASK_NONE;
};

#endif /* MECHSOUND_H_ */
