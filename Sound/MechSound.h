/*
 * MechSound.h
 *
 *  Created on: Nov 24, 2018
 *      Author: dennis
 */

#ifndef MECHSOUND_H_
#define MECHSOUND_H_
#include "../Power/Solenoid.h"

class MechSound {
public:
	MechSound(Solenoid* solenoid);
private:
	Solenoid* solenoid;
};

#endif /* MECHSOUND_H_ */
