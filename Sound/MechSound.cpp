/*
 * MechSound.cpp
 *
 *  Created on: Nov 24, 2018
 *      Author: dennis
 */

#include "MechSound.h"

MechSound::MechSound(Solenoid* solenoid) {
	this->solenoid = solenoid;
}

void MechSound::rattle(uint8_t number){
	stop();
	task = TASK_RATTLE;
	rattleCounter = number;
}

void MechSound::knock(uint8_t number){
	stop();
	task = TASK_KNOCK;
	rattleCounter = number;
}

void MechSound::stop(){
	task = TASK_NONE;
	solenoid->maxOnTime = oldMaxOnTime;
	solenoid->deactivate();
}

void MechSound::updateSound(){
	switch (task){
	case TASK_RATTLE:
		if(millis() % 100 == 0){
			solenoid->maxOnTime = 2;
			solenoid->activate();
			if(--rattleCounter == 0) stop();
		}
		break;
	case TASK_KNOCK:
		if(millis() % 300 == 0){
			solenoid->maxOnTime = 10;
			solenoid->activate();
			if(--rattleCounter == 0) stop();
		}
	}
}



